#pragma once

#include <sabre/service/service.hpp>

namespace Sabre::Testing
{
    class Service : public Sabre::Service
    {
    public:
        Service(Sabre::ServiceHandler fn);
        void start() override;
        void stop() override;
    };
} // namespace Sabre::Testing