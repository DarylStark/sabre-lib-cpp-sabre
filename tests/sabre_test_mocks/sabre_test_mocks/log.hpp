#pragma once

#include <sabre/log/logging.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class TestHandler : public sabre::log::LogHandler
    {
    private:
        sabre::log::LoggingLevel _level;
        std::string _logger_name;
        std::string _message;

    public:
        void handleLog(const sabre::log::LoggingLevel level,
                       const std::string &loggerName,
                       const std::string &message);
        sabre::log::LoggingLevel getLastLevel() const;
        std::string getLastLoggerName() const;
        std::string getLastMessage() const;
    };
} // namespace sabre::impl::sabre_test_mocks