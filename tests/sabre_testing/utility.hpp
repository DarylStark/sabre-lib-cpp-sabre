#pragma once

#include <sabre/utility/wait_for.hpp>

namespace sabre::impl::sabre_testing
{
    using sabre::utility::WaitForPred;

    class StWaitFor : public sabre::utility::WaitFor
    {
    protected:
        uint64_t _getCurrentTime() const;
        void _sleep() const;

    public:
        StWaitFor(WaitForPred fn, uint64_t timeoutInMs, uint64_t sleepTime);
    };
} // namespace sabre::impl::sabre_testing