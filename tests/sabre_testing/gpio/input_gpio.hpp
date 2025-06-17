#ifndef SABRE_TESTING_INPUT_GPIO_H
#define SABRE_TESTING_INPUT_GPIO_H

#include <sabre/gpio/input_gpio.hpp>

namespace sabre::testing
{
    class InputGPIO : public sabre::InputGPIO
    {
    public:
        bool get_level() const;
        void enable_pullup();
        void enable_pulldown();
        void disable_pullup();
        void disable_pulldown();
        void add_interrupt_handler(ISRHandler, ISRTrigger);
        void reset();
    };
} // namespace sabre::testing

#endif // SABRE_TESTING_INPUT_GPIO_H