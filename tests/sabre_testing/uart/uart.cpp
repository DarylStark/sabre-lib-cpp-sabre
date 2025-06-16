#include "uart.h"
#include <sabre/uart/uart.h>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <string>

namespace sabre::testing
{
    int TestUART::write_byte(char data) const
    {
        _buf.push_back(data);
        return static_cast<int>(data);
    }

    void TestUART::flush()
    {
        _buf.clear();
    }
} // namespace sabre::testing