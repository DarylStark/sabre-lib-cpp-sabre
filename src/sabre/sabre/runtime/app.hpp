#pragma once

#include "../core/resource_manager.hpp"

namespace sabre::runtime
{
    template <typename ReturnType>
    class App
    {
    public:
        using Ptr = App<ReturnType> *;
        using SharedPtr = std::shared_ptr<App<ReturnType>>;
        using UniquePtr = std::unique_ptr<App<ReturnType>>;

    protected:
        sabre::core::ResourceManager &_resourceManager;

    public:
        App(sabre::core::ResourceManager &resourceManager) noexcept
            : _resourceManager(resourceManager)
        {
        }

        /**
         * @brief Virtual destructor.
         */
        virtual ~App() noexcept = default;

        const sabre::core::ResourceManager &getResourceManager() const noexcept
        {
            return _resourceManager;
        }

        virtual ReturnType run() = 0;
    };
} // namespace sabre::runtime