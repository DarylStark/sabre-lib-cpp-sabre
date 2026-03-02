#include "logging.hpp"
#include "../core/exceptions.hpp"

namespace sabre::log
{
    Logger::Logger(const std::string &name) : _name(name) {}

    void Logger::log(const LoggingLevel level, const std::string &message)
    {
        // TODO: Log to locally configured logger
    }

    void LogManager::setLevel(LoggingLevel level)
    {
        _level = level;
    }

    LoggingLevel LogManager::getLevel()
    {
        return _level;
    }

    void LogManager::log(const LoggingLevel level,
                         const std::string &loggerName,
                         const std::string &message)
    {
        if (level <= _level)
            for (const auto &pair : _handlers)
                pair.second->handleLog(level, loggerName, message);
    }

    void LogManager::log(const LoggingLevel level, const std::string &message)
    {
        log(level, "", message);
    }

    void LogManager::addHandler(const std::string &identifier,
                                LogHandler::UniquePtr handler)
    {
        _handlers[identifier] = std::move(handler);
    }

    void LogManager::removeHandler(const std::string &identifier)
    {
        _handlers.erase(identifier);
    }

    size_t LogManager::getHandlerCount() const
    {
        return _handlers.size();
    }

    LogHandler::UniquePtr &LogManager::getHandler(const std::string &identifier)
    {
        if (_handlers.find(identifier) == _handlers.end())
        {
            // TODO: Custom exception
            throw sabre::core::LogHandlerNotAvailableException(
                "LogHandler not available");
        }
        return _handlers.at(identifier);
    }
} // namespace sabre::log