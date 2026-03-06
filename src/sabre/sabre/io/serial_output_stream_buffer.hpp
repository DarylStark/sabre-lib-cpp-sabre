#pragma once

#include "../hal/serial.hpp"
#include <memory>
#include <streambuf>

namespace sabre::io
{
    /**
     * @brief A stream buffer for Serial output.
     *
     * This class provides a stream buffer that can be used with Serial devices
     * for output operations. It allows for buffered writing to Serial, which
     * can improve performance by reducing the number of write operations.
     */
    class SerialStreamBuf : public std::streambuf
    {
    public:
        using int_type = std::streambuf::traits_type::int_type;

        using Ptr = SerialStreamBuf *;
        using SharedPtr = std::shared_ptr<SerialStreamBuf>;
        using UniquePtr = std::unique_ptr<SerialStreamBuf>;

    private:
        sabre::hal::Serial::Ptr _serialPtr;
        char *_buffer;
        size_t _bufferSize;

        void _resetPutBuffer();

    protected:
        /**
         * @brief Write a character to the Serial device.
         *
         * This method is called when the connected `std::ostream` object tries
         * to write a character to the stream buffer but when the stream buffer
         * is full.
         *
         * @param c The character to write.
         *
         * @return Returns the character written, or `traits_type::eof()` if an
         * error occurs.
         */
        int_type overflow(int_type c) override;

        /**
         * @brief Write a sequence of characters to the Serial device.
         *
         * This method is called when the connected `std::ostream` object tries
         * to write a sequence of characters to the stream buffer.
         *
         * @return Zero at all times.
         */
        int sync() override;

    public:
        /**
         * @brief Constructor for the SerialStreamBuf class.
         *
         * This constructor initializes the stream buffer with a Serial device
         * and a specified buffer size.
         *
         * @param uartPtr The Serial device to use for output operations.
         * @param bufferSize The size of the internal buffer (default is 512).
         */
        SerialStreamBuf(sabre::hal::Serial::Ptr uartPtr,
                        size_t bufferSize = 512);

        /**
         * @brief Destructor for the SerialStreamBuf class.
         *
         * This destructor flushes the buffer and releases any allocated
         * resources.
         */
        ~SerialStreamBuf() noexcept;
    };
} // namespace sabre::io