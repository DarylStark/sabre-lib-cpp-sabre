#include "os_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre
{
    namespace core
    {
        OsResourceManager::OsResourceManager(Factory &factory,
                                             sabre::log::LogManager &logManager)
            : _factory(factory), _logManager(logManager)
        {
        }

        void OsResourceManager::configureQueue(const std::string &identifier,
                                               std::size_t capacity,
                                               std::size_t elementSize)
        {
            auto it = _queues.find(identifier);
            if (it != _queues.end())
            {
                throw QueueAlreadyConfiguredException("Queue " + identifier +
                                                      " is already configured");
            }
            _queues[identifier] = _factory.createQueue(capacity, elementSize);
            _queues[identifier]->getLogHelper().createLogger(
                _logManager, "Queue_" + identifier);
        }

        sabre::os::Queue &
        OsResourceManager::getQueue(const std::string &identifier) const
        {
            auto it = _queues.find(identifier);
            if (it == _queues.end())
            {
                throw QueueNotConfiguredException("Queue " + identifier +
                                                  " is not configured yet.");
            }
            return *it->second;
        }
    } // namespace core
} // namespace sabre