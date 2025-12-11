#pragma once

#include "../../simulator/device.hpp"
#include <sabre/gpio/input_gpio.hpp>

namespace Sabre::Pilot
{
    class InputGPIO : public Sabre::InputGPIO
    {
    private:
        Device *_device;
        uint32_t _pin;

    protected:
        bool _get_level() const override;

    public:
        InputGPIO(Device *device, uint32_t pin);

        void reset() override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(ISRHandler, ISRTrigger) override;
    };
} // namespace Sabre::Pilot