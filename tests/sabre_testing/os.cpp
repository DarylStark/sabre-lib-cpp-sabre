#include "os.hpp"

namespace sabre::impl::sabre_testing
{
    Service::Service(ServiceHandler fn) : sabre::os::Service(fn) {}

    void Service::start()
    {
        _fn();
    }

    void Service::stop() {}
} // namespace sabre::impl::sabre_testing