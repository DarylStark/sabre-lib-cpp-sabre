#pragma once

#include "../core/resource_manager.hpp"
#include "app.hpp"
#include <concepts>

template <typename AppType, typename... Args>
concept ValidSabreApp =
    std::derived_from<AppType, sabre::runtime::App> &&
    std::constructible_from<AppType, sabre::core::ResourceManager &, Args...>;

namespace sabre::runtime
{
    template <ValidSabreApp AppType, typename... Args>
    void RunApp(sabre::core::ResourceManager &resourceManager, Args &&...args)
    {
        auto app = AppType(resourceManager, std::forward<Args>(args)...);
        app.run();
    }
} // namespace sabre::runtime