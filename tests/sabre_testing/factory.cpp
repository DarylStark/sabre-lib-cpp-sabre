#include "factory.hpp"
#include "gpio/input_gpio.hpp"
#include "uart/uart.hpp"

namespace sabre::Testing
{

    Factory::Factory(bool uart_should_be_nullptr)
        : _uart_should_be_nullptr(uart_should_be_nullptr)
    {
    }

    UART::UniquePtr Factory::create_uart_object(uint32_t uart_number,
                                                int32_t baud_rate,
                                                int32_t tx_pin, int32_t rx_pin,
                                                size_t buffer_size) const
    {
        if (_uart_should_be_nullptr)
            return nullptr;
        return std::make_unique<TestUART>();
    }

    InputGPIO::UniquePtr Factory::create_input_gpio(int32_t pin) const
    {
        return nullptr;
    }

    OutputGPIO::UniquePtr Factory::create_output_gpio(int32_t pin) const
    {
        return nullptr;
    }

    WifiStation::UniquePtr Factory::create_wifi_station() const
    {
        return nullptr;
    }

    WifiSoftAP::UniquePtr Factory::create_wifi_soft_ap() const
    {
        return nullptr;
    }

    MQTTClient::UniquePtr Factory::create_mqtt_client() const
    {
        return nullptr;
    }

    WaitFor::UniquePtr Factory::create_wait_for(WaitForPred fn,
                                                uint64_t timeout_in_ms,
                                                uint64_t sleep_time) const
    {
        return nullptr;
    }

    Service::UniquePtr Factory::create_service(ServiceHandler fn) const
    {
        return nullptr;
    }

    NTPClient::UniquePtr
    Factory::create_ntp_client(const std::string &server) const
    {
        return nullptr;
    }

    WallClock::UniquePtr Factory::create_wall_clock() const
    {
        return nullptr;
    }
} // namespace sabre::Testing