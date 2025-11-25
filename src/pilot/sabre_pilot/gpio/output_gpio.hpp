#pragma once

#include "../../simulator/device.hpp"
#include <sabre/gpio/output_gpio.hpp>

namespace sabre::pilot
{
    class OutputGPIO : public sabre::OutputGPIO
    {
    private:
        Device *__device;
        uint32_t _pin;

    public:
        OutputGPIO(Device *device, uint32_t pin);
        void reset() override;
        void set_high() override;
        void set_low() override;
        void set_level(bool level) override;
    };
} // namespace sabre::pilot
