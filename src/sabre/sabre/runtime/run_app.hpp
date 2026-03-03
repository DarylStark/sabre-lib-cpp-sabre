#pragma once

#include "../core/resource_manager.hpp"
#include <concepts>

template <typename AppType, typename... Args>
concept ValidSabreApp =
    std::derived_from<AppType, App> &&
    std::constructible_from<AppType, sabre::core::ResourceManager &, Args...>;

namespace sabre::runtime
{
    template <ValidSabreApp AppType, typename FactoryType>
    void RunApp(Args &&...args)
    {
        FactoryType factory;
        sabre::core::ResourceManager resourceManager(factory, 10, 2);
        auto app = AppType(resourceManager);
        app(std::forward<Args>(args)...);
    }
} // namespace sabre::runtime