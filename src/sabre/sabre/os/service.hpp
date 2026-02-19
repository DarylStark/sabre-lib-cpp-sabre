#pragma once

#include <functional>
#include <memory>

namespace sabre::os
{
    using ServiceHandler = std::function<void(void)>;

    /**
     * @brief Abstract base class for services in the Sabre framework.
     *
     * This class defines the interface for services, which are components that
     * can be started and stopped. Services can perform various tasks and are
     * managed by the Sabre framework.
     *
     * A implementation defines how a service is started and stopped, allowing
     * for flexible service management within the framework.
     */
    class Service
    {
    public:
        using Ptr = Service *;
        using SharedPtr = std::shared_ptr<Service>;
        using UniquePtr = std::unique_ptr<Service>;

    protected:
        ServiceHandler _fn;

    public:
        /**
         * @brief Constructor for the Service class.
         *
         * This constructor initializes the service with a handler function that
         * will be called when the service is started.
         *
         * @param function The function to be called when the service starts.
         */
        Service(const ServiceHandler &function) noexcept;

        /**
         * @brief Virtual destructor.
         */
        virtual ~Service() noexcept = default;

        /**
         * @brief Start the service.
         */
        virtual void start() = 0;

        /**
         * @brief Stop the service.
         *
         * This method is called to stop the service gracefully, allowing it to
         * clean up resources and perform any necessary shutdown operations.
         */
        virtual void stop() = 0;
    };
} // namespace sabre::os