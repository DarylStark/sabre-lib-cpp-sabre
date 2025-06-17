#include "input_gpio.hpp"

namespace sabre
{
    bool InputGPIO::get_level() const
    {
        return _get_level() == !_inverse_level;
    }

    void InputGPIO::set_inverse_level()
    {
        _inverse_level = true;
    }

    void InputGPIO::set_original_level()
    {
        _inverse_level = false;
    }

    bool InputGPIO::get_inverse_level() const
    {
        return _inverse_level;
    }
} // namespace sabre