#pragma once

#include <sabre/hal/uart.hpp>
#include <string>

namespace sabre::Testing
{
    class TestUART : public sabre::hal::UART
    {
    public:
        void initialize();
        int write_byte(char data) const;
        std::string read_bytes(size_t max_bytes, uint32_t timeout_ms) override;
        void flush();
        void deinitialize();

        mutable std::string _buf;
    };
} // namespace sabre::Testing