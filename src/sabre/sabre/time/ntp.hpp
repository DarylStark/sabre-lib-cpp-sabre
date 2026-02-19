#pragma once

#include <memory>

namespace sabre::time
{
    class NtpClient
    {
    public:
        using Ptr = NtpClient *;
        using SharedPtr = std::shared_ptr<NtpClient>;
        using UniquePtr = std::unique_ptr<NtpClient>;

        /**
         * @brief Virtual destructor.
         */
        virtual ~NtpClient() noexcept = default;

        /**
         * @brief Starts the NTP client.
         *
         * This will initialize the NTP client and start synchronizing time
         * with the specified NTP server.
         */
        virtual void start() = 0;

        /**
         * @brief Stops the NTP client.
         *
         * This will stop the NTP client and cease time synchronization.
         */
        virtual void stop() = 0;

        /**
         * @brief Checks if the NTP client is synchronized.
         *
         * @returns true if the NTP client is synchronized, false otherwise.
         */
        virtual bool isSynchronized() const noexcept = 0;
    };
} // namespace sabre::time