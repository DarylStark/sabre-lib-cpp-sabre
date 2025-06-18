#include "service_runner.hpp"

namespace sabre::testing
{
    void ServiceRunner::start()
    {
        _is_runner = true;
    }

    void ServiceRunner::stop()
    {
        _is_runner = false;
    }

    bool ServiceRunner::is_running() const
    {
        return _is_runner;
    }
} // namespace sabre::testing