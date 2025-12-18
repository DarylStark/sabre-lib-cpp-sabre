#include "utility.hpp"
#include <chrono>
#include <thread>

// All times in this implementation are in microseconds to get the tests to
// finish quickly. In a _real_ implementation, they should be in milliseconds!

namespace sabre::impl::sabre_testing
{
    uint64_t StWaitFor::_getCurrentTime() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
    }

    StWaitFor::StWaitFor(WaitForPred fn, uint64_t timeoutInMs,
                         uint64_t sleepTime)
        : sabre::utility::WaitFor(fn, timeoutInMs, sleepTime)
    {
    }

    void StWaitFor::_sleep() const
    {
        std::this_thread::sleep_for(std::chrono::microseconds(_sleepTime));
    }
} // namespace sabre::impl::sabre_testing