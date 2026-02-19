#include "gpio.hpp"

namespace sabre::hal
{
    Gpio::Gpio(int32_t pinNumber) noexcept : _pinNumber(pinNumber) {}

    int32_t Gpio::getPinNumber() const noexcept
    {
        return _pinNumber;
    }
} // namespace sabre::hal