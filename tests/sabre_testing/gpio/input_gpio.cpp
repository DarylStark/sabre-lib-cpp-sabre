#include "input_gpio.hpp"

namespace Sabre::Testing
{
    bool InputGPIO::_get_level() const
    {
        return level;
    }

    void InputGPIO::enable_pullup() {}
    void InputGPIO::enable_pulldown() {}
    void InputGPIO::disable_pullup() {}
    void InputGPIO::disable_pulldown() {}
    void InputGPIO::add_interrupt_handler(ISRHandler, ISRTrigger) {}
    void InputGPIO::reset() {}
} // namespace Sabre::Testing