#include "gpio.hpp"

namespace sabre::hal
{
    Gpio::Gpio(PinNumber pinNumber) noexcept : _pinNumber(pinNumber) {}

    PinNumber Gpio::getPinNumber() const noexcept
    {
        return _pinNumber;
    }
} // namespace sabre::hal