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
        App() noexcept;
        App(sabre::core::Factory::UniquePtr factory) noexcept;
        App(const App &) = delete;
        App &operator=(const App &) = delete;
        App(App &&) = default;

        /**
         * @brief Virtual destructor.
         */
        virtual ~App() noexcept = default;

        void setFactory(sabre::core::Factory::UniquePtr factory) noexcept;
        const sabre::core::Factory::UniquePtr &getFactory() const noexcept;

        virtual void start() = 0;
    };

    void runApp(App &app);
} // namespace sabre::runtime