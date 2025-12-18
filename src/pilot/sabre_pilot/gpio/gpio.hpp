#pragma once

#include <sabre/hal/gpio.hpp>

namespace sabre::Pilot
{
    class Gpio : public sabre::hal::Gpio
    {
    public:
        void reset() override;
    };
} // namespace sabre::Pilot