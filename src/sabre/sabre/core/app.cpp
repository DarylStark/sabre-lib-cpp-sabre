#include "app.hpp"

namespace sabre::core
{
    App::App() : _factory(nullptr) {}
    App::App(Factory::UniquePtr factory) : _factory(std::move(factory)) {}

    void App::set_factory(Factory::UniquePtr factory)
    {
        _factory = std::move(factory);
    }

    const Factory::UniquePtr &App::get_factory() const
    {
        return _factory;
    }

    void run_app(App &app)
    {
        if (!app.get_factory())
            throw std::runtime_error("Factory is not set in App.");
        app.start();
    }
} // namespace sabre::core