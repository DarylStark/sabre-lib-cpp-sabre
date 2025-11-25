#include "device_connector.hpp"

namespace sabre::pilot
{
    UartConnector::UartConnector(Device &device_a, uint32_t uart_number_a,
                                 Device &device_b, uint32_t uart_number_b)
        : _device_a(device_a), _uart_number_a(uart_number_a),
          _device_b(device_b), _uart_number_b(uart_number_b)
    {
        _device_a.register_event_callback(
            DeviceEventType::UART_DATA_SEND,
            [this](const DeviceEvent &event)
            {
                auto *data = dynamic_cast<UartEventData *>(event.data.get());
                if (data && data->uart_number == _uart_number_a)
                    _device_b.add_to_input_uart_buffer(
                        _uart_number_b, std::string(1, data->data));
            });
    }
} // namespace sabre::pilot