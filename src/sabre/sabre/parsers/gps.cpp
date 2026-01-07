#include "gps.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

namespace sabre::parsers
{

    std::string NmeaParser::_get_type(const std::string &scentence) const
    {
        return std::string(scentence.substr(3, 3));
    }

    std::string NmeaParser::_get_talker(const std::string &scentence) const
    {
        return std::string(scentence.substr(1, 2));
    }

    bool NmeaParser::_is_valid_checksum(const std::string &scentence) const
    {
        uint32_t total_xor = 0;

        size_t asterisk_pos = scentence.find('*');
        if (asterisk_pos == std::string::npos ||
            asterisk_pos + 2 >= scentence.size())
            return false;

        size_t dollar_pos = scentence.find('$');
        if (dollar_pos == std::string::npos || dollar_pos + 1 >= asterisk_pos)
            return false;

        for (size_t pos = dollar_pos + 1; pos < asterisk_pos; ++pos)
            total_xor ^= static_cast<uint8_t>(scentence[pos]);

        std::string checksum_str = scentence.substr(asterisk_pos + 1, 2);
        uint32_t sentence_checksum = std::stoul(checksum_str, nullptr, 16);
        return total_xor == sentence_checksum;
    }

    std::vector<std::string>
    NmeaParser::_get_fields(const std::string &scentence) const
    {
        std::vector<std::string> fields;
        size_t start = 0;
        size_t end = scentence.find(',');

        while (end != std::string::npos)
        {
            fields.push_back(scentence.substr(start, end - start));
            start = end + 1;
            end = scentence.find(',', start);
        }
        fields.push_back(scentence.substr(start));

        return fields;
    }

    // Helper to parse coordinates from NMEA fields
    bool NmeaParser::_extractPositionFromFields(
        const std::vector<std::string> &fields, size_t lat_idx,
        size_t lat_dir_idx, size_t lon_idx, size_t lon_dir_idx,
        models::geo::Position &out_position) const
    {
        static const std::map<char, models::geo::CoordinatesDirection> dir_map =
            {{'N', models::geo::CoordinatesDirection::NORTH},
             {'S', models::geo::CoordinatesDirection::SOUTH},
             {'E', models::geo::CoordinatesDirection::EAST},
             {'W', models::geo::CoordinatesDirection::WEST}};
        if (fields.size() <=
            std::max({lat_idx, lat_dir_idx, lon_idx, lon_dir_idx}))
            return false; // LCOV_EXCL_LINE

        const std::string &lat_str = fields[lat_idx];
        const std::string &lon_str = fields[lon_idx];
        if (lat_str.empty() || lon_str.empty())
            return false; // LCOV_EXCL_LINE

        uint16_t lat_deg = std::stoi(lat_str.substr(0, 2));
        double lat_min = std::stod(lat_str.substr(2));
        char lat_dir = fields[lat_dir_idx][0];

        uint16_t lon_deg = std::stoi(lon_str.substr(0, 3));
        double lon_min = std::stod(lon_str.substr(3));
        char lon_dir = fields[lon_dir_idx][0];

        out_position = models::geo::Position(
            models::geo::Coordinate(lat_deg, lat_min, dir_map.at(lat_dir)),
            models::geo::Coordinate(lon_deg, lon_min, dir_map.at(lon_dir)));
        return true;
    }

    void NmeaParser::_updateLastPosition(Position &new_position)
    {
        if (new_position == _last_position)
            return;

        uint32_t version = _last_position.getVersion();
        _last_position = new_position;
        _last_position.setVersion(version + 1);
    }

    bool NmeaParser::_parse_rmc(const std::string &scentence)
    {
        auto fields = _get_fields(scentence);
        if (fields.size() < 13 || fields[2] != "A")
            return false;
        models::geo::Position pos;
        if (!_extractPositionFromFields(fields, 3, 4, 5, 6, pos))
            return false; // LCOV_EXCL_LINE
        _updateLastPosition(pos);
        return true;
    }

    bool NmeaParser::_parse_gll(const std::string &scentence)
    {
        auto fields = _get_fields(scentence);
        if (fields.size() < 8 || fields[6] != "A")
            return false;
        models::geo::Position pos;
        if (!_extractPositionFromFields(fields, 1, 2, 3, 4, pos))
            return false; // LCOV_EXCL_LINE
        _updateLastPosition(pos);
        return true;
    }

    bool NmeaParser::_parse_gga(const std::string &scentence)
    {
        auto fields = _get_fields(scentence);
        if (fields.size() < 15 || fields[6] == "0")
            return false;
        models::geo::Position pos;
        if (!_extractPositionFromFields(fields, 2, 3, 4, 5, pos))
            return false; // LCOV_EXCL_LINE
        _updateLastPosition(pos);
        return true;
    }

    void NmeaParser::addSentence(const std::string &scentence)
    {
        std::string type = _get_type(scentence);
        std::string talker = _get_talker(scentence);
        std::string full_type = talker + type;

        if (!_is_valid_checksum(scentence))
            return;

        if (_sentences.find(full_type) != _sentences.end())
            parse();

        _sentences[full_type] = scentence;

        if (type == "RMC")
            parse();
    }

    void NmeaParser::parse()
    {
        using ParseFunc = bool (NmeaParser::*)(const std::string &);
        // Priority list: pair of sentence type and member function pointer

        // LCOV_EXCL_START
        static const std::vector<std::pair<std::string, ParseFunc>> priorities =
            {{"GNRMC", &NmeaParser::_parse_rmc},
             {"GNGLL", &NmeaParser::_parse_gll},
             {"GNGGA", &NmeaParser::_parse_gga},
             {"GPRMC", &NmeaParser::_parse_rmc},
             {"GPGLL", &NmeaParser::_parse_gll},
             {"GPGGA", &NmeaParser::_parse_gga},
             {"BDRMC", &NmeaParser::_parse_rmc},
             {"BDGLL", &NmeaParser::_parse_gll},
             {"BDGGA", &NmeaParser::_parse_gga},
             {"GLRMC", &NmeaParser::_parse_rmc},
             {"GLGLL", &NmeaParser::_parse_gll},
             {"GLGGA", &NmeaParser::_parse_gga},
             {"GARMC", &NmeaParser::_parse_rmc},
             {"GAGLL", &NmeaParser::_parse_gll},
             {"GAGGA", &NmeaParser::_parse_gga}};
        // LCOV_EXCL_STOP

        bool valid = false;
        for (const auto &[type, func] : priorities)
        {
            auto it = _sentences.find(type);
            if (it != _sentences.end())
            {
                valid = (this->*func)(it->second);
                if (valid)
                    break;
            }
        }

        _sentences.clear();
    }

    Position NmeaParser::getLastPosition() const
    {
        return _last_position;
    }

    size_t NmeaParser::getSentenceCount() const
    {
        return _sentences.size();
    }
} // namespace sabre::parsers