#include "time.hpp"

namespace sabre::impl::sabre_test_mocks
{
    sabre::types::MsTime StWallClock::nowMs() const noexcept
    {
        return 0;
    }

    void StWallClock::setNowMs(sabre::types::MsTime timeInMs) {}
} // namespace sabre::impl::sabre_test_mocks