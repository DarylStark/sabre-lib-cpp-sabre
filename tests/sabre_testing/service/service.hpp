#pragma once

#include <sabre/os/service.hpp>

namespace sabre::impl::sabre_testing
{
    using sabre::os::ServiceHandler;
    class Service : public sabre::os::Service
    {
    public:
        Service(ServiceHandler fn);
        void start() override;
        void stop() override;
    };
} // namespace sabre::impl::sabre_testing