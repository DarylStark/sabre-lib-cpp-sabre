#include "input_gpio.hpp"

namespace sabre::hal
{
    bool InputGpio::getLevel() const
    {
        return _getLevel() == !_inverseLevel;
    }

    void InputGpio::setInverseLevel(bool level) noexcept
    {
        _inverseLevel = level;
    }

    bool InputGpio::getInverseLevel() const noexcept
    {
        return _inverseLevel;
    }
} // namespace sabre::hal