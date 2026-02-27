#include "./resource_manager.hpp"

namespace sabre::core
{
    ResourceManager::ResourceManager(
        Factory &factory, sabre::hal::PinNumber max_gpios,
        sabre::hal::UartNumber upperboundUart) noexcept
        : _gpio_manager(factory, max_gpios),
          _serial_manager(factory, upperboundUart)
    {
    }

    GpioResourceManager &ResourceManager::gpio() noexcept
    {
        return _gpio_manager;
    }

    SerialResourceManager &ResourceManager::serial() noexcept
    {
        return _serial_manager;
    }
} // namespace sabre::core