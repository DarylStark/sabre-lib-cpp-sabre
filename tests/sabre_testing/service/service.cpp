#include "service.hpp"

namespace sabre::Testing
{
    Service::Service(sabre::ServiceHandler fn) : sabre::Service(fn) {}

    void Service::start()
    {
        _fn();
    }

    void Service::stop() {}
} // namespace sabre::Testing