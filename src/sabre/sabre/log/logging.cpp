#include "logging.hpp"

namespace sabre::log
{
    Logger::Logger(const std::string &name) : _name(name) {}

    void Logger::log(const LoggingLevel level, const std::string &message)
    {
        // TODO: Log to locally configured logger
    }

    void Logger::debug(const std::string &message)
    {
        log(LoggingLevel::DEBUG, message);
    }

    void Logger::info(const std::string &message)
    {
        log(LoggingLevel::INFO, message);
    }

    void Logger::notice(const std::string &message)
    {
        log(LoggingLevel::NOTICE, message);
    }

    void Logger::warning(const std::string &message)
    {
        log(LoggingLevel::WARNING, message);
    }

    void Logger::error(const std::string &message)
    {
        log(LoggingLevel::ERROR, message);
    }

    void Logger::critical(const std::string &message)
    {
        log(LoggingLevel::CRITICAL, message);
    }

    void Logger::alert(const std::string &message)
    {
        log(LoggingLevel::ALERT, message);
    }

    void Logger::emergency(const std::string &message)
    {
        log(LoggingLevel::EMERGENCY, message);
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
} // namespace sabre::log