#pragma once

#include <sabre/gpio/input_gpio.hpp>

namespace sabre::Testing
{
    class InputGPIO : public sabre::InputGPIO
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
} // namespace sabre::Testing