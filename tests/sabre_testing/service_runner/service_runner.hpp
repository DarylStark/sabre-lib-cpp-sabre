#ifndef SABRE_TESTING_SERVICE_RUNNER_H
#define SABRE_TESTING_SERVICE_RUNNER_H

#include <memory>
#include <sabre/service_runner/service_runner.hpp>

namespace sabre::testing
{
    class ServiceRunner : public sabre::ServiceRunner
    {
    private:
        bool _is_runner = false;

    protected:
        void _service() override;

    public:
        void start() override;
        void stop() override;
        bool is_running() const override;

        int value = 0;
    };
} // namespace sabre::testing

#endif // SABRE_TESTING_SERVICE_RUNNER_H