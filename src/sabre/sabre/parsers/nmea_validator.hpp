#pragma once

#include "string_validator.hpp"

namespace sabre::parsers
{
    enum class NmeaValidationState
    {
        WAITING_FOR_START,
        WAITING_FOR_END,
        ACCEPTED,
        ERROR
    };

    class NmeaValidator : public StringValidator
    {
    private:
        std::string _nmea_sentence;
        NmeaValidationState _state;

    public:
        NmeaValidator();
        ~NmeaValidator();

        void add_character(char character);

        void reset();
        std::string get_buffer() const;

        bool is_error() const;
        bool is_accepted() const;
        bool is_started() const;
    };
} // namespace sabre::parsers