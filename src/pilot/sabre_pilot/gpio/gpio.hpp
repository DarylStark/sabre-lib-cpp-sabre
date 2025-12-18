#pragma once

#include <sabre/gpio/gpio.hpp>

namespace sabre::Pilot
{
    class GPIO : public sabre::GPIO
    {
    public:
        void reset() override;
    };
} // namespace sabre::Pilot