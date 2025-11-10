#include "gps.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

namespace sabre
{
    namespace models
    {

        Coordinate::Coordinate()
            : _coordinate(0), _type(CoordinateType::LATITUDE)
        {
        }

        Coordinate::Coordinate(uint16_t degrees, uint16_t minutes,
                               double seconds, CoordinatesDirection direction)
        {
            _coordinate = degrees + (static_cast<double>(minutes) / 60.0) +
                          (seconds / 3600.0);
            if (direction == CoordinatesDirection::SOUTH ||
                direction == CoordinatesDirection::WEST)
                _coordinate = -_coordinate;

            _type = CoordinateType::LONGITUDE;
            if (direction == CoordinatesDirection::NORTH ||
                direction == CoordinatesDirection::SOUTH)
                _type = CoordinateType::LATITUDE;
        }

        Coordinate::Coordinate(uint16_t degrees, float minutes,
                               CoordinatesDirection direction)
        {
            _coordinate = degrees + (static_cast<double>(minutes) / 60.0);
            if (direction == CoordinatesDirection::SOUTH ||
                direction == CoordinatesDirection::WEST)
                _coordinate = -_coordinate;

            _type = CoordinateType::LONGITUDE;
            if (direction == CoordinatesDirection::NORTH ||
                direction == CoordinatesDirection::SOUTH)
                _type = CoordinateType::LATITUDE;
        }

        Coordinate::Coordinate(double coordinate, CoordinateType type)
            : _coordinate(coordinate), _type(type)
        {
        }

        double Coordinate::get_dd() const
        {
            return _coordinate;
        }

        CoordinateType Coordinate::get_type() const
        {
            return _type;
        }

        CoordinatesDirection Coordinate::get_direction() const
        {

            if (_type == CoordinateType::LONGITUDE)
                return _coordinate >= 0 ? CoordinatesDirection::EAST
                                        : CoordinatesDirection::WEST;
            return _coordinate >= 0 ? CoordinatesDirection::NORTH
                                    : CoordinatesDirection::SOUTH;
        }

        uint16_t Coordinate::get_degrees() const
        {
            return static_cast<uint16_t>(std::floor(std::abs(_coordinate)));
        }

        uint16_t Coordinate::get_minutes() const
        {
            double abs_coord = std::abs(_coordinate);
            double fractional = abs_coord - std::floor(abs_coord);
            return static_cast<uint16_t>(std::floor(fractional * 60.0));
        }

        double Coordinate::get_seconds() const
        {
            double abs_coord = std::abs(_coordinate);
            double fractional = abs_coord - std::floor(abs_coord);
            double minutes = fractional * 60.0;
            double min_fractional = minutes - std::floor(minutes);
            // Round to nearest millisecond for higher precision
            return std::round(min_fractional * 60.0 * 1000.0) / 1000.0;
        }

        Position::Position() : _latitude(), _longitude() {}

        Position::Position(Coordinate latitude, Coordinate longitude)
            : _latitude(latitude), _longitude(longitude)
        {
        }

        Coordinate Position::get_latitude() const
        {
            return _latitude;
        }

        Coordinate Position::get_longitude() const
        {
            return _longitude;
        }

        Distance::Distance() : _distance_in_mm(0) {}

        Distance::Distance(uint64_t distance_in_mm)
            : _distance_in_mm(distance_in_mm)
        {
        }

        uint64_t Distance::millimeters() const
        {
            return _distance_in_mm;
        }

        float Distance::centimeters() const
        {
            return static_cast<float>(_distance_in_mm) / 10.0f;
        }

        float Distance::meters() const
        {
            return static_cast<float>(_distance_in_mm) / 1000.0f;
        }

        float Distance::kilometers() const
        {
            return static_cast<float>(_distance_in_mm) / 1'000'000.0f;
        }

        Distance::operator uint64_t() const
        {
            return _distance_in_mm;
        }

        Distance Position::get_distance(const Position &other) const
        {
            const double R = 6371000; // Radius of the Earth in meters
            double lat1_rad = _latitude.get_dd() * M_PI / 180.0;
            double lat2_rad = other._latitude.get_dd() * M_PI / 180.0;
            double delta_lat =
                (other._latitude.get_dd() - _latitude.get_dd()) * M_PI / 180.0;
            double delta_lon =
                (other._longitude.get_dd() - _longitude.get_dd()) * M_PI /
                180.0;

            double a = std::sin(delta_lat / 2) * std::sin(delta_lat / 2) +
                       std::cos(lat1_rad) * std::cos(lat2_rad) *
                           std::sin(delta_lon / 2) * std::sin(delta_lon / 2);
            double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

            return Distance(static_cast<uint64_t>(R * c * 100.0 * 10.0));
        }

        bool Position::is_valid() const
        {
            return _latitude.get_dd() != 0.0 || _longitude.get_dd() != 0.0;
        }
    } // namespace models

    namespace parsers
    {
        NMEA_Parser::NMEA_Parser() : _last_position() {}

        std::string NMEA_Parser::_get_type(std::string scentence) const
        {
            return std::string(scentence.substr(3, 3));
        }

        std::string NMEA_Parser::_get_talker(std::string scentence) const
        {
            return std::string(scentence.substr(1, 2));
        }

