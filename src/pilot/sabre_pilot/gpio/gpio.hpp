#pragma once

#include <sabre/gpio/gpio.hpp>

namespace sabre::pilot
{
    class GPIO : public sabre::GPIO
    {
    public:
        void reset() override;
    };
} // namespace sabre::pilot