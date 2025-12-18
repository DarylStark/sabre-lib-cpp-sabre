#include "output_gpio.hpp"

namespace sabre::Pilot
{
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
} // namespace sabre::Pilot