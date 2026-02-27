#pragma once

#include "./gpio_resource_manager.hpp"
#include "./serial_resource_manager.hpp"

namespace sabre::core
{
    /**
     * @brief Resource manager for Sabre core resources.
     *
     * Manages resources such as GPIOs to ensure that multiple components
     * do not attempt to use the same resource at the same time.
     */
    class ResourceManager
    {
    private:
        GpioResourceManager _gpio_manager;
        SerialResourceManager _serial_manager;

    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~ResourceManager() = default;

        ResourceManager(Factory &factory, sabre::hal::PinNumber max_gpios,
                        sabre::hal::UartNumber upperboundUart) noexcept;

        GpioResourceManager &gpio() noexcept;
        SerialResourceManager &serial() noexcept;
    };
} // namespace sabre::core