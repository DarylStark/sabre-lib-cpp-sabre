#pragma once

#include <sabre/time/wall_clock.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StWallClock : public sabre::time::WallClock
    {
    public:
        sabre::types::MsTime nowMs() const noexcept;
        void setNowMs(sabre::types::MsTime timeInMs);
    };
} // namespace sabre::impl::sabre_test_mocks