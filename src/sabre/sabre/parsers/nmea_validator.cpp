#include "nmea_validator.hpp"

namespace sabre::parsers
{
    NmeaValidator::NmeaValidator()
        : _state(NmeaValidationState::WAITING_FOR_START)
    {
        _nmea_sentence.reserve(82);
    }

    NmeaValidator::~NmeaValidator() {}

    void NmeaValidator::add_character(char character)
    {
        if (_state == NmeaValidationState::WAITING_FOR_START)
        {
            if (character == '$')
            {
                _state = NmeaValidationState::WAITING_FOR_END;
                _nmea_sentence.push_back(character);
            }
        }
        else if (_state == NmeaValidationState::WAITING_FOR_END)
            if (character == '\r' || character == '\n')
                _state = NmeaValidationState::ACCEPTED;
            else if (character == '$' || _nmea_sentence.length() >= 82)
                _state = NmeaValidationState::ERROR;
            else
                _nmea_sentence.push_back(character);
    }

    void NmeaValidator::reset()
    {
        _state = NmeaValidationState::WAITING_FOR_START;
        _nmea_sentence.clear();
    }

    std::string NmeaValidator::get_buffer() const
    {
        return _nmea_sentence;
    }

    bool NmeaValidator::is_error() const
    {
        return _state == NmeaValidationState::ERROR;
    }

    bool NmeaValidator::is_accepted() const
    {
        return _state == NmeaValidationState::ACCEPTED;
    }

    bool NmeaValidator::is_started() const
    {
        return _state == NmeaValidationState::WAITING_FOR_END;
    }
} // namespace sabre::parsers