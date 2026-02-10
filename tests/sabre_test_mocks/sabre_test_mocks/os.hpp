#pragma once

#include <sabre/os/service.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StService : public sabre::os::Service
    {
    public:
        StService(const sabre::os::ServiceHandler &fn);
        void start() override;
        void stop() override;
    };
} // namespace sabre::impl::sabre_test_mocks