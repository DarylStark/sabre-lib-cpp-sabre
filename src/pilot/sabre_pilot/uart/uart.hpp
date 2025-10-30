#pragma once

#include "../../mcu.hpp"
#include <sabre/uart/uart.hpp>

namespace sabre::pilot
{
    class UART : public sabre::UART
    {
    private:
        MCU *_mcu;
        uint32_t _uart_number;

    public:
        UART(MCU *mcu, uint32_t number);
        void initialize() override;
        int write_byte(char data) const override;
        void flush() override;
        void deinitialize() override;
    };
} // namespace sabre::pilot