#include "service.hpp"

namespace Sabre
{
    Service::Service(ServiceHandler fn) : _fn(fn) {}
} // namespace Sabre