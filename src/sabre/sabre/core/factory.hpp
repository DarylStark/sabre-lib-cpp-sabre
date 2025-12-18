#pragma once

#include "../hal/input_gpio.hpp"
#include "../hal/output_gpio.hpp"
#include "../hal/uart.hpp"
#include "../io/uart_output_stream_buffer.hpp"
#include "../net/mqtt.hpp"
#include "../net/wifi_soft_ap.hpp"
#include "../net/wifi_station.hpp"
#include "../os/service.hpp"
#include "../time/ntp.hpp"
#include "../time/wall_clock.hpp"
#include "../utility/wait_for.hpp"

#include <memory>
#include <ostream>

namespace sabre::core
{
    using sabre::hal::InputGpio;
    using sabre::hal::OutputGpio;
    using sabre::hal::Uart;
    using sabre::net::MqttClient;
    using sabre::net::WifiSoftAP;
    using sabre::net::WifiStation;
    using sabre::os::Service;
    using sabre::os::ServiceHandler;
    using sabre::time::NtpClient;
    using sabre::time::WallClock;
    using sabre::utility::WaitFor;
    using sabre::utility::WaitForPred;

    /**
     * @brief Abstract factory for object creation.
     *
     * Creates objects for a specific implementation. The methods of
     * this factory return shared pointers to the real implemented objects. This
     * should be overriden by implementations to return the correct object
     * for the specific implementation.
     */
    class Factory
    {
    public:
        using Ptr = Factory *;
        using SharedPtr = std::shared_ptr<Factory>;
        using UniquePtr = std::unique_ptr<Factory>;
        /**
         * @brief Create a `UART` object.
         *
         * @param uart_number the UART number to configure the object with.
         * @param baud_rate the baud rate for the serial interface.
         * @param tx_pin transmit pin.
         * @param rx_pin receive pin.
         * @param buffer_size the size of the input buffer in bytes. The
         * specific implementation may choose to use this value to allocate
         * internal buffers. If the hardware does not support input buffering,
         * this value may be ignored.
         *
         * @return A `UARTUniquePtr` unique pointer to a `UART` object.
         */
        virtual Uart::UniquePtr
        create_uart_object(uint32_t uart_number, int32_t baud_rate,
                           int32_t tx_pin, int32_t rx_pin,
                           size_t buffer_size) const = 0;

        /**
         * @brief Create a `InputGpio` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `InputGpio::UniquePtr` unique pointer to a `InputGpio`
         * object.
         */
        virtual InputGpio::UniquePtr create_input_gpio(int32_t pin) const = 0;

        /**
         * @brief Create a `OutputGpio` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `OutputGpioUniquePtr` unique pointer to a `OutputGpio`
         * object.
         */
        virtual OutputGpio::UniquePtr create_output_gpio(int32_t pin) const = 0;

        /**
         * @brief Create a `WifiStation` object.
         *
         * @return A `WifiStationUniquePtr` unique pointer to a `WifiStation`
         * object.
         */
        virtual WifiStation::UniquePtr create_wifi_station() const = 0;

        /**
         * @brief Create a `WifiSoftAP` object.
         *
         * @return A `WifiSoftAPUniquePtr` unique pointer to a `WifiSoftAP`
         * object.
         */
        virtual WifiSoftAP::UniquePtr create_wifi_soft_ap() const = 0;

        /**
         * @brief Create a `MQTTClient` object.
         *
         * @return A `MQTTClientUniquePtr` unique pointer to a `MQTTClient`
         * object.
         */

        /**
         * @brief Create a `WallClock` object.
         *
         * @return A `WallClockUniquePtr` unique pointer to a `WallClock`
         * object.
         */
        virtual WallClock::UniquePtr create_wall_clock() const = 0;

        /**
         * @brief Create a `NTPClient` object.
         *
         * @param server the NTP server address to synchronize with.
         *
         * @return A `NTPClientUniquePtr` unique pointer to a `NTPClient`
         * object.
         */
        virtual NtpClient::UniquePtr
        create_ntp_client(const std::string &server) const = 0;

        virtual MqttClient::UniquePtr create_mqtt_client() const = 0;

        /**
         * @brief Create a `WaitFor` object.
         *
         * @param fn the function to run in the WaitFor.
         * @param timeout_in_ms the maximum runtime in ms of the function.
         * @param sleep_time how much time (in ms) to sleep between each
         * iteration.
         *
         * @return A `WaitForUniquePtr` unique pointer to a `WaitFor`
         * object.
         */
        virtual WaitFor::UniquePtr
        create_wait_for(WaitForPred fn, uint64_t timeout_in_ms,
                        uint64_t sleep_time) const = 0;

        /**
         * @brief Create a `Service` object.
         *
         * @param fn the function to run as the service.
         *
         * @return A `ServiceUniquePtr` unique pointer to a `Service`
         * object.
         */
        virtual Service::UniquePtr create_service(ServiceHandler fn) const = 0;
    };
} // namespace sabre::core