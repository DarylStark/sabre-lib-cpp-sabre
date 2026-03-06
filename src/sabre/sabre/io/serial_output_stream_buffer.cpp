#include <streambuf>

#include "serial_output_stream_buffer.hpp"

namespace sabre::io
{
    SerialStreamBuf::SerialStreamBuf(sabre::hal::Serial::Ptr serialPtr,
                                     size_t bufferSize)
        : _serialPtr(serialPtr)
    {
        _buffer = new char[bufferSize];
        _bufferSize = bufferSize;
        _resetPutBuffer();
    }

    SerialStreamBuf::~SerialStreamBuf() noexcept
    {
        delete[] _buffer;
    }

    SerialStreamBuf::int_type SerialStreamBuf::overflow(int_type c)
    {
        if (c != traits_type::eof())
        {
            if (pptr() >= epptr())
            {
                sync();
                _serialPtr->flush();
            }
            *pptr() = c;
            pbump(1);
        }
        return c;
    }

    int SerialStreamBuf::sync()
    {
        size_t len = pptr() - pbase();
        if (len == 0)
            return 0;

        for (size_t i = 0; i < len; ++i)
            _serialPtr->writeByte(pbase()[i]);
        _resetPutBuffer();
        return 0;
    }

    void SerialStreamBuf::_resetPutBuffer()
    {
        setp(_buffer, _buffer + _bufferSize);
    }
} // namespace sabre::io