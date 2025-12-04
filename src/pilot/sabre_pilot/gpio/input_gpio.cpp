#include "input_gpio.hpp"

namespace sabre::pilot
{
    InputGPIO::InputGPIO(Device *device, uint32_t pin)
        : _device(device), _pin(pin)
    {
        _device->set_gpio_type(pin, GPIOType::INPUT);
    }

    bool InputGPIO::_get_level() const
    {
        // Implementation specific code to get the GPIO level
        return _device->get_gpio(_pin).state > 0;
    }

    void InputGPIO::reset()
    {
        // Implementation specific code to reset the GPIO
        _device->reset_gpio(_pin);
    }

    void InputGPIO::enable_pullup()
    {
        // Implementation specific code to enable pull-up resistor
    }

    void InputGPIO::enable_pulldown()
    {
        // Implementation specific code to enable pull-down resistor
    }

    void InputGPIO::disable_pullup()
    {
        // Implementation specific code to disable pull-up resistor
    }

    void InputGPIO::disable_pulldown()
    {
        // Implementation specific code to disable pull-down resistor
    }

    void InputGPIO::add_interrupt_handler(ISRHandler handler,
                                          ISRTrigger trigger)
    {
        // Implementation specific code to add an interrupt handler
    }
} // namespace sabre::pilot