#pragma once

#include <string>

namespace sabre::parsers
{
    class StringValidator
    {
    public:
        virtual ~StringValidator() = default;

        virtual void add_character(char character) = 0;

        virtual void reset() = 0;
        virtual std::string get_buffer() const = 0;

        virtual bool is_error() const = 0;
        virtual bool is_accepted() const = 0;
        virtual bool is_started() const = 0;
    };
} // namespace sabre::parsers