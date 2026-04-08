#pragma once

#include "../os/queue.hpp"
#include "factory.hpp"
#include <unordered_map>

namespace sabre::core
{
    class OsResourceManager
    {
    private:
        Factory &_factory;
        sabre::log::LogManager &_logManager;

        std::unordered_map<std::string, sabre::os::Queue::UniquePtr> _queues;

    public:
        OsResourceManager(Factory &factory, sabre::log::LogManager &logManager);
        void configureQueue(const std::string &identifier, std::size_t capacity,
                            std::size_t elementSize);
        sabre::os::Queue &getQueue(const std::string &identifier) const;
    };
} // namespace sabre::core