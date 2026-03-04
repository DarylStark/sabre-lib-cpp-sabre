#pragma once

#include "../core/resource_manager.hpp"
#include "app.hpp"
#include <concepts>
#include <utility>

namespace sabre::runtime
{
    template <typename AppType, typename... Args>
    concept ValidSabreApp =
        std::constructible_from<AppType, sabre::core::ResourceManager &,
                                Args...> &&
        requires(AppType a) {
            { a.run() };
        };

    template <typename AppType, typename... Args>
        requires ValidSabreApp<AppType, Args...>
    auto RunApp(sabre::core::ResourceManager &resourceManager, Args &&...args)
    {
        AppType app(resourceManager, std::forward<Args>(args)...);
        return app.run();
    }
} // namespace sabre::runtime