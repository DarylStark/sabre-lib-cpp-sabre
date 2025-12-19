#pragma once

#include "logging.hpp"
#include <deque>
#include <memory>
#include <ostream>

namespace sabre::log
{
    class OStreamLogHandler : public LogHandler
    {
    public:
        using Ptr = OStreamLogHandler *;
        using SharedPtr = std::shared_ptr<OStreamLogHandler>;
        using UniquePtr = std::unique_ptr<OStreamLogHandler>;

    private:
        std::ostream &_stream;

    public:
        OStreamLogHandler(std::ostream &stream);
        void handleLog(const LoggingLevel level, const std::string &loggerName,
                       const std::string &message) override;
    };

    using LogBufferHandlerBuffer = std::deque<std::string>;
    class LogBufferHandler : public LogHandler
    {
    public:
        using Ptr = LogBufferHandler *;
        using SharedPtr = std::shared_ptr<LogBufferHandler>;
        using UniquePtr = std::unique_ptr<LogBufferHandler>;

    private:
        LogBufferHandlerBuffer _buffer;
        size_t _maxSize;

    public:
        LogBufferHandler(size_t size);
        void handleLog(const LoggingLevel level, const std::string &loggerName,
                       const std::string &message) override;
        const LogBufferHandlerBuffer &getBuffer() const;
    };
} // namespace sabre::log