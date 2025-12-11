#pragma once

#include "logging.hpp"
#include <deque>
#include <memory>
#include <ostream>

namespace Sabre
{
    class OStreamLogHandler : public LogHandler
    {
    private:
        std::ostream &_stream;

    public:
        OStreamLogHandler(std::ostream &stream);
        void handle_log(const LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message) override;
    };
    using OStreamLogHandlerPtr = OStreamLogHandler *;
    using OStreamLogHandlerSharedPtr = std::shared_ptr<OStreamLogHandler>;
    using OStreamLogHandlerUniquePtr = std::unique_ptr<OStreamLogHandler>;

    using LogBufferHandlerBuffer = std::deque<std::string>;
    class LogBufferHandler : public LogHandler
    {
    private:
        LogBufferHandlerBuffer _buffer;
        size_t _max_size;

    public:
        LogBufferHandler(size_t size);
        void handle_log(const LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message) override;
        const LogBufferHandlerBuffer &get_buffer() const;
    };
    using LogBufferHandlerPtr = LogBufferHandler *;
    using LogBufferHandlerSharedPtr = std::shared_ptr<LogBufferHandler>;
    using LogBufferHandlerUniquePtr = std::unique_ptr<LogBufferHandler>;
} // namespace Sabre