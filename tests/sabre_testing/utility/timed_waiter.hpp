#ifndef SABRE_TESTING_TIMED_WAITER_H
#define SABRE_TESTING_TIMED_WAITER_H

#include <sabre/utility/timed_waiter.hpp>

namespace sabre::testing
{
    class TimedWaiter : public sabre::TimedWaiter
    {
    protected:
        uint64_t _get_current_time() const;
        void _sleep() const;

    public:
        TimedWaiter(TimedWaiterPred fn, uint64_t timeout_in_ms,
                    uint64_t sleep_time);
    };
} // namespace sabre::testing

#endif // SABRE_TESTING_TIMED_WAITER_H