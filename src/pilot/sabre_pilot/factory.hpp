#pragma once

#include "../simulator/device.hpp"
#include "sabre/app/app.hpp"
#include <sabre/factory.hpp>

namespace Sabre::Pilot
{
    class Factory : public Sabre::Factory
    {
    private:
        Device *_device;

    public:
        Factory(Device *device);
        UARTUniquePtr create_uart_object(uint32_t uart_number,
                                         int32_t baud_rate, int32_t tx_pin,
                                         int32_t rx_pin,
                                         size_t buffer_size) const;
        InputGPIOUniquePtr create_input_gpio(int32_t pin) const;
        OutputGPIOUniquePtr create_output_gpio(int32_t pin) const;
        WifiStationUniquePtr create_wifi_station() const;
        WifiSoftAPUniquePtr create_wifi_soft_ap() const;
        WallClockUniquePtr create_wall_clock() const;
        NTPClientUniquePtr create_ntp_client(const std::string &server) const;
        MQTTClientUniquePtr create_mqtt_client() const;
        WaitForUniquePtr create_wait_for(WaitForPred fn, uint64_t timeout_in_ms,
                                         uint64_t sleep_time) const;
        ServiceUniquePtr create_service(ServiceHandler fn) const;
    };
} // namespace Sabre::Pilot