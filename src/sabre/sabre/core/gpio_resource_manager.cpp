#include "gpio_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre::core
{
    GpioResourceManager::GpioResourceManager(Factory &factory,
                                             int32_t max_gpios) noexcept
        : _factory(factory), _upperboundGpio(max_gpios)
    {
    }

    bool GpioResourceManager::_isValidGpio(int32_t pin) const noexcept
    {
        return pin >= 0 && pin <= _upperboundGpio;
    }

    bool GpioResourceManager::_isFreePin(int32_t pin) const noexcept
    {
        return _resources.find(pin) == _resources.end();
    }

    template <typename T>
    bool GpioResourceManager::_isType(int32_t pin) const
    {
        auto it = _resources.find(pin);
        return it != _resources.end() && std::holds_alternative<T>(it->second);
    }

    template <typename T, typename FactoryFunc>
    T &GpioResourceManager::_getOrCreateGpio(int32_t pin,
                                             FactoryFunc factoryFunc)
    {
        using UniquePtrType = typename T::UniquePtr;

        if (!_isValidGpio(pin))
            throw GpioUnavailableException();

        if (_isFreePin(pin))
            _resources[pin] = factoryFunc(pin);

        if (_isType<UniquePtrType>(pin))
        {
            auto it = _resources.find(pin);
            return *std::get<UniquePtrType>(it->second);
        }

        throw GpioInUseException("GPIO pin already in use");
    }

    sabre::hal::InputGpio &GpioResourceManager::getInputGpio(int32_t pin)
    {
        return _getOrCreateGpio<sabre::hal::InputGpio>(
            pin, [this](int32_t p) { return _factory.createInputGpio(p); });
    }

    sabre::hal::OutputGpio &GpioResourceManager::getOutputGpio(int32_t pin)
    {
        return _getOrCreateGpio<sabre::hal::OutputGpio>(
            pin, [this](int32_t p) { return _factory.createOutputGpio(p); });
    }

    sabre::hal::Gpio &GpioResourceManager::getGpio(int32_t pin)
    {
        return _getOrCreateGpio<sabre::hal::Gpio>(
            pin, [this](int32_t p) { return _factory.createGpio(p); });
    }
} // namespace sabre::core