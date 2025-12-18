#pragma once

#include <sabre/core/app.hpp>
#include <sabre/core/factory.hpp>

namespace sabre::impl::sabre_testing
{
    using namespace sabre::core;

    class StFactory : public sabre::core::Factory
    {
        bool _uart_should_be_nullptr = false;

    public:
        StFactory(bool uart_should_be_nullptr = false);
        Uart::UniquePtr create_uart_object(uint32_t uart_number,
                                           int32_t baud_rate, int32_t tx_pin,
                                           int32_t rx_pin,
                                           size_t buffer_size) const;
        InputGpio::UniquePtr createInputGpio(int32_t pin) const;
        OutputGpio::UniquePtr createOutputGpio(int32_t pin) const;
        WifiStation::UniquePtr createWifiStation() const;
        WifiSoftAp::UniquePtr createWifiSoftAp() const;
        MqttClient::UniquePtr createMqttClient() const;
        WaitFor::UniquePtr createWaitFor(WaitForPred fn, uint64_t timeout_in_ms,
                                         uint64_t sleep_time) const;
        Service::UniquePtr createService(ServiceHandler fn) const;

        NtpClient::UniquePtr
        createNtpClient(const std::string &server) const override;
        WallClock::UniquePtr createWallClock() const override;
    };

    class TestApp : public sabre::core::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_testing