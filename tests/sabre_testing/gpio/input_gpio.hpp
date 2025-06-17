#ifndef SABRE_TESTING_INPUT_GPIO_H
#define SABRE_TESTING_INPUT_GPIO_H

#include <sabre/gpio/input_gpio.hpp>

namespace sabre::testing
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
} // namespace sabre::testing

#endif // SABRE_TESTING_INPUT_GPIO_H