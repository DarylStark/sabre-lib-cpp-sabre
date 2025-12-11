#include "service.hpp"

namespace Sabre::Testing
{
    Service::Service(Sabre::ServiceHandler fn) : Sabre::Service(fn) {}

    void Service::start()
    {
        _fn();
    }

    void Service::stop() {}
} // namespace Sabre::Testing