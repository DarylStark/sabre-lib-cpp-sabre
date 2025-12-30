#include "service.hpp"

namespace sabre::os
{
    Service::Service(ServiceHandler fn) : _fn(fn) {}
} // namespace sabre::os