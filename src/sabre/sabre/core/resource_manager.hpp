#pragma once

#include "../log/logging.hpp"
#include "../time/wall_clock.hpp"
#include "./device_resource_manager.hpp"
#include "./gpio_resource_manager.hpp"
#include "./network_resource_manager.hpp"
#include "./os_resource_manager.hpp"
#include "./serial_resource_manager.hpp"
#include "./time_resource_manager.hpp"

namespace sabre::core
{
    struct ResourceManagerConfig
    {
        sabre::hal::PinNumber maxGpios = 1;
        sabre::hal::UartNumber upperboundUart = 1;
    };
    /**
     * @brief Resource manager for Sabre core resources.
     *
     * Manages resources such as GPIOs to ensure that multiple components
     * do not attempt to use the same resource at the same time.
     */
    class ResourceManager
    {
    private:
        // Configuration
        ResourceManagerConfig _config;

        // Local resources
        sabre::core::Factory &_factory;
        sabre::log::LogManager _logManager;

        // Local lazy resources
        sabre::platform::Platform::UniquePtr _platform;

        // Categorized resource managers
        GpioResourceManager _gpio_manager;
        SerialResourceManager _serial_manager;
        TimeResourceManager _time_manager;
        NetworkResourceManager _network_manager;
        OsResourceManager _os_manager;
        DeviceResourceManager _device_manager;

    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~ResourceManager() = default;

        ResourceManager(Factory &factory, ResourceManagerConfig config);

        // Local resources
        sabre::log::LogManager &getLogManager() noexcept;
        const sabre::core::Factory &getFactory() const noexcept;

        // Local lazy resources
        sabre::platform::Platform &getPlatform();

        // Categorized resource managers
        GpioResourceManager &gpio() noexcept;
        SerialResourceManager &serial() noexcept;
        TimeResourceManager &time() noexcept;
        NetworkResourceManager &network() noexcept;
        OsResourceManager &os() noexcept;
        DeviceResourceManager &devices() noexcept;
    };
} // namespace sabre::core