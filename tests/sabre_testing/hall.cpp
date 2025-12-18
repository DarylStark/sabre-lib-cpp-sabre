#include "hal.hpp"

namespace sabre::impl::sabre_testing
{
    bool StInputGpio::_getLevel() const
    {
        return level;
    }

    void StInputGpio::enablePullup() {}
    void StInputGpio::enablePulldown() {}
    void StInputGpio::disablePullup() {}
    void StInputGpio::disablePulldown() {}
    void StInputGpio::addInterruptHandler(ISRHandler, ISRTrigger) {}
    void StInputGpio::reset() {}

    void TestUART::initialize()
    {
        // No-op for test implementation
    }

    int TestUART::writeByte(char data) const
    {
        _buf.push_back(data);
        return static_cast<int>(data);
    }

    std::string TestUART::readBytes(size_t maxBytes, uint32_t timeoutMs)
    {
        // For testing purposes, return up to maxBytes from the buffer
        std::string result = _buf.substr(0, maxBytes);
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