#include "hal.hpp"

namespace sabre::impl::sabre_testing
{
    bool InputGPIO::_get_level() const
    {
        return level;
    }

    void InputGPIO::enable_pullup() {}
    void InputGPIO::enable_pulldown() {}
    void InputGPIO::disable_pullup() {}
    void InputGPIO::disable_pulldown() {}
    void InputGPIO::add_interrupt_handler(ISRHandler, ISRTrigger) {}
    void InputGPIO::reset() {}

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
} // namespace sabre::impl::sabre_testing