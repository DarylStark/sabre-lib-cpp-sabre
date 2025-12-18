#include "hal.hpp"

namespace sabre::impl::pilot
{
    Uart::Uart(Device *device, uint32_t number, size_t buffer_size)
        : _device(device), _uart_number(number), _buffer_size(buffer_size)
    {
    }

    void Uart::initialize()
    {
        // TODO : Custom exception
        if (!_device->initialize_uart(_uart_number, _buffer_size))
            throw std::runtime_error("UART already initialized");
    }

    int Uart::writeByte(char data) const
    {
        if (!_device->write_uart_data(_uart_number, data))
            return -1; // UART not initialized
        return 0;      // Success
    }

    std::string Uart::readBytes(size_t max_bytes, uint32_t timeout_ms)
    {
        return _device->read_uart_data(_uart_number, max_bytes, timeout_ms);
    }

    void Uart::flush()
    {
        // Implementation for flushing the UART output buffer
        // TODO: Implement something for this
        asm("nop");
    }

    void Uart::deinitialize()
    {
        if (!_device->deinitialize_uart(_uart_number))
            throw std::runtime_error("UART not initialized");
    }

    void Gpio::reset()
    {
        // Implementation specific code to reset the GPIO
    }

    InputGpio::InputGpio(Device *device, uint32_t pin)
        : _device(device), _pin(pin)
    {
        _device->set_gpio_type(pin, GPIOType::INPUT);
    }

    bool InputGpio::_getLevel() const
    {
        // Implementation specific code to get the GPIO level
        return _device->get_gpio(_pin).state > 0;
    }

    void InputGpio::reset()
    {
        // Implementation specific code to reset the GPIO
        _device->reset_gpio(_pin);
    }

    void InputGpio::enablePullup()
    {
        // Implementation specific code to enable pull-up resistor
    }

    void InputGpio::enablePulldown()
    {
        // Implementation specific code to enable pull-down resistor
    }

    void InputGpio::disablePullup()
    {
        // Implementation specific code to disable pull-up resistor
    }

    void InputGpio::disablePulldown()
    {
        // Implementation specific code to disable pull-down resistor
    }

    void InputGpio::addInterruptHandler(sabre::hal::ISRHandler handler,
                                        sabre::hal::ISRTrigger trigger)
    {
        // Implementation specific code to add an interrupt handler
    }

    OutputGpio::OutputGpio(Device *device, uint32_t pin)
        : __device(device), _pin(pin)
    {
        __device->set_gpio_type(pin, GPIOType::OUTPUT);
    }

    void OutputGpio::reset()
    {
        __device->reset_gpio(_pin);
    }

    void OutputGpio::setHigh()
    {
        setLevel(true);
    }

    void OutputGpio::setLow()
    {
        setLevel(false);
    }

    void OutputGpio::setLevel(bool level)
    {
        __device->set_gpio_state(_pin, level ? 1 : 0);
    }
} // namespace sabre::impl::pilot