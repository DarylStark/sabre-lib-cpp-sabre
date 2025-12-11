#include "uart.hpp"
#include <sabre/uart/uart.hpp>
#include <sabre/uart/uart_output_stream_buffer.hpp>
#include <string>

namespace Sabre::Testing
{
    void TestUART::initialize()
    {
        // No-op for test implementation
    }

    int TestUART::write_byte(char data) const
    {
        _buf.push_back(data);
        return static_cast<int>(data);
    }

    std::string TestUART::read_bytes(size_t max_bytes, uint32_t timeout_ms)
    {
        // For testing purposes, return up to max_bytes from the buffer
        std::string result = _buf.substr(0, max_bytes);
        _buf.erase(0, result.size());
        return result;
    }

    void TestUART::flush()
    {
        _buf.clear();
    }

    void TestUART::deinitialize()
    {
        // No-op for test implementation
    }
} // namespace Sabre::Testing