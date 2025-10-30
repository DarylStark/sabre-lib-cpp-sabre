#include "factory.hpp"

namespace sabre
{
    UARTStreamBufUniquePtr Factory::create_uart_output_stream_buffer(
        uint32_t uart_number, int32_t baud_rate, int32_t tx_pin, int32_t rx_pin,
        size_t buffer_size) const
    {
        auto uart = create_uart_object(uart_number, baud_rate, tx_pin, rx_pin);
        if (!uart)
            return nullptr;
        uart->initialize();
        return std::make_unique<UARTStreamBuf>(std::move(uart), buffer_size);
    }
} // namespace sabre