#include "app.hpp"

namespace sabre::core
{
    App::App() : _factory(nullptr) {}
    App::App(Factory::UniquePtr factory) : _factory(std::move(factory)) {}

    void App::setFactory(Factory::UniquePtr factory)
    {
        _factory = std::move(factory);
    }

    const Factory::UniquePtr &App::getFactory() const
    {
        return _factory;
    }

    void runApp(App &app)
    {
        if (!app.getFactory())
            throw std::runtime_error("Factory is not set in App.");
        app.start();
    }
} // namespace sabre::core