#pragma once

#include <sabre/core/factory.hpp>
#include <sabre/runtime/app.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StFactory : public sabre::core::Factory
    {
        bool _uart_should_be_nullptr = false;

    public:
        StFactory(bool uartShouldBeNullptr = false);
        sabre::core::Uart::UniquePtr
        createUartObject(uint32_t uartNumber, int32_t baudRate, int32_t txPin,
                         int32_t rxPin, size_t bufferSize) const;
        sabre::core::InputGpio::UniquePtr createInputGpio(int32_t pin) const;
        sabre::core::OutputGpio::UniquePtr createOutputGpio(int32_t pin) const;
        sabre::core::WifiStation::UniquePtr createWifiStation() const;
        sabre::core::WifiSoftAp::UniquePtr createWifiSoftAp() const;
        sabre::core::MqttClient::UniquePtr createMqttClient() const;
        sabre::core::WaitFor::UniquePtr
        createWaitFor(sabre::core::WaitForPred fn, uint64_t timeoutInMs,
                      uint64_t sleepTime) const;
        sabre::core::Service::UniquePtr
        createService(sabre::core::ServiceHandler fn) const;

        sabre::core::NtpClient::UniquePtr
        createNtpClient(const std::string &server) const override;
        sabre::core::WallClock::UniquePtr createWallClock() const override;
    };

    class TestApp : public sabre::runtime::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_test_mocks