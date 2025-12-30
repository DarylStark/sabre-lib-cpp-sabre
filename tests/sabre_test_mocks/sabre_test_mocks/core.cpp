#include "core.hpp"
#include "hal.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StFactory::StFactory(bool uartShouldBeNullptr)
        : _uart_should_be_nullptr(uartShouldBeNullptr)
    {
    }

    Uart::UniquePtr StFactory::createUartObject(uint32_t uartNumber,
                                                int32_t baudRate, int32_t txPin,
                                                int32_t rxPin,
                                                size_t bufferSize) const
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
                                                uint64_t timeoutInMs,
                                                uint64_t sleepTime) const
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

    TestApp::TestApp() : sabre::runtime::App() {}

    TestApp::TestApp(sabre::core::Factory::UniquePtr factory)
        : sabre::runtime::App(std::move(factory))
    {
    }

    void TestApp::start()
    {
        // TestApp start implementation
    }
} // namespace sabre::impl::sabre_test_mocks