#include "device_connector.hpp"

namespace sabre::pilot
{
    UartConnector::UartConnector(MCU &mcu_a, uint32_t uart_number_a, MCU &mcu_b,
                                 uint32_t uart_number_b)
        : _mcu_a(mcu_a), _uart_number_a(uart_number_a), _mcu_b(mcu_b),
          _uart_number_b(uart_number_b)
    {
        _mcu_a.register_event_callback(
            DeviceEventType::UART_DATA_SEND,
            [this](const DeviceEvent &event)
            {
                auto *data = dynamic_cast<UartEventData *>(event.data.get());
                if (data && data->uart_number == _uart_number_a)
                    _mcu_b.add_to_input_uart_buffer(_uart_number_b,
                                                    std::string(1, data->data));
            });
    }
} // namespace sabre::pilot