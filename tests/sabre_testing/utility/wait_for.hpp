#pragma once

#include <sabre/utility/wait_for.hpp>

namespace sabre::testing
{
    class WaitFor : public sabre::WaitFor
    {
    protected:
        uint64_t _get_current_time() const;
        void _sleep() const;

    public:
        WaitFor(WaitForPred fn, uint64_t timeout_in_ms, uint64_t sleep_time);
    };
} // namespace sabre::testing