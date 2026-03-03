#pragma once

#include <sabre/log/logging.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class TestHandler : public sabre::log::LogHandler
    {
    private:
        sabre::log::LoggingLevel &_level;
        std::string &_logger_name;
        std::string &_message;

    public:
        TestHandler(sabre::log::LoggingLevel &levelStorage,
                    std::string &loggerNameStorage,
                    std::string &messageStorage);
        void handleLog(const sabre::log::LoggingLevel level,
                       const std::string &loggerName,
                       const std::string &message);
    };
} // namespace sabre::impl::sabre_test_mocks