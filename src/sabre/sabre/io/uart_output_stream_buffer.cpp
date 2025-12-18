#include <streambuf>

#include "uart_output_stream_buffer.hpp"

namespace sabre::io
{
    UartStreamBuf::UartStreamBuf(Uart::UniquePtr uart, size_t buffer_size)
        : _uart(std::move(uart))
    {
        _buffer = new char[buffer_size];
        _buffer_size = buffer_size;
        _reset_put_buffer();
    }

    UartStreamBuf::~UartStreamBuf()
    {
        sync();
        delete[] _buffer;
    }

    UartStreamBuf::int_type UartStreamBuf::overflow(int_type c)
    {
        if (c != traits_type::eof())
        {
            if (pptr() >= epptr())
            {
                sync();
                _uart->flush();
            }
            *pptr() = c;
            pbump(1);
        }
        return c;
    }

    int UartStreamBuf::sync()
    {
        size_t len = pptr() - pbase();
        if (len == 0)
            return 0;

        for (size_t i = 0; i < len; ++i)
            _uart->write_byte(pbase()[i]);
        _reset_put_buffer();
        return 0;
    }

    void UartStreamBuf::_reset_put_buffer()
    {
        setp(_buffer, _buffer + _buffer_size);
    }
} // namespace sabre::io