        bool NMEA_Parser::_is_valid_checksum(const std::string &scentence) const
        {
            uint32_t total_xor = 0;

            size_t asterisk_pos = scentence.find('*');
            if (asterisk_pos == std::string::npos ||
                asterisk_pos + 2 >= scentence.size())
                return false;

            size_t dollar_pos = scentence.find('$');
            if (dollar_pos == std::string::npos ||
                dollar_pos + 1 >= asterisk_pos)
                return false;

            for (size_t pos = dollar_pos + 1; pos < asterisk_pos; ++pos)
                total_xor ^= static_cast<uint8_t>(scentence[pos]);

            std::string checksum_str = scentence.substr(asterisk_pos + 1, 2);
            uint32_t sentence_checksum = std::stoul(checksum_str, nullptr, 16);
            return total_xor == sentence_checksum;
        }

        std::vector<std::string>
        NMEA_Parser::_get_fields(std::string scentence) const
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
        bool NMEA_Parser::_extract_position_from_fields(
            const std::vector<std::string> &fields, size_t lat_idx,
            size_t lat_dir_idx, size_t lon_idx, size_t lon_dir_idx,
            models::Position &out_position) const
        {
            static const std::map<char, models::CoordinatesDirection> dir_map =
                {{'N', models::CoordinatesDirection::NORTH},
                 {'S', models::CoordinatesDirection::SOUTH},
                 {'E', models::CoordinatesDirection::EAST},
                 {'W', models::CoordinatesDirection::WEST}};

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

            out_position = models::Position(
                models::Coordinate(lat_deg, lat_min, dir_map.at(lat_dir)),
                models::Coordinate(lon_deg, lon_min, dir_map.at(lon_dir)));
            return true;
        }

        bool NMEA_Parser::_parse_rmc(std::string scentence)
        {
            auto fields = _get_fields(scentence);
            if (fields.size() < 13 || fields[2] != "A")
                return false;
            models::Position pos;
            if (!_extract_position_from_fields(fields, 3, 4, 5, 6, pos))
                return false; // LCOV_EXCL_LINE
            _last_position = pos;
            return true;
        }

        bool NMEA_Parser::_parse_gll(std::string scentence)
        {
            auto fields = _get_fields(scentence);
            if (fields.size() < 8 || fields[6] != "A")
                return false;
            models::Position pos;
            if (!_extract_position_from_fields(fields, 1, 2, 3, 4, pos))
                return false; // LCOV_EXCL_LINE
            _last_position = pos;
            return true;
        }

        bool NMEA_Parser::_parse_gga(std::string scentence)
        {
            auto fields = _get_fields(scentence);
            if (fields.size() < 15 || fields[6] == "0")
                return false;
            models::Position pos;
            if (!_extract_position_from_fields(fields, 2, 3, 4, 5, pos))
                return false; // LCOV_EXCL_LINE
            _last_position = pos;
            return true;
        }

        void NMEA_Parser::add_scentence(const std::string &scentence)
        {
            std::string type = _get_type(scentence);
            std::string talker = _get_talker(scentence);
            std::string full_type = talker + type;

            if (!_is_valid_checksum(scentence))
                return;

            if (_scentences.find(full_type) != _scentences.end())
                parse();

            _scentences[full_type] = scentence;

            if (type == "RMC")
                parse();
        }

        void NMEA_Parser::parse()
        {
            using ParseFunc = bool (NMEA_Parser::*)(std::string);
            // Priority list: pair of sentence type and member function pointer

            // LCOV_EXCL_START
            static const std::vector<std::pair<std::string, ParseFunc>>
                priorities = {{"GNRMC", &NMEA_Parser::_parse_rmc},
                              {"GNGLL", &NMEA_Parser::_parse_gll},
                              {"GNGGA", &NMEA_Parser::_parse_gga},
                              {"GPRMC", &NMEA_Parser::_parse_rmc},
                              {"GPGLL", &NMEA_Parser::_parse_gll},
                              {"GPGGA", &NMEA_Parser::_parse_gga},
                              {"BDRMC", &NMEA_Parser::_parse_rmc},
                              {"BDGLL", &NMEA_Parser::_parse_gll},
                              {"BDGGA", &NMEA_Parser::_parse_gga},
                              {"GLRMC", &NMEA_Parser::_parse_rmc},
                              {"GLGLL", &NMEA_Parser::_parse_gll},
                              {"GLGGA", &NMEA_Parser::_parse_gga},
                              {"GARMC", &NMEA_Parser::_parse_rmc},
                              {"GAGLL", &NMEA_Parser::_parse_gll},
                              {"GAGGA", &NMEA_Parser::_parse_gga}};
            // LCOV_EXCL_STOP

            bool valid = false;
            for (const auto &[type, func] : priorities)
            {
                auto it = _scentences.find(type);
                if (it != _scentences.end())
                {
                    valid = (this->*func)(it->second);
                    if (valid)
                        break;
                }
            }

            _scentences.clear();
        }

        Position NMEA_Parser::get_last_position() const
        {
            return _last_position;
        }

        size_t NMEA_Parser::get_scentence_count() const
        {
            return _scentences.size();
        }
    } // namespace parsers
} // namespace sabre