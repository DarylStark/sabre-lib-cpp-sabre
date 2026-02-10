#pragma once

#include <sabre/core/factory.hpp>
#include <sabre/hal/gpio.hpp>
#include <sabre/runtime/app.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StFactory : public sabre::core::Factory
    {
        bool _uart_should_be_nullptr = false;

    public:
        StFactory(bool uartShouldBeNullptr = false);
        sabre::hal::Serial::UniquePtr
        createUartObject(uint32_t uartNumber, int32_t baudRate, int32_t txPin,
                         int32_t rxPin, size_t bufferSize) const;
        sabre::hal::Serial::UniquePtr createUsbCdc(uint32_t index,
                                                    size_t bufferSize) const;
        sabre::hal::InputGpio::UniquePtr createInputGpio(int32_t pin) const;
        sabre::hal::OutputGpio::UniquePtr createOutputGpio(int32_t pin) const;
        sabre::hal::Gpio::UniquePtr createGpio(int32_t pin) const;
        sabre::net::WifiStation::UniquePtr createWifiStation() const;
        sabre::net::WifiSoftAp::UniquePtr createWifiSoftAp() const;
        sabre::net::MqttClient::UniquePtr createMqttClient() const;
        sabre::utility::WaitFor::UniquePtr
        createWaitFor(sabre::utility::WaitForPred fn, uint64_t timeoutInMs,
                      uint64_t sleepTime) const;
        sabre::os::Service::UniquePtr
        createService(sabre::os::ServiceHandler fn) const;

        sabre::time::NtpClient::UniquePtr
        createNtpClient(const std::string &server) const override;
        sabre::time::WallClock::UniquePtr createWallClock() const override;
    };

    class TestApp : public sabre::runtime::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_test_mocks