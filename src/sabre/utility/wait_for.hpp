#ifndef SABRE_WAIT_FOR_H
#define SABRE_WAIT_FOR_H

#include <cstdint>
#include <functional>
#include <memory>

namespace sabre
{
    using WaitForPred = std::function<bool()>;
    class WaitFor
    {
    private:
        bool _done(bool result, uint64_t total_runtime);

    protected:
        uint64_t _timeout_in_ms;
        WaitForPred _fn;
        uint64_t _sleep_time = 0;

        bool _result = false;
        uint64_t _runtime = 0;

        virtual uint64_t _get_current_time() const = 0;
        virtual void _sleep() const = 0;

    public:
        WaitFor(WaitForPred fn, uint64_t timeout_in_ms, uint64_t sleep_time);
        bool operator()();
        bool get_result() const;
        uint64_t get_result_runtime() const;
    };
    using WaitForPtr = WaitFor *;
    using WaitForSharedPtr = std::shared_ptr<WaitFor>;
}; // namespace sabre

#endif // SABRE_WAIT_FOR_H