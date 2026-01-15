#pragma once

#include "../hal/input_gpio.hpp"
#include "../hal/output_gpio.hpp"
#include "../hal/serial.hpp"
#include "../io/serial_output_stream_buffer.hpp"
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
    using sabre::hal::Serial;
    using sabre::net::MqttClient;
    using sabre::net::WifiSoftAp;
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
         * @brief Virtual destructor.
         */
        virtual ~Factory() = default;

        /**
         * @brief Create a `Serial` object for UART communication.
         *
         * @param uartNumber the UART number to configure the object with.
         * @param baudRate the baud rate for the serial interface.
         * @param txPin transmit pin.
         * @param rxPin receive pin.
         * @param bufferSize the size of the input buffer in bytes. The
         * specific implementation may choose to use this value to allocate
         * internal buffers. If the hardware does not support input buffering,
         * this value may be ignored.
         *
         * @return A `Serial::UniquePtr` unique pointer to a `Serial` object.
         */
        virtual Serial::UniquePtr createUartObject(uint32_t uartNumber,
                                                   int32_t baudRate,
                                                   int32_t txPin, int32_t rxPin,
                                                   size_t bufferSize) const = 0;

        /**
         * @brief Create a `Serial` object for USB CDC communication.
         *
         * @param index the USB CDC index to configure the object with.
         *
         * @param bufferSize the size of the input buffer in bytes. The
         * specific implementation may choose to use this value to allocate
         * internal buffers. If the hardware does not support input buffering,
         * this value may be ignored.
         *
         * @return A `Serial::UniquePtr` unique pointer to a `Serial` object.
         */
        virtual Serial::UniquePtr createUsbCdc(uint32_t index,
                                               size_t bufferSize) const = 0;

        /**
         * @brief Create a `InputGpio` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `InputGpio::UniquePtr` unique pointer to a `InputGpio`
         * object.
         */
        virtual InputGpio::UniquePtr createInputGpio(int32_t pin) const = 0;

        /**
         * @brief Create a `OutputGpio` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `OutputGpioUniquePtr` unique pointer to a `OutputGpio`
         * object.
         */
        virtual OutputGpio::UniquePtr createOutputGpio(int32_t pin) const = 0;

        /**
         * @brief Create a `Gpio` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @return A `GpioUniquePtr` unique pointer to a `Gpio`
         * object.
         */
        virtual sabre::hal::Gpio::UniquePtr createGpio(int32_t pin) const = 0;

        /**
         * @brief Create a `WifiStation` object.
         *
         * @return A `WifiStationUniquePtr` unique pointer to a `WifiStation`
         * object.
         */
        virtual WifiStation::UniquePtr createWifiStation() const = 0;

        /**
         * @brief Create a `WifiSoftAP` object.
         *
         * @return A `WifiSoftAPUniquePtr` unique pointer to a `WifiSoftAP`
         * object.
         */
        virtual WifiSoftAp::UniquePtr createWifiSoftAp() const = 0;

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
        virtual WallClock::UniquePtr createWallClock() const = 0;

        /**
         * @brief Create a `NTPClient` object.
         *
         * @param server the NTP server address to synchronize with.
         *
         * @return A `NTPClientUniquePtr` unique pointer to a `NTPClient`
         * object.
         */
        virtual NtpClient::UniquePtr
        createNtpClient(const std::string &server) const = 0;

        virtual MqttClient::UniquePtr createMqttClient() const = 0;

        /**
         * @brief Create a `WaitFor` object.
         *
         * @param fn the function to run in the WaitFor.
         * @param timeoutInMs the maximum runtime in ms of the function.
         * @param sleepTime how much time (in ms) to sleep between each
         * iteration.
         *
         * @return A `WaitForUniquePtr` unique pointer to a `WaitFor`
         * object.
         */
        virtual WaitFor::UniquePtr createWaitFor(WaitForPred fn,
                                                 uint64_t timeoutInMs,
                                                 uint64_t sleepTime) const = 0;

        /**
         * @brief Create a `Service` object.
         *
         * @param fn the function to run as the service.
         *
         * @return A `ServiceUniquePtr` unique pointer to a `Service`
         * object.
         */
        virtual Service::UniquePtr createService(ServiceHandler fn) const = 0;
    };
} // namespace sabre::core