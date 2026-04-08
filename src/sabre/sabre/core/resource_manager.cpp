#include "./resource_manager.hpp"

namespace sabre::core
{

    ResourceManager::ResourceManager(Factory &factory,
                                     ResourceManagerConfig config)
        : _config(config), _factory(factory),
          _gpio_manager(factory, config.maxGpios, _logManager),
          _serial_manager(factory, config.upperboundUart, _logManager),
          _time_manager(factory, _logManager),
          _network_manager(factory, _logManager),
          _os_manager(factory, _logManager),
          _device_manager(factory, _logManager)
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

    OsResourceManager &ResourceManager::os() noexcept
    {
        return _os_manager;
    }

    DeviceResourceManager &ResourceManager::devices() noexcept
    {
        return _device_manager;
    }

    sabre::log::LogManager &ResourceManager::getLogManager() noexcept
    {
        return _logManager;
    }

    const sabre::core::Factory &ResourceManager::getFactory() const noexcept
    {
        return _factory;
    }

    sabre::platform::Platform &ResourceManager::getPlatform()
    {
        if (!_platform)
        {
            _platform = _factory.createPlatform();
        }
        return *_platform;
    }
} // namespace sabre::core