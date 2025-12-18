#include "input_gpio.hpp"

namespace sabre::hal
{
    bool InputGpio::getLevel() const
    {
        return _getLevel() == !_inverseLevel;
    }

    void InputGpio::setInverseLevel(bool level)
    {
        _inverseLevel = level;
    }

    bool InputGpio::getInverseLevel() const
    {
        return _inverseLevel;
    }
} // namespace sabre::hal