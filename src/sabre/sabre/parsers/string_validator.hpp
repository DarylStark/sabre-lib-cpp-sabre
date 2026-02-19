#pragma once

#include <string>

namespace sabre::parsers
{
    class StringValidator
    {
    public:
        virtual ~StringValidator() noexcept = default;

        virtual void addCharacter(char character) = 0;

        virtual void reset() noexcept = 0;
        virtual std::string getBuffer() const = 0;

        virtual bool isError() const noexcept = 0;
        virtual bool isAccepted() const noexcept = 0;
        virtual bool isStarted() const noexcept = 0;
    };
} // namespace sabre::parsers