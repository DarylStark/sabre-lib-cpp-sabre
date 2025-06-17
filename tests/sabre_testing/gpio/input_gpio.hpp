#ifndef SABRE_TESTING_INPUT_GPIO_H
#define SABRE_TESTING_INPUT_GPIO_H

#include <sabre/gpio/input_gpio.hpp>

namespace sabre::testing
{
    class InputGPIO : public sabre::InputGPIO
    {
    protected:
        bool _get_level() const;

    public:
        void enable_pullup();
        void enable_pulldown();
        void disable_pullup();
        void disable_pulldown();
        void add_interrupt_handler(ISRHandler, ISRTrigger);
        void reset();

        bool level = true;
    };
} // namespace sabre::testing

#endif // SABRE_TESTING_INPUT_GPIO_H