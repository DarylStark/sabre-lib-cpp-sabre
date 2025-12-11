#pragma once

#include <sabre/logging/logging.hpp>

namespace Sabre::Testing
{
    class TestHandler : public Sabre::LogHandler
    {
    private:
        Sabre::LoggingLevel _level;
        std::string _logger_name;
        std::string _message;

    public:
        void handle_log(const Sabre::LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message);
        Sabre::LoggingLevel get_last_level() const;
        std::string get_last_logger_name() const;
        std::string get_last_message() const;
    };
} // namespace Sabre::Testing