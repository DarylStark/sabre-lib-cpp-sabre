#include "device_connector.hpp"

namespace sabre::pilot
{
    UartConnector::UartConnector(MCU &mcu_a, uint32_t uart_number_a, MCU &mcu_b,
                                 uint32_t uart_number_b)
        : _mcu_a(mcu_a), _uart_number_a(uart_number_a), _mcu_b(mcu_b),
          _uart_number_b(uart_number_b)
    {
    }
} // namespace sabre::pilot