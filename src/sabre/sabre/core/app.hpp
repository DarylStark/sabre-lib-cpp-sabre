#pragma once

#include "../factory.hpp"

namespace sabre::core
{

    class App
    {
    public:
        using Ptr = App *;
        using SharedPtr = std::shared_ptr<App>;
        using UniquePtr = std::unique_ptr<App>;

    protected:
        Factory::UniquePtr _factory;

    public:
        App();
        App(Factory::UniquePtr factory);
        App(const App &) = delete;
        App &operator=(const App &) = delete;
        App(App &&) = default;

        void set_factory(Factory::UniquePtr factory);
        const Factory::UniquePtr &get_factory() const;

        virtual ~App() = default;

        virtual void start() = 0;
    };

    void run_app(App &app);
} // namespace sabre::core