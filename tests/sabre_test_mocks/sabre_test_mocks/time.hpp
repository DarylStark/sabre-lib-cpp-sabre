#pragma once

#include <sabre/time/ntp.hpp>
#include <sabre/time/wall_clock.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StWallClock : public sabre::time::WallClock
    {
    public:
        sabre::types::MsTime nowMs() const noexcept;
        void setNowMs(sabre::types::MsTime timeInMs);
    };

    class StNtpClient : public sabre::time::NtpClient
    {
    public:
        void start() override;
        void stop() override;
        bool isSynchronized() const noexcept override;
    };
} // namespace sabre::impl::sabre_test_mocks