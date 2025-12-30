#include "log.hpp"

namespace sabre::impl::sabre_test_mocks
{
    void TestHandler::handleLog(const LoggingLevel level,
                                const std::string &loggerName,
                                const std::string &message)
    {
        _level = level;
        _logger_name = loggerName;
        _message = message;
    }

    LoggingLevel TestHandler::getLastLevel() const
    {
        return _level;
    }

    std::string TestHandler::getLastLoggerName() const
    {
        return _logger_name;
    }

    std::string TestHandler::getLastMessage() const
    {
        return _message;
    }
} // namespace sabre::impl::sabre_test_mocks