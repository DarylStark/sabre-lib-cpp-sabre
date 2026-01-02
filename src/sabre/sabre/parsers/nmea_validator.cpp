#include "nmea_validator.hpp"

namespace sabre::parsers
{
    NmeaValidator::NmeaValidator()
        : _state(NmeaValidationState::WAITING_FOR_START)
    {
        _NmeaSentence.reserve(82);
    }

    NmeaValidator::~NmeaValidator() {}

    void NmeaValidator::addCharacter(char character)
    {
        if (_state == NmeaValidationState::WAITING_FOR_START)
        {
            if (character == '$')
            {
                _state = NmeaValidationState::WAITING_FOR_END;
                _NmeaSentence.push_back(character);
            }
        }
        else if (_state == NmeaValidationState::WAITING_FOR_END)
        {
            if (character == '\r' || character == '\n')
                _state = NmeaValidationState::ACCEPTED;
            else if (character == '$' || _NmeaSentence.length() >= 82)
                _state = NmeaValidationState::ERROR;
            else
                _NmeaSentence.push_back(character);
        }
    }

    void NmeaValidator::reset()
    {
        _state = NmeaValidationState::WAITING_FOR_START;
        _NmeaSentence.clear();
    }

    std::string NmeaValidator::getBuffer() const
    {
        return _NmeaSentence;
    }

    bool NmeaValidator::isError() const
    {
        return _state == NmeaValidationState::ERROR;
    }

    bool NmeaValidator::isAccepted() const
    {
        return _state == NmeaValidationState::ACCEPTED;
    }

    bool NmeaValidator::isStarted() const
    {
        return _state == NmeaValidationState::WAITING_FOR_END;
    }
} // namespace sabre::parsers