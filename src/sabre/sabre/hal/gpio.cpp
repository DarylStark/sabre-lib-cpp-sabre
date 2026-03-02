#include "gpio.hpp"

namespace sabre::hal
{
    Gpio::Gpio(PinNumber pinNumber) noexcept : _pinNumber(pinNumber) {}

    PinNumber Gpio::getPinNumber() const noexcept
    {
        return _pinNumber;
    }

    sabre::log::LogHelper &Gpio::getLogHelper()
    {
        return _log_helper;
    }
} // namespace sabre::hal