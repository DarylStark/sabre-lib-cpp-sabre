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
                         int32_t rxPin,
                         size_t bufferSize) const noexcept override;
        sabre::hal::Serial::UniquePtr
        createUsbCdc(uint32_t index, size_t bufferSize) const noexcept override;
        sabre::hal::InputGpio::UniquePtr
        createInputGpio(int32_t pin) const noexcept override;
        sabre::hal::OutputGpio::UniquePtr
        createOutputGpio(int32_t pin) const noexcept override;
        sabre::hal::Gpio::UniquePtr
        createGpio(int32_t pin) const noexcept override;
        sabre::net::WifiStation::UniquePtr
        createWifiStation() const noexcept override;
        sabre::net::WifiSoftAp::UniquePtr
        createWifiSoftAp() const noexcept override;
        sabre::net::MqttClient::UniquePtr
        createMqttClient() const noexcept override;
        sabre::utility::WaitFor::UniquePtr
        createWaitFor(sabre::utility::WaitForPred fn, uint64_t timeoutInMs,
                      uint64_t sleepTime) const noexcept override;
        sabre::os::Service::UniquePtr
        createService(sabre::os::ServiceHandler fn) const noexcept override;

        sabre::time::NtpClient::UniquePtr
        createNtpClient(const std::string &server) const noexcept override;
        sabre::time::WallClock::UniquePtr
        createWallClock() const noexcept override;
    };

    class TestApp : public sabre::runtime::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_test_mocks