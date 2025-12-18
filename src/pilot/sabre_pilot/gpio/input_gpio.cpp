#include "input_gpio.hpp"

namespace sabre::Pilot
{
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
} // namespace sabre::Pilot