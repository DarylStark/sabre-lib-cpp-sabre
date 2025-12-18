#include "nmea_validator.hpp"

namespace sabre::parsers
{
    NMEAValidator::NMEAValidator()
        : _state(NMEA_Validation_State::WAITING_FOR_START)
    {
        _nmea_sentence.reserve(82);
    }

    NMEAValidator::~NMEAValidator() {}

    void NMEAValidator::add_character(char character)
    {
        if (_state == NMEA_Validation_State::WAITING_FOR_START)
        {
            if (character == '$')
            {
                _state = NMEA_Validation_State::WAITING_FOR_END;
                _nmea_sentence.push_back(character);
            }
        }
        else if (_state == NMEA_Validation_State::WAITING_FOR_END)
            if (character == '\r' || character == '\n')
                _state = NMEA_Validation_State::ACCEPTED;
            else if (character == '$' || _nmea_sentence.length() >= 82)
                _state = NMEA_Validation_State::ERROR;
            else
                _nmea_sentence.push_back(character);
    }

    void NMEAValidator::reset()
    {
        _state = NMEA_Validation_State::WAITING_FOR_START;
        _nmea_sentence.clear();
    }

    std::string NMEAValidator::get_buffer() const
    {
        return _nmea_sentence;
    }

    bool NMEAValidator::is_error() const
    {
        return _state == NMEA_Validation_State::ERROR;
    }

    bool NMEAValidator::is_accepted() const
    {
        return _state == NMEA_Validation_State::ACCEPTED;
    }

    bool NMEAValidator::is_started() const
    {
        return _state == NMEA_Validation_State::WAITING_FOR_END;
    }
} // namespace sabre::parsers