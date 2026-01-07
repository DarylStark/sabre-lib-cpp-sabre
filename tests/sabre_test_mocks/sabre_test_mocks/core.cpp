#include "core.hpp"
#include "hal.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StFactory::StFactory(bool uartShouldBeNullptr)
        : _uart_should_be_nullptr(uartShouldBeNullptr)
    {
    }

    sabre::core::Uart::UniquePtr
    StFactory::createUartObject(uint32_t uartNumber, int32_t baudRate,
                                int32_t txPin, int32_t rxPin,
                                size_t bufferSize) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_unique<TestUART>();
    }

    sabre::core::InputGpio::UniquePtr
    StFactory::createInputGpio(int32_t pin) const
    {
        return nullptr;
    }

    sabre::core::OutputGpio::UniquePtr
    StFactory::createOutputGpio(int32_t pin) const
    {
        return nullptr;
    }

    sabre::core::WifiStation::UniquePtr StFactory::createWifiStation() const
    {
        return nullptr;
    }

    sabre::core::WifiSoftAp::UniquePtr StFactory::createWifiSoftAp() const
    {
        return nullptr;
    }

    sabre::core::MqttClient::UniquePtr StFactory::createMqttClient() const
    {
        return nullptr;
    }

    sabre::core::WaitFor::UniquePtr
    StFactory::createWaitFor(sabre::core::WaitForPred fn, uint64_t timeoutInMs,
                             uint64_t sleepTime) const
    {
        return nullptr;
    }

    sabre::core::Service::UniquePtr
    StFactory::createService(sabre::core::ServiceHandler fn) const
    {
        return nullptr;
    }

    sabre::core::NtpClient::UniquePtr
    StFactory::createNtpClient(const std::string &server) const
    {
        return nullptr;
    }

    sabre::core::WallClock::UniquePtr StFactory::createWallClock() const
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