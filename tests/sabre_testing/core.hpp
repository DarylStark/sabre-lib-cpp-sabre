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
        InputGpio::UniquePtr create_input_gpio(int32_t pin) const;
        OutputGpio::UniquePtr create_output_gpio(int32_t pin) const;
        WifiStation::UniquePtr create_wifi_station() const;
        WifiSoftAP::UniquePtr create_wifi_soft_ap() const;
        MqttClient::UniquePtr create_mqtt_client() const;
        WaitFor::UniquePtr create_wait_for(WaitForPred fn,
                                           uint64_t timeout_in_ms,
                                           uint64_t sleep_time) const;
        Service::UniquePtr create_service(ServiceHandler fn) const;

        NtpClient::UniquePtr
        create_ntp_client(const std::string &server) const override;
        WallClock::UniquePtr create_wall_clock() const override;
    };

    class TestApp : public sabre::core::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_testing