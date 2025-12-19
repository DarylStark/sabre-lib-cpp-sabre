#include "device_connector.hpp"

namespace sabre::impl::pilot
{
    UartConnector::UartConnector(Device &device_a, uint32_t uart_number_a,
                                 Device &device_b, uint32_t uart_number_b)
        : _deviceA(device_a), _uartNumberA(uart_number_a), _deviceB(device_b),
          _uartNumberB(uart_number_b)
    {
        _deviceA.register_event_callback(
            DeviceEventType::UART_DATA_SEND,
            [this](const DeviceEvent &event)
            {
                auto *data = dynamic_cast<UartEventData *>(event.data.get());
                if (data && data->uartNumber == _uartNumberA)
                    _deviceB.add_to_input_uart_buffer(
                        _uartNumberB, std::string(1, data->data));
            });
    }
} // namespace sabre::impl::pilot