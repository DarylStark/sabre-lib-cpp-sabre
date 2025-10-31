#include "factory.hpp"
#include <iostream>

#include "gpio/input_gpio.hpp"
#include "gpio/output_gpio.hpp"
#include "uart/uart.hpp"

namespace sabre::pilot
{
    Factory::Factory(MCU *mcu) : _mcu(mcu)
    {
        std::cout << "Factory created for MCU at " << mcu << std::endl;
    }

    UARTUniquePtr Factory::create_uart_object(uint32_t uart_number,
                                              int32_t baud_rate, int32_t tx_pin,
                                              int32_t rx_pin,
                                              size_t buffer_size) const
    {
        // Implementation specific code to create a UART object
        return std::make_unique<UART>(_mcu, uart_number, buffer_size);
    }

    InputGPIOUniquePtr Factory::create_input_gpio(int32_t pin) const
    {
        std::cout << "Creating InputGPIO on pin " << pin << " for MCU at "
                  << _mcu << std::endl;
        return std::make_unique<InputGPIO>(_mcu, pin);
    }

    OutputGPIOUniquePtr Factory::create_output_gpio(int32_t pin) const
    {
        std::cout << "Creating OutputGPIO on pin " << pin << " for MCU at "
                  << _mcu << std::endl;
        return std::make_unique<OutputGPIO>(_mcu, pin);
    }

    WifiStationUniquePtr Factory::create_wifi_station() const
    {
        // Implementation specific code to create a WifiStation object
        return nullptr; // Placeholder
    }

    WifiSoftAPUniquePtr Factory::create_wifi_soft_ap() const
    {
        // Implementation specific code to create a WifiSoftAP object
        return nullptr; // Placeholder
    }

    WallClockUniquePtr Factory::create_wall_clock() const
    {
        // Implementation specific code to create a WallClock object
        return nullptr; // Placeholder
    }

    NTPClientUniquePtr
    Factory::create_ntp_client(const std::string &server) const
    {
        // Implementation specific code to create an NTPClient object
        return nullptr; // Placeholder
    }

    MQTTClientUniquePtr Factory::create_mqtt_client() const
    {
        // Implementation specific code to create an MQTTClient object
        return nullptr; // Placeholder
    }

    WaitForUniquePtr Factory::create_wait_for(WaitForPred fn,
                                              uint64_t timeout_in_ms,
                                              uint64_t sleep_time) const
    {
        // Implementation specific code to create a WaitFor object
        return nullptr; // Placeholder
    }

    ServiceUniquePtr Factory::create_service(ServiceHandler fn) const
    {
        // Implementation specific code to create a Service object
        return nullptr; // Placeholder
    }
} // namespace sabre::pilot