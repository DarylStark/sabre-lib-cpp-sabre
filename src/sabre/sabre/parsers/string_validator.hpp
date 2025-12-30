#pragma once

#include <string>

namespace sabre::parsers
{
    class StringValidator
    {
    public:
        virtual ~StringValidator() = default;

        virtual void addCharacter(char character) = 0;

        virtual void reset() = 0;
        virtual std::string getBuffer() const = 0;

        virtual bool isError() const = 0;
        virtual bool isAccepted() const = 0;
        virtual bool isStarted() const = 0;
    };
} // namespace sabre::parsers