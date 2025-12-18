#include "uart.hpp"

namespace sabre::Pilot
{
    UART::UART(Device *device, uint32_t number, size_t buffer_size)
        : _device(device), _uart_number(number), _buffer_size(buffer_size)
    {
    }

    void UART::initialize()
    {
        // TODO : Custom exception
        if (!_device->initialize_uart(_uart_number, _buffer_size))
            throw std::runtime_error("UART already initialized");
    }

    int UART::write_byte(char data) const
    {
        if (!_device->write_uart_data(_uart_number, data))
            return -1; // UART not initialized
        return 0;      // Success
    }

    std::string UART::read_bytes(size_t max_bytes, uint32_t timeout_ms)
    {
        return _device->read_uart_data(_uart_number, max_bytes, timeout_ms);
    }

    void UART::flush()
    {
        // Implementation for flushing the UART output buffer
        // TODO: Implement something for this
        asm("nop");
    }

    void UART::deinitialize()
    {
        if (!_device->deinitialize_uart(_uart_number))
            throw std::runtime_error("UART not initialized");
    }
} // namespace sabre::Pilot