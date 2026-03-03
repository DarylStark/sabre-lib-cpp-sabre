#include "app.hpp"

namespace sabre::runtime
{
    App::App(sabre::core::ResourceManager &resourceManager) noexcept
        : _resourceManager(resourceManager)
    {
    }

    const sabre::core::ResourceManager &App::getResourceManager() const noexcept
    {
        return _resourceManager;
    }
} // namespace sabre::runtime