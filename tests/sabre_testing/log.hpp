#pragma once

#include <sabre/log/logging.hpp>

namespace sabre::impl::sabre_testing
{
    using sabre::log::LoggingLevel;

    class TestHandler : public sabre::log::LogHandler
    {
    private:
        LoggingLevel _level;
        std::string _logger_name;
        std::string _message;

    public:
        void handleLog(const LoggingLevel level, const std::string &logger_name,
                       const std::string &message);
        LoggingLevel get_last_level() const;
        std::string get_last_logger_name() const;
        std::string get_last_message() const;
    };
} // namespace sabre::impl::sabre_testing