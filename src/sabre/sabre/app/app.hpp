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
        FactoryUniquePtr _factory;

    public:
        App();
        App(FactoryUniquePtr factory);
        App(const App &) = delete;
        App &operator=(const App &) = delete;
        App(App &&) = default;

        void set_factory(FactoryUniquePtr factory);
        const FactoryUniquePtr &get_factory() const;

        virtual ~App() = default;

        virtual void start() = 0;
    };

    void run_app(App &app);
} // namespace sabre::core