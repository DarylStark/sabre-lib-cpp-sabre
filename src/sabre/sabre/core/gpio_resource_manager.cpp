#include "gpio_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre::core
{
    GpioResourceManager::GpioResourceManager(Factory &factory,
                                             int32_t max_gpios)
        : _factory(factory), _max_gpios(max_gpios)
    {
    }

    GpioResourceManager::GpioType
    GpioResourceManager::_pinInUse(int32_t pin) const
    {
        if (_input_gpios.find(pin) != _input_gpios.end())
            return GpioType::Input;
        if (_output_gpios.find(pin) != _output_gpios.end())
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

        if (_input_gpios.find(pin) == _input_gpios.end())
            _input_gpios.try_emplace(pin, _factory.createInputGpio(pin));

        return *_input_gpios[pin];
    }

    sabre::hal::OutputGpio &GpioResourceManager::getOutputGpio(int32_t pin)
    {
        if (_pinInUse(pin) != GpioType::Output &&
            _pinInUse(pin) != GpioType::None)
        {
            throw GpioInUseException("GPIO pin already in use as output");
        }

        if (_output_gpios.find(pin) == _output_gpios.end())
            _output_gpios.try_emplace(pin, _factory.createOutputGpio(pin));
        return *_output_gpios[pin];
    }
} // namespace sabre::core