#include "core.hpp"
#include <sabre/runtime/run_app.hpp>

namespace sabre::impl::sabre_test_mocks
{
    template <ValidSabreApp AppType, typename... Args>
    void RunApp(Args &&...args)
    {
        StFactory factory;
        sabre::core::ResourceManager resourceManager(factory, 10, 20);

        sabre::runtime::RunApp<AppType>(resourceManager,
                                        std::forward<Args>(args));
    }
} // namespace sabre::impl::sabre_test_mocks