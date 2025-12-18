#pragma once

#include "../simulator/device.hpp"
#include "sabre/core/app.hpp"
#include <sabre/core/factory.hpp>

namespace sabre::Pilot
{
    class Factory : public sabre::core::Factory
    {
    private:
        Device *_device;

    public:
        Factory(Device *device);
        sabre::hal::Uart::UniquePtr createUartObject(uint32_t uart_number,
                                                     int32_t baud_rate,
                                                     int32_t tx_pin,
                                                     int32_t rx_pin,
                                                     size_t buffer_size) const;
        sabre::hal::InputGpio::UniquePtr createInputGpio(int32_t pin) const;
        sabre::hal::OutputGpio::UniquePtr createOutputGpio(int32_t pin) const;
        sabre::net::WifiStation::UniquePtr createWifiStation() const;
        sabre::net::WifiSoftAp::UniquePtr createWifiSoftAp() const;
        sabre::time::WallClock::UniquePtr createWallClock() const;
        sabre::time::NtpClient::UniquePtr
        createNtpClient(const std::string &server) const;
        sabre::net::MqttClient::UniquePtr createMqttClient() const;
        sabre::utility::WaitFor::UniquePtr
        createWaitFor(sabre::utility::WaitForPred fn, uint64_t timeout_in_ms,
                      uint64_t sleep_time) const;
        sabre::os::Service::UniquePtr
        createService(sabre::os::ServiceHandler fn) const;
    };
} // namespace sabre::Pilot