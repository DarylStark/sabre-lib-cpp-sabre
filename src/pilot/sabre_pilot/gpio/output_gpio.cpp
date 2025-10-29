#include "output_gpio.hpp"

namespace sabre::pilot
{
    OutputGPIO::OutputGPIO(MCU *mcu, uint32_t pin) : _mcu(mcu), _pin(pin)
    {
        _mcu->set_gpio_type(pin, GPIOType::OUTPUT);
    }

    void OutputGPIO::reset()
    {
        _mcu->reset_gpio(_pin);
    }

    void OutputGPIO::set_high()
    {
        set_level(true);
    }

    void OutputGPIO::set_low()
    {
        set_level(false);
    }

    void OutputGPIO::set_level(bool level)
    {
        _mcu->set_gpio_state(_pin, level ? 1 : 0);
    }
} // namespace sabre::pilot