#include "service.hpp"

namespace sabre::Testing
{
    Service::Service(ServiceHandler fn) : sabre::os::Service(fn) {}

    void Service::start()
    {
        _fn();
    }

    void Service::stop() {}
} // namespace sabre::Testing