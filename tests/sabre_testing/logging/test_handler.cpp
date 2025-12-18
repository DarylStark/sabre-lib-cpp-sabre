#include "test_handler.hpp"

namespace sabre::Testing
{
    void TestHandler::handle_log(const LoggingLevel level,
                                 const std::string &logger_name,
                                 const std::string &message)
    {
        _level = level;
        _logger_name = logger_name;
        _message = message;
    }

    sabre::LoggingLevel TestHandler::get_last_level() const
    {
        return _level;
    }

    std::string TestHandler::get_last_logger_name() const
    {
        return _logger_name;
    }

    std::string TestHandler::get_last_message() const
    {
        return _message;
    }
} // namespace sabre::Testing