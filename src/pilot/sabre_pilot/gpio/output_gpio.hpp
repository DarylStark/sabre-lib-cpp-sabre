#pragma once

#include "../../simulator/device.hpp"
#include <sabre/hal/output_gpio.hpp>

namespace sabre::Pilot
{
    class OutputGpio : public sabre::hal::OutputGpio
    {
    private:
        Device *__device;
        uint32_t _pin;

    public:
        OutputGpio(Device *device, uint32_t pin);
        void reset() override;
        void setHigh() override;
        void setLow() override;
        void setLevel(bool level) override;
    };
} // namespace sabre::Pilot
