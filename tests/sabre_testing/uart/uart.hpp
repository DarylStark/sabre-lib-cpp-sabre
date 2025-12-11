#pragma once

#include <sabre/uart/uart.hpp>
#include <sabre/uart/uart_output_stream_buffer.hpp>
#include <string>

namespace Sabre::Testing
{
    class TestUART : public Sabre::UART
    {
    public:
        void initialize();
        int write_byte(char data) const;
        std::string read_bytes(size_t max_bytes, uint32_t timeout_ms) override;
        void flush();
        void deinitialize();

        mutable std::string _buf;
    };
} // namespace Sabre::Testing