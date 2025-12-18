#pragma once

#include "device.hpp"

namespace sabre::impl::pilot
{
    class UartConnector
    {
    private:
        Device &_device_a;
        uint32_t _uart_number_a;
        Device &_device_b;
        uint32_t _uart_number_b;

    public:
        UartConnector(Device &device_a, uint32_t uart_number_a,
                      Device &device_b, uint32_t uart_number_b);
    };
} // namespace sabre::impl::pilot