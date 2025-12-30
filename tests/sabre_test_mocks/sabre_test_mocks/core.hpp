#pragma once

#include <sabre/core/factory.hpp>
#include <sabre/runtime/app.hpp>

namespace sabre::impl::sabre_test_mocks
{
    using namespace sabre::core;

    class StFactory : public sabre::core::Factory
    {
        bool _uart_should_be_nullptr = false;

    public:
        StFactory(bool uartShouldBeNullptr = false);
        Uart::UniquePtr createUartObject(uint32_t uartNumber, int32_t baudRate,
                                         int32_t txPin, int32_t rxPin,
                                         size_t bufferSize) const;
        InputGpio::UniquePtr createInputGpio(int32_t pin) const;
        OutputGpio::UniquePtr createOutputGpio(int32_t pin) const;
        WifiStation::UniquePtr createWifiStation() const;
        WifiSoftAp::UniquePtr createWifiSoftAp() const;
        MqttClient::UniquePtr createMqttClient() const;
        WaitFor::UniquePtr createWaitFor(WaitForPred fn, uint64_t timeoutInMs,
                                         uint64_t sleepTime) const;
        Service::UniquePtr createService(ServiceHandler fn) const;

        NtpClient::UniquePtr
        createNtpClient(const std::string &server) const override;
        WallClock::UniquePtr createWallClock() const override;
    };

    class TestApp : public sabre::runtime::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_test_mocks