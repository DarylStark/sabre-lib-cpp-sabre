#include "gpio_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre::core
{
    GpioResourceManager::GpioResourceManager(Factory &factory,
                                             int32_t max_gpios)
        : _factory(factory), _upperboundGpio(max_gpios)
    {
    }

    GpioResourceManager::GpioType
    GpioResourceManager::_pinInUse(int32_t pin) const
    {
        if (pin < 0 || pin > _upperboundGpio)
            throw GpioUnavailableException();

        if (_inputGpios.find(pin) != _inputGpios.end())
            return GpioType::Input;
        if (_outputGpios.find(pin) != _outputGpios.end())
            return GpioType::Output;
        return GpioType::None;
    }

    sabre::hal::InputGpio &GpioResourceManager::getInputGpio(int32_t pin)
    {
        if (_pinInUse(pin) != GpioType::Input &&
            _pinInUse(pin) != GpioType::None)
        {
            throw GpioInUseException("GPIO pin already in use as output");
        }

        if (_inputGpios.find(pin) == _inputGpios.end())
            _inputGpios.try_emplace(pin, _factory.createInputGpio(pin));

        return *_inputGpios[pin];
    }

    sabre::hal::OutputGpio &GpioResourceManager::getOutputGpio(int32_t pin)
    {
        if (_pinInUse(pin) != GpioType::Output &&
            _pinInUse(pin) != GpioType::None)
        {
            throw GpioInUseException("GPIO pin already in use as input");
        }

        if (_outputGpios.find(pin) == _outputGpios.end())
            _outputGpios.try_emplace(pin, _factory.createOutputGpio(pin));
        return *_outputGpios[pin];
    }
} // namespace sabre::core