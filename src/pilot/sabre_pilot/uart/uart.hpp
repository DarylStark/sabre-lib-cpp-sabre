#pragma once

#include "../../simulator/device.hpp"
#include <sabre/hal/uart.hpp>

namespace sabre::Pilot
{
    class Uart : public sabre::hal::Uart
    {
    private:
        Device *_device;
        uint32_t _uart_number;
        size_t _buffer_size;

    public:
        Uart(Device *device, uint32_t number, size_t buffer_size);
        void initialize() override;
        int writeByte(char data) const override;
        std::string readBytes(size_t max_bytes, uint32_t timeout_ms) override;
        void flush() override;
        void deinitialize() override;
    };
} // namespace sabre::Pilot