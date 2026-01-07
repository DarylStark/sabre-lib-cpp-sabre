#include "core.hpp"
#include "hal.hpp"
#include <iostream>

namespace sabre::impl::pilot
{
    Factory::Factory(Device *device) : _device(device)
    {
        std::cout << "Factory created for device at " << device << '\n'
                  << std::flush;
    }

    sabre::hal::Uart::UniquePtr
    Factory::createUartObject(uint32_t uartNumber, int32_t baudRate,
                              int32_t txPin, int32_t rxPin,
                              size_t bufferSize) const
    {
        // Implementation specific code to create a UART object
        return std::make_unique<Uart>(_device, uartNumber, bufferSize);
    }

    sabre::hal::InputGpio::UniquePtr Factory::createInputGpio(int32_t pin) const
    {
        std::cout << "Creating InputGPIO on pin " << pin << " for device at "
                  << _device << '\n'
                  << std::flush;
        return std::make_unique<sabre::impl::pilot::InputGpio>(_device, pin);
    }

    sabre::hal::OutputGpio::UniquePtr
    Factory::createOutputGpio(int32_t pin) const
    {
        std::cout << "Creating OutputGPIO on pin " << pin << " for device at "
                  << _device << '\n'
                  << std::flush;
        return std::make_unique<sabre::impl::pilot::OutputGpio>(_device, pin);
    }

    sabre::net::WifiStation::UniquePtr Factory::createWifiStation() const
    {
        // Implementation specific code to create a WifiStation object
        return nullptr; // Placeholder
    }

    sabre::net::WifiSoftAp::UniquePtr Factory::createWifiSoftAp() const
    {
        // Implementation specific code to create a WifiSoftAP object
        return nullptr; // Placeholder
    }

    sabre::time::WallClock::UniquePtr Factory::createWallClock() const
    {
        // Implementation specific code to create a WallClock object
        return nullptr; // Placeholder
    }

    sabre::time::NtpClient::UniquePtr
    Factory::createNtpClient(const std::string &server) const
    {
        // Implementation specific code to create an NTPClient object
        return nullptr; // Placeholder
    }

    sabre::net::MqttClient::UniquePtr Factory::createMqttClient() const
    {
        // Implementation specific code to create an MQTTClient object
        return nullptr; // Placeholder
    }

    sabre::utility::WaitFor::UniquePtr
    Factory::createWaitFor(sabre::utility::WaitForPred fn, uint64_t timeoutInMs,
                           uint64_t sleepTime) const
    {
        // Implementation specific code to create a WaitFor object
        return nullptr; // Placeholder
    }

    sabre::os::Service::UniquePtr
    Factory::createService(sabre::os::ServiceHandler fn) const
    {
        // Implementation specific code to create a Service object
        return nullptr; // Placeholder
    }
} // namespace sabre::impl::pilot