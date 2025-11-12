#pragma once

#include "mcu.hpp"

namespace sabre::pilot
{
    class UartConnector
    {
    private:
        MCU &_mcu_a;
        uint32_t _uart_number_a;
        MCU &_mcu_b;
        uint32_t _uart_number_b;

    public:
        UartConnector(MCU &mcu_a, uint32_t uart_number_a, MCU &mcu_b,
                      uint32_t uart_number_b);
    };
} // namespace sabre::pilot