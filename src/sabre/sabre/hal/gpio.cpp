#include "gpio.hpp"

namespace sabre::hal
{
    Gpio::Gpio(int32_t pinNumber) : _pinNumber(pinNumber) {}

    int32_t Gpio::getPinNumber() const
    {
        return _pinNumber;
    }
} // namespace sabre::hal