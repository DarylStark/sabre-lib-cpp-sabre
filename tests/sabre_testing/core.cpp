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

    InputGpio::UniquePtr StFactory::createInputGpio(int32_t pin) const
    {
        return nullptr;
    }

    OutputGpio::UniquePtr StFactory::createOutputGpio(int32_t pin) const
    {
        return nullptr;
    }

    WifiStation::UniquePtr StFactory::createWifiStation() const
    {
        return nullptr;
    }

    WifiSoftAp::UniquePtr StFactory::createWifiSoftAp() const
    {
        return nullptr;
    }

    MqttClient::UniquePtr StFactory::createMqttClient() const
    {
        return nullptr;
    }

    WaitFor::UniquePtr StFactory::createWaitFor(WaitForPred fn,
                                                uint64_t timeout_in_ms,
                                                uint64_t sleep_time) const
    {
        return nullptr;
    }

    Service::UniquePtr StFactory::createService(ServiceHandler fn) const
    {
        return nullptr;
    }

    NtpClient::UniquePtr
    StFactory::createNtpClient(const std::string &server) const
    {
        return nullptr;
    }

    WallClock::UniquePtr StFactory::createWallClock() const
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