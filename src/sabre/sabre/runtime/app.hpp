#pragma once

#include "../core/resource_manager.hpp"

namespace sabre::runtime
{
    class App
    {
    public:
        using Ptr = App *;
        using SharedPtr = std::shared_ptr<App>;
        using UniquePtr = std::unique_ptr<App>;

    protected:
        sabre::core::ResourceManager &_resourceManager;

    public:
        App(sabre::core::ResourceManager &resourceManager) noexcept;

        /**
         * @brief Virtual destructor.
         */
        virtual ~App() noexcept = default;

        const sabre::core::ResourceManager &getResourceManager() const noexcept;

        virtual void run() = 0;
    };
} // namespace sabre::runtime