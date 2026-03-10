#pragma once

#include "core.hpp"
#include <sabre/runtime/run_app.hpp>

namespace sabre::impl::sabre_test_mocks
{
    template <typename AppType, typename... Args>
        requires sabre::runtime::ValidSabreApp<AppType, Args...>
    auto RunApp(Args &&...args)
    {
        StFactory factory;
        sabre::core::ResourceManager resourceManager(factory, {10, 20});

        return sabre::runtime::RunApp<AppType>(resourceManager,
                                               std::forward<Args>(args)...);
    }
} // namespace sabre::impl::sabre_test_mocks