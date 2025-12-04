#pragma once

#include <sabre/logging/logging.hpp>

namespace sabre::testing
{
    class TestHandler : public sabre::LogHandler
    {
    private:
        sabre::LoggingLevel _level;
        std::string _logger_name;
        std::string _message;

    public:
        void handle_log(const sabre::LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message);
        sabre::LoggingLevel get_last_level() const;
        std::string get_last_logger_name() const;
        std::string get_last_message() const;
    };
} // namespace sabre::testing