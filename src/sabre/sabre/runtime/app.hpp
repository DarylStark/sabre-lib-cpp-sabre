#pragma once

#include "../core/factory.hpp"

namespace sabre::runtime
{

    class App
    {
    public:
        using Ptr = App *;
        using SharedPtr = std::shared_ptr<App>;
        using UniquePtr = std::unique_ptr<App>;

    protected:
        sabre::core::Factory::UniquePtr _factory;

    public:
        App();
        App(sabre::core::Factory::UniquePtr factory);
        App(const App &) = delete;
        App &operator=(const App &) = delete;
        App(App &&) = default;

        void setFactory(sabre::core::Factory::UniquePtr factory);
        const sabre::core::Factory::UniquePtr &getFactory() const;

        virtual ~App() = default;

        virtual void start() = 0;
    };

    void runApp(App &app);
} // namespace sabre::runtime