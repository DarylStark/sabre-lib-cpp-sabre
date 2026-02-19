#include "service.hpp"

namespace sabre::os
{
    Service::Service(const ServiceHandler &fn) noexcept : _fn(fn) {}
} // namespace sabre::os