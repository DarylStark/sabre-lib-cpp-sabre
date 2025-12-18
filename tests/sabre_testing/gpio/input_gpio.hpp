#pragma once

#include <sabre/hal/input_gpio.hpp>

namespace sabre::Testing
{
    using sabre::hal::ISRHandler;
    using sabre::hal::ISRTrigger;

    class InputGPIO : public sabre::hal::InputGPIO
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