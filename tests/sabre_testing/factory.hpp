#ifndef SABRE_TESTING_FACTORY_H
#define SABRE_TESTING_FACTORY_H

#include <memory>
#include <ostream>
#include <sabre/factory.hpp>

namespace sabre::testing
{
    class Factory : public sabre::Factory
    {
        bool _uart_should_be_nullptr = false;

    public:
        Factory(bool uart_should_be_nullptr = false);
        UARTUniquePtr create_uart_object(uint32_t uart_number,
                                         int32_t baud_rate, int32_t tx_pin,
                                         int32_t rx_pin) const;
        InputGPIOUniquePtr create_input_gpio(int32_t pin) const;
        OutputGPIOUniquePtr create_output_gpio(int32_t pin) const;
        WifiStationUniquePtr create_wifi_station() const;
        WifiSoftAPUniquePtr create_wifi_soft_ap() const;
        MQTTClientUniquePtr create_mqtt_client() const;
        WaitForUniquePtr create_wait_for(WaitForPred fn, uint64_t timeout_in_ms,
                                         uint64_t sleep_time) const;
        ServiceUniquePtr create_service(ServiceHandler fn) const;

        NTPClientUniquePtr create_ntp_client(
            const std::string& server) const override;
        WallClockUniquePtr create_wall_clock() const override;
    };
} // namespace sabre::testing

#endif // SABRE_FACTORY_H