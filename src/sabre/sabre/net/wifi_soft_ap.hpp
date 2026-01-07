#pragma once

namespace sabre::net
{
    /**
     * @brief An interface for a Wi-Fi Soft Access Point (AP).
     *
     * This class provides methods to initialize, start, stop, and deinitialize
     * a Wi-Fi Soft AP. It is designed to be implemented by classes that provide
     * specific functionality for managing a Wi-Fi Soft AP.
     */
    class WifiSoftAp
    {
    public:
        using Ptr = WifiSoftAp *;
        using SharedPtr = std::shared_ptr<WifiSoftAp>;
        using UniquePtr = std::unique_ptr<WifiSoftAp>;

        /**
         * @brief Virtual destructor.
         */
        virtual ~WifiSoftAp() = default;

        /**
         * @brief Initialize the Wi-Fi Soft AP.
         */
        virtual void init() = 0;

        /**
         * @brief Start the Wi-Fi Soft AP with the specified SSID and password.
         *
         * @param ssid The SSID of the Wi-Fi network.
         * @param password The password for the Wi-Fi network.
         */
        virtual void start(std::string ssid, std::string password) = 0;

        /**
         * @brief Stop the Wi-Fi Soft AP.
         */
        virtual void stop() = 0;

        /**
         * @brief Deinitialize the Wi-Fi Soft AP.
         *
         * This method is called to clean up resources and stop the Soft AP.
         */
        virtual void deinitialize() = 0;
    };
}; // namespace sabre::net