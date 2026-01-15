#include "./resource_manager.hpp"

namespace sabre::core
{
    ResourceManager::ResourceManager(Factory &factory, int32_t max_gpios,
                                     uint32_t upperboundUart)
        : _gpio_manager(factory, max_gpios),
          _serial_manager(factory, upperboundUart)
    {
    }

    GpioResourceManager &ResourceManager::gpio()
    {
        return _gpio_manager;
    }

    SerialResourceManager &ResourceManager::serial()
    {
        return _serial_manager;
    }
} // namespace sabre::core