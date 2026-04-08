#pragma once

#include <sabre/os/queue.hpp>
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

    class StQueue : public sabre::os::Queue
    {
    public:
        StQueue(std::size_t count, std::size_t capacity);
        ~StQueue();

        void push(const void *item, sabre::types::MsTime timeout) override;
        void pushFromIsr(const void *item) override;

        void *pop(sabre::types::MsTime timeout) override;
        void *popFromIsr() override;

        std::size_t count() const override;
        std::size_t capacity() const override;
        bool isEmpty() const override;
        bool isFull() const override;
        void clear() override;
    };
} // namespace sabre::impl::sabre_test_mocks