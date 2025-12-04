#pragma once

#include "../../simulator/device.hpp"
#include <sabre/uart/uart.hpp>

namespace sabre::pilot
{
    class UART : public sabre::UART
    {
    private:
        Device *_device;
        uint32_t _uart_number;
        size_t _buffer_size;

    public:
        UART(Device *device, uint32_t number, size_t buffer_size);
        void initialize() override;
        int write_byte(char data) const override;
        std::string read_bytes(size_t max_bytes, uint32_t timeout_ms) override;
        void flush() override;
        void deinitialize() override;
    };
} // namespace sabre::pilot