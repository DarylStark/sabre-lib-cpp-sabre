#include "./resource_manager.hpp"

namespace sabre::core
{
    ResourceManager::ResourceManager(Factory &factory, int32_t max_gpios)
        : _gpio_manager(factory, max_gpios)
    {
    }

    GpioResourceManager &ResourceManager::gpio()
    {
        return _gpio_manager;
    }
} // namespace sabre::core