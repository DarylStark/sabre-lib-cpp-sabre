#pragma once

#include <sabre/utility/wait_for.hpp>

namespace sabre::impl::sabre_testing
{
    using sabre::utility::WaitForPred;

    class WaitFor : public sabre::utility::WaitFor
    {
    protected:
        uint64_t _get_current_time() const;
        void _sleep() const;

    public:
        WaitFor(WaitForPred fn, uint64_t timeout_in_ms, uint64_t sleep_time);
    };
} // namespace sabre::impl::sabre_testing