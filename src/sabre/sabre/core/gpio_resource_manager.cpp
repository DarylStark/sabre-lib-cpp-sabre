#include "gpio_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre::core
{
    GpioResourceManager::GpioResourceManager(
        Factory &factory, sabre::hal::PinNumber max_gpios,
        sabre::log::LogManager &logManager) noexcept
        : _logManager(logManager), _factory(factory), _upperboundGpio(max_gpios)
    {
    }

    bool
    GpioResourceManager::_isValidGpio(sabre::hal::PinNumber pin) const noexcept
    {
        return pin >= 0 && pin <= _upperboundGpio;
    }

    bool
    GpioResourceManager::_isFreePin(sabre::hal::PinNumber pin) const noexcept
    {
        return _resources.find(pin) == _resources.end();
    }

    template <typename T>
    bool GpioResourceManager::_isType(sabre::hal::PinNumber pin) const
    {
        auto it = _resources.find(pin);
        return it != _resources.end() && std::holds_alternative<T>(it->second);
    }

    template <typename T, typename FactoryFunc>
    T &GpioResourceManager::_getOrCreateGpio(sabre::hal::PinNumber pin,
                                             FactoryFunc factoryFunc)
    {
        using UniquePtrType = typename T::UniquePtr;

        if (!_isValidGpio(pin))
            throw GpioUnavailableException();

        if (_isFreePin(pin))
        {
            _resources[pin] = factoryFunc(pin);
        }

        if (_isType<UniquePtrType>(pin))
        {
            auto it = _resources.find(pin);
            return *std::get<UniquePtrType>(it->second);
        }

        throw GpioInUseException("GPIO pin already in use");
    }

    sabre::hal::InputGpio &
    GpioResourceManager::getInputGpio(sabre::hal::PinNumber pin)
    {
        return _getOrCreateGpio<sabre::hal::InputGpio>(
            pin,
            [this](sabre::hal::PinNumber p)
            {
                sabre::hal::InputGpio::UniquePtr gpio =
                    _factory.createInputGpio(p);
                gpio->getLogHelper().createLogger(
                    _logManager, "InputGpio_" + std::to_string(p));
                return gpio;
            });
    }

    sabre::hal::OutputGpio &
    GpioResourceManager::getOutputGpio(sabre::hal::PinNumber pin)
    {
        return _getOrCreateGpio<sabre::hal::OutputGpio>(
            pin,
            [this](sabre::hal::PinNumber p)
            {
                sabre::hal::OutputGpio::UniquePtr gpio =
                    _factory.createOutputGpio(p);
                gpio->getLogHelper().createLogger(
                    _logManager, "InputGpio_" + std::to_string(p));
                return gpio;
            });
    }

    sabre::hal::Gpio &GpioResourceManager::getGpio(sabre::hal::PinNumber pin)
    {
        return _getOrCreateGpio<sabre::hal::Gpio>(
            pin,
            [this](sabre::hal::PinNumber p)
            {
                sabre::hal::Gpio::UniquePtr gpio = _factory.createGpio(p);
                gpio->getLogHelper().createLogger(
                    _logManager, "InputGpio_" + std::to_string(p));
                return gpio;
            });
    }
} // namespace sabre::core