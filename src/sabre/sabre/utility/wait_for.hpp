#pragma once

#include <cstdint>
#include <functional>
#include <memory>

namespace sabre::utility
{
    using WaitForPred = std::function<bool()>;

    /**
     * @brief A class that waits for a condition to be met within a specified
     * timeout.
     *
     * This class provides a mechanism to repeatedly check a predicate function
     * until it returns true or the timeout is reached. It can be used for
     * waiting for asynchronous operations to complete or conditions to be met.
     */
    class WaitFor
    {
    public:
        using Ptr = WaitFor *;
        using SharedPtr = std::shared_ptr<WaitFor>;
        using UniquePtr = std::unique_ptr<WaitFor>;

    private:
        bool _done(bool result, uint64_t totalRuntime);

    protected:
        uint64_t _timeoutInMs;
        WaitForPred _fn;
        uint64_t _sleepTime = 0;

        bool _result = false;
        uint64_t _runtime = 0;

        /**
         * @brief Get the current time in milliseconds.
         *
         * This method should be implemented by derived classes to provide
         * the current time in milliseconds since the epoch or a similar
         * reference point.
         */
        virtual uint64_t _getCurrentTime() const = 0;

        /**
         * @brief Sleep for a specified duration.
         *
         * This method should be implemented by derived classes to provide
         * a sleep mechanism that pauses execution for the specified
         * duration in milliseconds.
         */
        virtual void _sleep() const = 0;

    public:
        /**
         * @brief Constructor for the WaitFor class.
         *
         * @param fn The predicate function to check.
         * @param timeoutInMs The maximum time to wait in milliseconds.
         * @param sleepTime The time to sleep between checks in milliseconds.
         */
        WaitFor(WaitForPred fn, uint64_t timeoutInMs, uint64_t sleepTime);

        /**
         * @brief Start the waiting process.
         *
         * This method begins the process of waiting for the predicate function
         * to return true or the timeout to be reached.
         *
         * @return True if the predicate function returned true, false if the
         *         timeout was reached.
         */
        bool operator()();

        /**
         * @brief Get the result of the last wait operation.
         *
         * This method returns the result of the last wait operation, indicating
         * whether the predicate function returned true or not.
         *
         * @return True if the predicate function returned true, false
         * otherwise.
         */
        bool getResult() const;

        /**
         * @brief Get the runtime of the last wait operation.
         *
         * This method returns the total time taken for the last wait operation
         * in milliseconds.
         *
         * @return The runtime in milliseconds.
         */
        uint64_t getResultRuntime() const;
    };
}; // namespace sabre::utility