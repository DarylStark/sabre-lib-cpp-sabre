#pragma once

#include "string_validator.hpp"

namespace sabre::parsers
{
    enum class NMEA_Validation_State
    {
        WAITING_FOR_START,
        WAITING_FOR_END,
        ACCEPTED,
        ERROR
    };

    class NMEAValidator : public StringValidator
    {
    private:
        std::string _nmea_sentence;
        NMEA_Validation_State _state;

    public:
        NMEAValidator();
        ~NMEAValidator();

        void add_character(char character);

        void reset();
        std::string get_buffer() const;

        bool is_error() const;
        bool is_accepted() const;
        bool is_started() const;
    };
} // namespace sabre::parsers