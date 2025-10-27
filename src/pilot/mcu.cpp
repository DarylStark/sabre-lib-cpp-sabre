#include "mcu.hpp"
#include "sabre_pilot/factory.hpp"
#include <iostream>

namespace sabre::pilot
{
    MCU::MCU(MCUConfig config, sabre::AppUniquePtr &&app)
        : _config(config), _app(std::move(app)), _gpios(config.gpio_count)
    {
    }

    void MCU::start()
    {
        std::cout << "GPIO Size: " << _config.gpio_count << std::endl;
        // TODO: Custom exception
        if (_app->get_factory())
            throw std::runtime_error("Factory is already set in App.");
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
} // namespace sabre::pilot
