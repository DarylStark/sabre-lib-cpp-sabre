#include "time.hpp"

namespace sabre::impl::sabre_test_mocks
{
    sabre::types::MsTime StWallClock::nowMs() const noexcept
    {
        return 0;
    }

    void StWallClock::setNowMs(sabre::types::MsTime timeInMs) {}

    void StNtpClient::start() {}

    void StNtpClient::stop() {}

    bool StNtpClient::isSynchronized() const noexcept
    {
        return true;
    }
} // namespace sabre::impl::sabre_test_mocks