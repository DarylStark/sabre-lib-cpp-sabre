#pragma once

#include "../../simulator/mcu.hpp"
#include <sabre/gpio/input_gpio.hpp>

namespace sabre::pilot
{
    class InputGPIO : public sabre::InputGPIO
    {
    private:
        MCU *_mcu;
        uint32_t _pin;

    protected:
        bool _get_level() const override;

    public:
        InputGPIO(MCU *mcu, uint32_t pin);

        void reset() override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(ISRHandler, ISRTrigger) override;
    };
} // namespace sabre::pilot