#pragma once

#include "../log/logging.hpp"
#include "../types/types.hpp"

#include <memory>

namespace sabre
{
    namespace os
    {
        class Queue
        {
        public:
            using Ptr = Queue *;
            using SharedPtr = std::shared_ptr<Queue>;
            using UniquePtr = std::unique_ptr<Queue>;

        private:
            sabre::log::LogHelper _log_helper;

        public:
            virtual ~Queue();

            sabre::log::LogHelper &getLogHelper();
            virtual void push(const void *item,
                              sabre::types::MsTime timeout) = 0;
            virtual void pushFromIsr(const void *item) = 0;

            virtual void *pop(sabre::types::MsTime timeout) = 0;
            virtual void *popFromIsr() = 0;

            virtual std::size_t count() const = 0;
            virtual std::size_t capacity() const = 0;
            virtual bool isEmpty() const = 0;
            virtual bool isFull() const = 0;
            virtual void clear() = 0;
        };
    } // namespace os
} // namespace sabre