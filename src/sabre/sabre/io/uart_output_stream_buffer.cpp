#include <streambuf>

#include "uart_output_stream_buffer.hpp"

namespace sabre::io
{
    UartStreamBuf::UartStreamBuf(Serial::UniquePtr uartPtr, size_t bufferSize)
        : _uartPtr(std::move(uartPtr))
    {
        _buffer = new char[bufferSize];
        _bufferSize = bufferSize;
        _resetPutBuffer();
    }

    UartStreamBuf::~UartStreamBuf()
    {
        delete[] _buffer;
    }

    UartStreamBuf::int_type UartStreamBuf::overflow(int_type c)
    {
        if (c != traits_type::eof())
        {
            if (pptr() >= epptr())
            {
                sync();
                _uartPtr->flush();
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
            _uartPtr->writeByte(pbase()[i]);
        _resetPutBuffer();
        return 0;
    }

    void UartStreamBuf::_resetPutBuffer()
    {
        setp(_buffer, _buffer + _bufferSize);
    }
} // namespace sabre::io