#include "wait_for.hpp"

namespace sabre::utility
{

    bool WaitFor::_done(bool result, uint64_t total_runtime)
    {
        _runtime = total_runtime;
        _result = result;
        return result;
    }

    WaitFor::WaitFor(WaitForPred fn, uint64_t timeout_in_ms,
                     uint64_t sleep_time)
        : _timeoutInMs(timeout_in_ms), _fn(fn), _sleepTime(sleep_time)
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

    bool WaitFor::getResult() const
    {
        return _result;
    }

    uint64_t WaitFor::getResultRuntime() const
    {
        return _runtime;
    }
}; // namespace sabre::utility