#include "service.hpp"

namespace sabre::os
{
    Service::Service(const ServiceHandler &fn) : _fn(fn) {}
} // namespace sabre::os