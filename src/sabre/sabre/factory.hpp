#pragma once

#include "clients/mqtt.hpp"
#include "clients/ntp.hpp"
#include "gpio/input_gpio.hpp"
#include "gpio/output_gpio.hpp"
#include "service/service.hpp"
#include "system/wall_clock.hpp"
#include "uart/uart.hpp"
#include "uart/uart_output_stream_buffer.hpp"
#include "utility/wait_for.hpp"
#include "wifi/wifi_soft_ap.hpp"
#include "wifi/wifi_station.hpp"

#include <memory>
#include <ostream>

namespace sabre::core
{
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
        virtual UARTUniquePtr create_uart_object(uint32_t uart_number,
                                                 int32_t baud_rate,
                                                 int32_t tx_pin, int32_t rx_pin,
                                                 size_t buffer_size) const = 0;

        /**
         * @brief Create a `UARTStreamBuf` object.
         *
         * @param uart_number the UART number to configure the object with.
         * @param baud_rate the baud rate for the serial interface.
         * @param tx_pin transmit pin.
         * @param rx_pin receive pin.
         * @param buffer_size the size of the buffer in bytes.
         *
         * @return A `UARTStreamBufUniquePtr` unique pointer to a
         * `UARTStreamBuf` object.
         */
        virtual UARTStreamBufUniquePtr create_uart_output_stream_buffer(
            uint32_t uart_number, int32_t baud_rate, int32_t tx_pin,
            int32_t rx_pin, size_t buffer_size) const;

        /**
         * @brief Create a `InputGPIO` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `InputGPIOUniquePtr` unique pointer to a `InputGPIO`
         * object.
         */
        virtual InputGPIOUniquePtr create_input_gpio(int32_t pin) const = 0;

        /**
         * @brief Create a `OutputGPIO` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `OutputGPIOUniquePtr` unique pointer to a `OutputGPIO`
         * object.
         */
        virtual OutputGPIOUniquePtr create_output_gpio(int32_t pin) const = 0;

        /**
         * @brief Create a `WifiStation` object.
         *
         * @return A `WifiStationUniquePtr` unique pointer to a `WifiStation`
         * object.
         */
        virtual WifiStationUniquePtr create_wifi_station() const = 0;

        /**
         * @brief Create a `WifiSoftAP` object.
         *
         * @return A `WifiSoftAPUniquePtr` unique pointer to a `WifiSoftAP`
         * object.
         */
        virtual WifiSoftAPUniquePtr create_wifi_soft_ap() const = 0;

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
        virtual WallClockUniquePtr create_wall_clock() const = 0;

        /**
         * @brief Create a `NTPClient` object.
         *
         * @param server the NTP server address to synchronize with.
         *
         * @return A `NTPClientUniquePtr` unique pointer to a `NTPClient`
         * object.
         */
        virtual NTPClientUniquePtr
        create_ntp_client(const std::string &server) const = 0;

        virtual MQTTClientUniquePtr create_mqtt_client() const = 0;

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
        virtual WaitForUniquePtr create_wait_for(WaitForPred fn,
                                                 uint64_t timeout_in_ms,
                                                 uint64_t sleep_time) const = 0;

        /**
         * @brief Create a `Service` object.
         *
         * @param fn the function to run as the service.
         *
         * @return A `ServiceUniquePtr` unique pointer to a `Service`
         * object.
         */
        virtual ServiceUniquePtr create_service(ServiceHandler fn) const = 0;
    };
} // namespace sabre::core