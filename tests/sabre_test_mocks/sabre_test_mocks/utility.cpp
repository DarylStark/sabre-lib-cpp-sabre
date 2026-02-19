#include "utility.hpp"
#include <chrono>
#include <thread>

// All times in this implementation are in microseconds to get the tests to
// finish quickly. In a _real_ implementation, they should be in milliseconds!

namespace sabre::impl::sabre_test_mocks
{
    uint64_t StWaitFor::_getCurrentTime() const noexcept
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
    }

    StWaitFor::StWaitFor(const sabre::utility::WaitForPred &fn,
                         uint64_t timeoutInMs, uint64_t sleepTime) noexcept
        : sabre::utility::WaitFor(fn, timeoutInMs, sleepTime)
    {
    }

    void StWaitFor::_sleep() const noexcept
    {
        std::this_thread::sleep_for(std::chrono::microseconds(_sleepTime));
    }
} // namespace sabre::impl::sabre_test_mocks