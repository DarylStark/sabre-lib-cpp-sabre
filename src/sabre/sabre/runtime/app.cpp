#include "app.hpp"

namespace sabre::runtime
{
    App::App() : _factory(nullptr) {}
    App::App(sabre::core::Factory::UniquePtr factory)
        : _factory(std::move(factory))
    {
    }

    void App::setFactory(sabre::core::Factory::UniquePtr factory)
    {
        _factory = std::move(factory);
    }

    const sabre::core::Factory::UniquePtr &App::getFactory() const
    {
        return _factory;
    }

    void runApp(App &app)
    {
        if (!app.getFactory())
            throw std::runtime_error("Factory is not set in App.");
        app.start();
    }
} // namespace sabre::runtime