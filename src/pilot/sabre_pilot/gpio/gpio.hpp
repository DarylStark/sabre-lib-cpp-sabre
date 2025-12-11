#pragma once

#include <sabre/gpio/gpio.hpp>

namespace Sabre::Pilot
{
    class GPIO : public Sabre::GPIO
    {
    public:
        void reset() override;
    };
} // namespace Sabre::Pilot