#pragma once

#include <sabre/service/service.hpp>

namespace sabre::Testing
{
    class Service : public sabre::Service
    {
    public:
        Service(sabre::ServiceHandler fn);
        void start() override;
        void stop() override;
    };
} // namespace sabre::Testing