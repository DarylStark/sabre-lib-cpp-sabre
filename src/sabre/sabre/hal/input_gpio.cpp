#include "input_gpio.hpp"

namespace sabre::hal
{
    bool InputGpio::get_level() const
    {
        return _get_level() == !_inverse_level;
    }

    void InputGpio::set_inverse_level(bool level)
    {
        _inverse_level = level;
    }

    bool InputGpio::get_inverse_level() const
    {
        return _inverse_level;
    }
} // namespace sabre::hal