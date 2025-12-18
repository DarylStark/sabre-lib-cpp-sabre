#include "app.hpp"

namespace sabre::impl::sabre_testing
{
    TestApp::TestApp() : sabre::core::App() {}

    TestApp::TestApp(sabre::core::Factory::UniquePtr factory)
        : sabre::core::App(std::move(factory))
    {
    }

    void TestApp::start()
    {
        // TestApp start implementation
    }
} // namespace sabre::impl::sabre_testing