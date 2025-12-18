#include "core.hpp"
#include "hal.hpp"

namespace sabre::impl::sabre_testing
{
    StFactory::StFactory(bool uart_should_be_nullptr)
        : _uart_should_be_nullptr(uart_should_be_nullptr)
    {
    }

    Uart::UniquePtr StFactory::create_uart_object(uint32_t uart_number,
                                                  int32_t baud_rate,
                                                  int32_t tx_pin,
                                                  int32_t rx_pin,
                                                  size_t buffer_size) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_unique<TestUART>();
    }

    InputGpio::UniquePtr StFactory::create_input_gpio(int32_t pin) const
    {
        return nullptr;
    }

    OutputGpio::UniquePtr StFactory::create_output_gpio(int32_t pin) const
    {
        return nullptr;
    }

    WifiStation::UniquePtr StFactory::create_wifi_station() const
    {
        return nullptr;
    }

    WifiSoftAP::UniquePtr StFactory::create_wifi_soft_ap() const
    {
        return nullptr;
    }

    MqttClient::UniquePtr StFactory::create_mqtt_client() const
    {
        return nullptr;
    }

    WaitFor::UniquePtr StFactory::create_wait_for(WaitForPred fn,
                                                  uint64_t timeout_in_ms,
                                                  uint64_t sleep_time) const
    {
        return nullptr;
    }

    Service::UniquePtr StFactory::create_service(ServiceHandler fn) const
    {
        return nullptr;
    }

    NtpClient::UniquePtr
    StFactory::create_ntp_client(const std::string &server) const
    {
        return nullptr;
    }

    WallClock::UniquePtr StFactory::create_wall_clock() const
    {
        return nullptr;
    }

    TestApp::TestApp() : sabre::core::App() {}

    TestApp::TestApp(sabre::core::Factory::UniquePtr factory)
        : sabre::core::App(std::move(factory))
    {
    }

    void TestApp::start()
    {
        // TestApp start implementation
    }
} // namespace sabre::impl::sabre_testing