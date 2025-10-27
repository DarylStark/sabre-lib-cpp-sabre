#pragma once

#include <sabre/gpio/output_gpio.hpp>

namespace sabre::pilot
{
    class OutputGPIO : public sabre::OutputGPIO
    {
    public:
        void reset() override;
        void set_high() override;
        void set_low() override;
        void set_level(bool level) override;
    };
} // namespace sabre::pilot
