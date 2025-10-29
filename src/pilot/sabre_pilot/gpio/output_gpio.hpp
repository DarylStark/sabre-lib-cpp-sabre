#pragma once

#include "../../mcu.hpp"
#include <sabre/gpio/output_gpio.hpp>

namespace sabre::pilot
{
    class OutputGPIO : public sabre::OutputGPIO
    {
    private:
        MCU *_mcu;
        uint32_t _pin;

    public:
        OutputGPIO(MCU *mcu, uint32_t pin);
        void reset() override;
        void set_high() override;
        void set_low() override;
        void set_level(bool level) override;
    };
} // namespace sabre::pilot
