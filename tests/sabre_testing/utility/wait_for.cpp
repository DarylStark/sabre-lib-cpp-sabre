#include "wait_for.hpp"
#include <chrono>
#include <thread>

// All times in this implementation are in microseconds to get the tests to
// finish quickly. In a _real_ implementation, they should be in milliseconds!

namespace Sabre::Testing
{
    uint64_t WaitFor::_get_current_time() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
    }

    WaitFor::WaitFor(WaitForPred fn, uint64_t timeout_in_ms,
                     uint64_t sleep_time)
        : Sabre::WaitFor(fn, timeout_in_ms, sleep_time)
    {
    }

    void WaitFor::_sleep() const
    {
        std::this_thread::sleep_for(std::chrono::microseconds(_sleep_time));
    }
} // namespace Sabre::Testing