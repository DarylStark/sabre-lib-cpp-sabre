#include "uart.hpp"

namespace sabre::pilot
{
    UART::UART(MCU *mcu, uint32_t number) : _mcu(mcu), _uart_number(number) {}

    void UART::initialize()
    {
        // TODO : Custom exception
        if (!_mcu->initialize_uart(_uart_number))
            throw std::runtime_error("UART already initialized");
    }

    int UART::write_byte(char data) const
    {
        if (!_mcu->write_uart_data(_uart_number, data))
            return -1; // UART not initialized
        return 0;      // Success
    }

    void UART::flush()
    {
        // Implementation for flushing the UART output buffer
        // TODO: Implement something for this
        asm("nop");
    }

    void UART::deinitialize()
    {
        if (!_mcu->deinitialize_uart(_uart_number))
            throw std::runtime_error("UART not initialized");
    }
} // namespace sabre::pilot