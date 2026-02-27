#include "wait_for.hpp"

namespace sabre::utility
{

    bool WaitFor::_done(bool result, sabre::types::MsTime totalRuntime) noexcept
    {
        _runtime = totalRuntime;
        _result = result;
        return result;
    }

    WaitFor::WaitFor(const WaitForPred &fn, sabre::types::MsTime timeoutInMs,
                     sabre::types::MsTime sleepTime)
        : _timeoutInMs(timeoutInMs), _fn(fn), _sleepTime(sleepTime)
    {
    }

    bool WaitFor::operator()()
    {
        sabre::types::MsTime starttime = _getCurrentTime();

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

    sabre::types::MsTime WaitFor::getResultRuntime() const noexcept
    {
        return _runtime;
    }
}; // namespace sabre::utility