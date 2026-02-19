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
        NmeaValidator() noexcept;
        ~NmeaValidator() noexcept;

        void addCharacter(char character) noexcept;

        void reset() noexcept;
        std::string getBuffer() const noexcept;

        bool isError() const noexcept;
        bool isAccepted() const noexcept;
        bool isStarted() const noexcept;
    };
} // namespace sabre::parsers