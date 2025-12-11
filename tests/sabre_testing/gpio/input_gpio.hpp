#pragma once

#include <sabre/gpio/input_gpio.hpp>

namespace Sabre::Testing
{
    class InputGPIO : public Sabre::InputGPIO
    {
    protected:
        bool _get_level() const override;

    public:
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(ISRHandler, ISRTrigger) override;
        void reset() override;

        bool level = true;
    };
} // namespace Sabre::Testing