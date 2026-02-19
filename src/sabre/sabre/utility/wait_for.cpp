#include "wait_for.hpp"

namespace sabre::utility
{

    bool WaitFor::_done(bool result, uint64_t totalRuntime) noexcept
    {
        _runtime = totalRuntime;
        _result = result;
        return result;
    }

    WaitFor::WaitFor(const WaitForPred &fn, uint64_t timeoutInMs,
                     uint64_t sleepTime)
        : _timeoutInMs(timeoutInMs), _fn(fn), _sleepTime(sleepTime)
    {
    }

    bool WaitFor::operator()()
    {
        uint64_t starttime = _getCurrentTime();

        while (_timeoutInMs > _getCurrentTime() - starttime)
        {
            if (_fn())
                return _done(true, _getCurrentTime() - starttime);
            _sleep();
        }
        return _done(false, _getCurrentTime() - starttime);
    }

    bool WaitFor::getResult() const noexcept
    {
        return _result;
    }

    uint64_t WaitFor::getResultRuntime() const noexcept
    {
        return _runtime;
    }
}; // namespace sabre::utility