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

    GpioResourceManager::GpioType
    GpioResourceManager::_pinInUse(int32_t pin) const
    {
        if (_inputGpios.find(pin) != _inputGpios.end())
            return GpioType::Input;
        if (_outputGpios.find(pin) != _outputGpios.end())
            return GpioType::Output;
        return GpioType::None;
    }

    sabre::hal::InputGpio &GpioResourceManager::getInputGpio(int32_t pin)
    {
        if (!_isValidGpio(pin))
        {
            throw GpioUnavailableException();
        }

        if (_pinInUse(pin) != GpioType::Input &&
            _pinInUse(pin) != GpioType::None)
        {
            throw GpioInUseException("GPIO pin already in use");
        }

        if (_inputGpios.find(pin) == _inputGpios.end())
            _inputGpios.try_emplace(pin, _factory.createInputGpio(pin));

        return *_inputGpios[pin];
    }

    sabre::hal::OutputGpio &GpioResourceManager::getOutputGpio(int32_t pin)
    {
        if (!_isValidGpio(pin))
        {
            throw GpioUnavailableException();
        }

        if (_pinInUse(pin) != GpioType::Output &&
            _pinInUse(pin) != GpioType::None)
        {
            throw GpioInUseException("GPIO pin already in use");
        }

        if (_outputGpios.find(pin) == _outputGpios.end())
            _outputGpios.try_emplace(pin, _factory.createOutputGpio(pin));
        return *_outputGpios[pin];
    }

    sabre::hal::Gpio &GpioResourceManager::getGpio(int32_t pin)
    {
        if (!_isValidGpio(pin))
        {
            throw GpioUnavailableException();
        }

        if (_pinInUse(pin) != GpioType::Gpio &&
            _pinInUse(pin) != GpioType::None)
        {
            throw GpioInUseException("GPIO pin already in use");
        }

        if (_gpios.find(pin) == _gpios.end())
            _gpios.try_emplace(pin, _factory.createOutputGpio(pin));
        return *_gpios[pin];
    }
} // namespace sabre::core