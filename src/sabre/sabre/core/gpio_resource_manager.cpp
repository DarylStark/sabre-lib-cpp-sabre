#include "gpio_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre::core
{
    GpioResourceManager::GpioResourceManager(Factory &factory,
                                             int32_t max_gpios)
        : _factory(factory), _upperboundGpio(max_gpios)
    {
    }

    bool GpioResourceManager::_isValidGpio(int32_t pin) const
    {
        return pin >= 0 && pin <= _upperboundGpio;
    }

    bool GpioResourceManager::_isFreePin(int32_t pin) const
    {
        return _resources.find(pin) == _resources.end();
    }

    sabre::hal::InputGpio &GpioResourceManager::getInputGpio(int32_t pin)
    {
        if (!_isValidGpio(pin))
            throw GpioUnavailableException();

        if (_isFreePin(pin))
            _resources[pin] = _factory.createInputGpio(pin);

        auto it = _resources.find(pin);
        if (it != _resources.end() &&
            std::holds_alternative<sabre::hal::InputGpio::UniquePtr>(
                it->second))
        {
            return *std::get<sabre::hal::InputGpio::UniquePtr>(it->second);
        }

        throw GpioInUseException("GPIO pin already in use");
    }

    sabre::hal::OutputGpio &GpioResourceManager::getOutputGpio(int32_t pin)
    {
        if (!_isValidGpio(pin))
            throw GpioUnavailableException();

        if (_isFreePin(pin))
            _resources[pin] = _factory.createOutputGpio(pin);

        auto it = _resources.find(pin);
        if (it != _resources.end() &&
            std::holds_alternative<sabre::hal::OutputGpio::UniquePtr>(
                it->second))
        {
            return *std::get<sabre::hal::OutputGpio::UniquePtr>(it->second);
        }

        throw GpioInUseException("GPIO pin already in use");
    }

    sabre::hal::Gpio &GpioResourceManager::getGpio(int32_t pin)
    {
        if (!_isValidGpio(pin))
            throw GpioUnavailableException();

        if (_isFreePin(pin))
            _resources[pin] = _factory.createGpio(pin);

        auto it = _resources.find(pin);
        if (it != _resources.end() &&
            std::holds_alternative<sabre::hal::Gpio::UniquePtr>(it->second))
        {
            return *std::get<sabre::hal::Gpio::UniquePtr>(it->second);
        }

        throw GpioInUseException("GPIO pin already in use");
    }
} // namespace sabre::core