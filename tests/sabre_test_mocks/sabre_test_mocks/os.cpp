#include "os.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StService::StService(ServiceHandler fn) : sabre::os::Service(fn) {}

    void StService::start()
    {
        _fn();
    }

    void StService::stop() {}
} // namespace sabre::impl::sabre_test_mocks