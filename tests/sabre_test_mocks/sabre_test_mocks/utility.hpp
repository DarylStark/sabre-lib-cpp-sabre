#pragma once

#include <sabre/utility/wait_for.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StWaitFor : public sabre::utility::WaitFor
    {
    protected:
        uint64_t _getCurrentTime() const;
        void _sleep() const;

    public:
        StWaitFor(const sabre::utility::WaitForPred &fn, uint64_t timeoutInMs,
                  uint64_t sleepTime);
    };
} // namespace sabre::impl::sabre_test_mocks