#include "factory.hpp"
#include "uart/uart.hpp"

namespace sabre::testing
{

    Factory::Factory(bool uart_should_be_nullptr)
        : _uart_should_be_nullptr(uart_should_be_nullptr)
    {
    }

    UARTSharedPtr Factory::create_uart_object(uint32_t uart_number,
                                              int32_t baud_rate, int32_t tx_pin,
                                              int32_t rx_pin) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_shared<TestUART>();
    }

    InputGPIOSharedPtr Factory::create_input_gpio(int32_t pin) const
    {
        return nullptr;
    }

    OutputGPIOSharedPtr Factory::create_output_gpio(int32_t pin) const
    {
        return nullptr;
    }

    WifiStationSharedPtr Factory::create_wifi_station() const
    {
        return nullptr;
    }

    WifiSoftAPSharedPtr Factory::create_wifi_soft_ap() const
    {
        return nullptr;
    }

    MQTTClientSharedPtr Factory::create_mqtt_client() const
    {
        return nullptr;
    }

    WaitForSharedPtr Factory::create_wait_for(WaitForPred fn,
                                              uint64_t timeout_in_ms,
                                              uint64_t sleep_time) const
    {
        return nullptr;
    }
} // namespace sabre::testing