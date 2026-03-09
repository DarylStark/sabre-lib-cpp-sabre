#include "core.hpp"
#include "hal.hpp"
#include "time.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StFactory::StFactory(bool uartShouldBeNullptr)
        : _uart_should_be_nullptr(uartShouldBeNullptr)
    {
    }

    sabre::hal::Serial::UniquePtr StFactory::createUartObject(
        sabre::hal::UartNumber uartNumber, sabre::hal::BaudRate baudRate,
        sabre::hal::PinNumber txPin, sabre::hal::PinNumber rxPin,
        size_t bufferSize) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_unique<TestUART>();
    }

    sabre::hal::Serial::UniquePtr
    StFactory::createUsbCdc(sabre::hal::UsbIndex index, size_t bufferSize) const
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
        return std::make_unique<sabre::impl::sabre_test_mocks::StNtpClient>();
    }

    sabre::time::WallClock::UniquePtr StFactory::createWallClock() const
    {
        return std::make_unique<sabre::impl::sabre_test_mocks::StWallClock>();
    }
} // namespace sabre::impl::sabre_test_mocks