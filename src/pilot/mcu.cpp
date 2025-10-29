#include "mcu.hpp"
#include "sabre_pilot/factory.hpp"
#include <iostream>

namespace sabre::pilot
{
    MCU::MCU(MCUConfig config, sabre::AppUniquePtr &&app)
        : _config(config), _app(std::move(app)), _gpios(config.gpio_count)
    {
        uint32_t gpio_index = 0;
        for (auto &gpio : _gpios)
            gpio.number = gpio_index++;
        asm("nop");
    }

    void MCU::start()
    {
        _app->set_factory(std::make_unique<Factory>(this));
        _app->start();
    }

    MCUGPIO &MCU::get_gpio(size_t index)
    {
        if (index >= _gpios.size())
            throw std::out_of_range("GPIO index out of range");
        return _gpios[index];
    }

    void MCU::set_gpio_type(size_t index, GPIOType type)
    {
        get_gpio(index).type = type;
    }

    void MCU::reset_gpio(size_t index)
    {
        auto &gpio = get_gpio(index);
        gpio.type = GPIOType::GENERIC;
        gpio.state = 0;
    }

    void MCU::set_gpio_state(size_t index, uint32_t state)
    {
        get_gpio(index).state = state;
        // TODO: Call ISR if this is a Input GPIO
    }

    GPIOVector MCU::get_gpios(GPIOType type) const
    {
        GPIOVector gpios;
        std::copy_if(_gpios.begin(), _gpios.end(), std::back_inserter(gpios),
                     [&type](MCUGPIO gpio) { return gpio.type == type; });
        return gpios;
    }
} // namespace sabre::pilot
