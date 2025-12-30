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
        std::string _NmeaSentence;
        NmeaValidationState _state;

    public:
        NmeaValidator();
        ~NmeaValidator();

        void addCharacter(char character);

        void reset();
        std::string getBuffer() const;

        bool isError() const;
        bool isAccepted() const;
        bool isStarted() const;
    };
} // namespace sabre::parsers