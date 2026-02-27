#include "core.hpp"
#include "hal.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StFactory::StFactory(bool uartShouldBeNullptr)
        : _uart_should_be_nullptr(uartShouldBeNullptr)
    {
    }

    sabre::hal::Serial::UniquePtr StFactory::createUartObject(
        uint32_t uartNumber, int32_t baudRate, sabre::hal::PinNumber txPin,
        sabre::hal::PinNumber rxPin, size_t bufferSize) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_unique<TestUART>();
    }

    sabre::hal::Serial::UniquePtr
    StFactory::createUsbCdc(uint32_t index, size_t bufferSize) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_unique<TestUART>();
    }

    sabre::hal::InputGpio::UniquePtr
    StFactory::createInputGpio(sabre::hal::PinNumber pin) const
    {
        return std::make_unique<sabre::impl::sabre_test_mocks::StInputGpio>();
    }

    sabre::hal::OutputGpio::UniquePtr
    StFactory::createOutputGpio(sabre::hal::PinNumber pin) const
    {
        return std::make_unique<sabre::impl::sabre_test_mocks::StOutputGpio>();
    }

    sabre::hal::Gpio::UniquePtr
    StFactory::createGpio(sabre::hal::PinNumber pin) const
    {
        return std::make_unique<sabre::impl::sabre_test_mocks::StGpio>(pin);
    }

    sabre::net::WifiStation::UniquePtr StFactory::createWifiStation() const
    {
        return nullptr;
    }

    sabre::net::WifiSoftAp::UniquePtr StFactory::createWifiSoftAp() const
    {
        return nullptr;
    }

    sabre::net::MqttClient::UniquePtr StFactory::createMqttClient() const
    {
        return nullptr;
    }

    sabre::utility::WaitFor::UniquePtr
    StFactory::createWaitFor(sabre::utility::WaitForPred fn,
                             uint64_t timeoutInMs, uint64_t sleepTime) const
    {
        return nullptr;
    }

    sabre::os::Service::UniquePtr
    StFactory::createService(sabre::os::ServiceHandler fn) const
    {
        return nullptr;
    }

    sabre::time::NtpClient::UniquePtr
    StFactory::createNtpClient(const std::string &server) const
    {
        return nullptr;
    }

    sabre::time::WallClock::UniquePtr StFactory::createWallClock() const
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