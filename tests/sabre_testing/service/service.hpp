#ifndef SABRE_TESTING_SERVICE_H
#define SABRE_TESTING_SERVICE_H

#include <sabre/service/service.hpp>

namespace sabre::testing
{
    class Service : public sabre::Service
    {
    public:
        Service(sabre::ServiceHandler fn);
        void start() override;
        void stop() override;
    };
} // namespace sabre::testing

#endif // SABRE_TESTING_SERVICE_H
