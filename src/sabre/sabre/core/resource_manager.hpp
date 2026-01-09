#pragma once

#include "./gpio_resource_manager.hpp"

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

    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~ResourceManager() = default;

        ResourceManager(Factory &factory, int32_t max_gpios);

        GpioResourceManager &gpio();
    };
} // namespace sabre::core