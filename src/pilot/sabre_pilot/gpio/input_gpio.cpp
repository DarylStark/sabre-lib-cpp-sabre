#include "input_gpio.hpp"

namespace sabre::pilot
{
    InputGPIO::InputGPIO(MCU *mcu, uint32_t pin) : _mcu(mcu), _pin(pin)
    {
        mcu->set_gpio_type(pin, GPIOType::INPUT);
    }

    bool InputGPIO::_get_level() const
    {
        // Implementation specific code to get the GPIO level
        return false; // Placeholder
    }

    void InputGPIO::reset()
    {
        // Implementation specific code to reset the GPIO
        _mcu->reset_gpio(_pin);
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