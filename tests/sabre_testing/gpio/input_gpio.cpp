#include "input_gpio.hpp"

namespace sabre::testing
{
    bool InputGPIO::get_level() const
    {
        return true;
    }

    void InputGPIO::enable_pullup() {}
    void InputGPIO::enable_pulldown() {}
    void InputGPIO::disable_pullup() {}
    void InputGPIO::disable_pulldown() {}
    void InputGPIO::add_interrupt_handler(ISRHandler, ISRTrigger) {}
    void InputGPIO::reset() {}
} // namespace sabre::testing