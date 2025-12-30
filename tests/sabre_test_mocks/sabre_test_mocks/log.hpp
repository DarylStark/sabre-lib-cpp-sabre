#pragma once

#include <sabre/log/logging.hpp>

namespace sabre::impl::sabre_test_mocks
{
    using sabre::log::LoggingLevel;

    class TestHandler : public sabre::log::LogHandler
    {
    private:
        LoggingLevel _level;
        std::string _logger_name;
        std::string _message;

    public:
        void handleLog(const LoggingLevel level, const std::string &loggerName,
                       const std::string &message);
        LoggingLevel getLastLevel() const;
        std::string getLastLoggerName() const;
        std::string getLastMessage() const;
    };
} // namespace sabre::impl::sabre_test_mocks