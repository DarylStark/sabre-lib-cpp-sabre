#include "./resource_manager.hpp"

namespace sabre::core
{
    ResourceManager::ResourceManager(
        Factory &factory, sabre::hal::PinNumber max_gpios,
        sabre::hal::UartNumber upperboundUart) noexcept
        : _factory(factory),
          _gpio_manager(factory, max_gpios, _logManager),
          _serial_manager(factory, upperboundUart, _logManager)
    {
    }

    Factory &ResourceManager::getFactory() noexcept
    {
        return _factory;
    }

    GpioResourceManager &ResourceManager::gpio() noexcept
    {
        return _gpio_manager;
    }

    SerialResourceManager &ResourceManager::serial() noexcept
    {
        return _serial_manager;
    }

    sabre::log::LogManager &ResourceManager::getLogManager()
    {
        return _logManager;
    }
} // namespace sabre::core