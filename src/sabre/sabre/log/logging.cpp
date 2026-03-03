#include "logging.hpp"
#include "../core/exceptions.hpp"

namespace sabre::log
{
    Logger::Logger(LogManager &manager, const std::string &name)
        : _manager(manager), _name(name)
    {
    }

    void Logger::log(const LoggingLevel level, const std::string &message)
    {
        _manager.log(level, _name, message);
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

    Logger LogManager::getLogger(const std::string &name)
    {
        return Logger(*this, name);
    }

    void LogHelper::createLogger(LogManager &logManager,
                                 const std::string &name)
    {
        _logger = std::make_unique<Logger>(logManager, name);
    }

    void LogHelper::log(LoggingLevel level, const std::string &message)
    {
        if (_logger)
            _logger->log(level, message);
    }

    void LogHelper::reset()
    {
        _logger.reset();
    }
} // namespace sabre::log