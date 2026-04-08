#include "os.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StService::StService(const sabre::os::ServiceHandler &fn)
        : sabre::os::Service(fn)
    {
    }

    void StService::start()
    {
        _fn();
    }

    void StService::stop() {}

    StQueue::StQueue(std::size_t count, std::size_t capacity) {}
    StQueue::~StQueue() {}

    void StQueue::push(const void *item, sabre::types::MsTime timeout) {}

    void StQueue::pushFromIsr(const void *item) {}

    void *StQueue::pop(sabre::types::MsTime timeout)
    {
        return nullptr;
    }

    void *StQueue::popFromIsr()
    {
        return nullptr;
    }

    std::size_t StQueue::count() const
    {
        return 0;
    }

    std::size_t StQueue::capacity() const
    {
        return 0;
    }

    bool StQueue::isEmpty() const
    {
        return false;
    }

    bool StQueue::isFull() const
    {
        return false;
    }

    void StQueue::clear() {}
} // namespace sabre::impl::sabre_test_mocks