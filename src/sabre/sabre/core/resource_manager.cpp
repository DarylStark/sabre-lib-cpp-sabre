#include "./resource_manager.hpp"

namespace sabre::core
{

    ResourceManager::ResourceManager(Factory &factory,
                                     ResourceManagerConfig config)
        : _config(config), _factory(factory),
          _gpio_manager(factory, config.maxGpios, _logManager),
          _serial_manager(factory, config.upperboundUart, _logManager),
          _time_manager(factory, _logManager),
          _network_manager(factory, _logManager)
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

    TimeResourceManager &ResourceManager::time() noexcept
    {
        return _time_manager;
    }

    NetworkResourceManager &ResourceManager::network() noexcept
    {
        return _network_manager;
    }

    sabre::log::LogManager &ResourceManager::getLogManager()
    {
        return _logManager;
    }

    const sabre::core::Factory &ResourceManager::getFactory() const
    {
        return _factory;
    }
} // namespace sabre::core