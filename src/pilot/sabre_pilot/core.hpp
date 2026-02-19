#pragma once

#include "../simulator/device.hpp"
#include "sabre/runtime/app.hpp"
#include <sabre/core/factory.hpp>

namespace sabre::impl::pilot
{
    class Factory : public sabre::core::Factory
    {
    private:
        Device *_device;

    public:
        Factory(Device *device);
        sabre::hal::Serial::UniquePtr
        createUartObject(uint32_t uartNumber, int32_t baudRate, int32_t txPin,
                         int32_t rxPin, size_t bufferSize) const override;
        sabre::hal::Serial::UniquePtr
        createUsbCdc(uint32_t index, size_t bufferSize) const override;
        sabre::hal::InputGpio::UniquePtr
        createInputGpio(int32_t pin) const override;
        sabre::hal::OutputGpio::UniquePtr
        createOutputGpio(int32_t pin) const override;
        sabre::hal::Gpio::UniquePtr createGpio(int32_t pin) const override;
        sabre::net::WifiStation::UniquePtr createWifiStation() const override;
        sabre::net::WifiSoftAp::UniquePtr createWifiSoftAp() const override;
        sabre::time::WallClock::UniquePtr createWallClock() const override;
        sabre::time::NtpClient::UniquePtr
        createNtpClient(const std::string &server) const override;
        sabre::net::MqttClient::UniquePtr createMqttClient() const override;
        sabre::utility::WaitFor::UniquePtr
        createWaitFor(sabre::utility::WaitForPred fn, uint64_t timeoutInMs,
                      uint64_t sleepTime) const override;
        sabre::os::Service::UniquePtr
        createService(sabre::os::ServiceHandler fn) const override;
    };
} // namespace sabre::impl::pilot