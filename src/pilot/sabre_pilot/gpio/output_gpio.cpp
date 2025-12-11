#include "output_gpio.hpp"

namespace Sabre::Pilot
{
    OutputGPIO::OutputGPIO(Device *device, uint32_t pin)
        : __device(device), _pin(pin)
    {
        __device->set_gpio_type(pin, GPIOType::OUTPUT);
    }

    void OutputGPIO::reset()
    {
        __device->reset_gpio(_pin);
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
        __device->set_gpio_state(_pin, level ? 1 : 0);
    }
} // namespace Sabre::Pilot