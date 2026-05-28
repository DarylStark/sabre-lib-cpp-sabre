#include "hal.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StGpio::StGpio(int32_t pin) : sabre::hal::Gpio(pin) {}

    void StGpio::reset() {}

    bool StInputGpio::_getLevel() const
    {
        return level;
    }

    void StInputGpio::enablePullup() {}
    void StInputGpio::enablePulldown() {}
    void StInputGpio::disablePullup() {}
    void StInputGpio::disablePulldown() {}
    void StInputGpio::addInterruptHandler(sabre::hal::ISRHandler,
                                          sabre::hal::ISRTrigger)
    {
    }
    void StInputGpio::reset() {}

    void StOutputGpio::setLevel(bool level) {}
    void StOutputGpio::setHigh() {}
    void StOutputGpio::setLow() {}
    void StOutputGpio::reset() {}

    void TestUART::initialize() {}

    int TestUART::writeByte(char data) const
    {
        _buf.push_back(data);
        return static_cast<int>(data);
    }

    std::string TestUART::readBytes(size_t maxBytes,
                                    sabre::types::MsTime timeoutMs)
    {
        // For testing purposes, return up to maxBytes from the buffer
        std::string result = _buf.substr(0, maxBytes);
        _buf.erase(0, result.size());
        return result;
    }

    void TestUART::flush() {}

    void TestUART::deinitialize() {}
} // namespace sabre::impl::sabre_test_mocks