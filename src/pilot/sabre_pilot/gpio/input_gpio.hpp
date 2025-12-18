#pragma once

#include "../../simulator/device.hpp"
#include <sabre/hal/input_gpio.hpp>

namespace sabre::Pilot
{
    class InputGpio : public sabre::hal::InputGpio
    {
    private:
        Device *_device;
        uint32_t _pin;

    protected:
        bool _getLevel() const override;

    public:
        InputGpio(Device *device, uint32_t pin);

        void reset() override;
        void enablePullup() override;
        void enablePulldown() override;
        void disablePullup() override;
        void disablePulldown() override;
        void addInterruptHandler(sabre::hal::ISRHandler,
                                 sabre::hal::ISRTrigger) override;
    };
} // namespace sabre::Pilot