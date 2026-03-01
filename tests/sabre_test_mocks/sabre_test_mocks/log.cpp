#include "log.hpp"

namespace sabre::impl::sabre_test_mocks
{
    TestHandler::TestHandler(sabre::log::LoggingLevel &levelStorage,
                             std::string &loggerNameStorage,
                             std::string &messageStorage)
        : _level(levelStorage), _logger_name(loggerNameStorage),
          _message(messageStorage)
    {
    }

    void TestHandler::handleLog(const sabre::log::LoggingLevel level,
                                const std::string &loggerName,
                                const std::string &message)
    {
        _level = level;
        _logger_name = loggerName;
        _message = message;
    }

} // namespace sabre::impl::sabre_test_mocks