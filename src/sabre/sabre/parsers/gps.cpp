#include "gps.hpp"
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
            _coordinate = degrees + (static_cast<double>(minutes) / 60) +
                          (seconds / 3600);
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
            _coordinate = degrees + (minutes / 60.0f);
            if (direction == CoordinatesDirection::SOUTH ||
                direction == CoordinatesDirection::WEST)
                _coordinate = -_coordinate;

            _type = CoordinateType::LONGITUDE;
            if (direction == CoordinatesDirection::NORTH ||
                direction == CoordinatesDirection::SOUTH)
                _type = CoordinateType::LATITUDE;
        }

        Coordinate::Coordinate(float coordinate, CoordinateType type)
            : _coordinate(coordinate), _type(type)
        {
        }

        float Coordinate::get_dd() const
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

        float Coordinate::get_seconds() const
        {
            double abs_coord = std::abs(_coordinate);
            double fractional = abs_coord - std::floor(abs_coord);
            double minutes = fractional * 60.0;
            double min_fractional = minutes - std::floor(minutes);
            return static_cast<float>(min_fractional * 60.0);
        }

        // TODO: Remove when `Coordinate` is done
        Coordinates::Coordinates(uint16_t degrees, double minutes,
                                 CoordinatesDirection direction)
            : _degrees(degrees), _minutes(minutes), _direction(direction)
        {
        }

        double Coordinates::to_decimal() const
        {
            double decimal = _degrees + (_minutes / 60.0f);
            if (_direction == CoordinatesDirection::SOUTH ||
                _direction == CoordinatesDirection::WEST)
                decimal = -decimal;
            return decimal;
        }
    } // namespace models

    namespace parsers
    {

        GGLData::GGLData(bool valid, Coordinates latitude,
                         Coordinates longitude)
            : valid(valid), latitude(latitude), longitude(longitude)
        {
        }

        bool GGLData::is_valid() const
        {
            return valid;
        }

        Coordinates GGLData::get_latitude() const
        {
            return latitude;
        }
        Coordinates GGLData::get_longitude() const
        {
            return longitude;
        }

        RMCData::RMCData(bool valid, Coordinates latitude,
                         Coordinates longitude)
            : valid(valid), latitude(latitude), longitude(longitude)
        {
        }

        bool RMCData::is_valid() const
        {
            return valid;
        }

        Coordinates RMCData::get_latitude() const
        {
            return latitude;
        }

        Coordinates RMCData::get_longitude() const
        {
            return longitude;
        }

        GPSData::GPSData() : ggl(nullptr) {}

        bool GPSData::is_valid() const
        {
            return ggl != nullptr && (rmc->is_valid() || ggl->is_valid());
        }

        NMEA::NMEA() : _is_parsed(false), _last_data("") {}

        void NMEA::set_data(const std::string data)
        {
            _last_data = data;
            _is_parsed = false;
        }

        std::shared_ptr<GGLData> NMEA::_parse_ggl()
        {
            // Find the complete GGL sentence
            size_t start = _last_data.find("$GNGLL");
            if (start == std::string::npos)
                return std::make_shared<GGLData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));

            size_t end = _last_data.find("\n", start);
            if (end == std::string::npos)
                end = _last_data.length();

            std::string ggl_sentence = _last_data.substr(start, end - start);
            // Parse the GGL sentence
            // Example: $GPGGL,4916.45,N,12311.12,W,225444,A,*1D
            std::vector<std::string> fields;
            size_t pos = 0;
            while ((pos = ggl_sentence.find(',')) != std::string::npos)
            {
                fields.push_back(ggl_sentence.substr(0, pos));
                ggl_sentence.erase(0, pos + 1);
            }
            fields.push_back(ggl_sentence);

            if (fields.size() < 7)
                return std::make_shared<GGLData>(
                    false, Coordinates(0, 0.0f, CoordinatesDirection::NORTH),
                    Coordinates(0, 0.0f, CoordinatesDirection::WEST));

            // Latitude
            std::string lat_str = fields[1];
            char lat_dir = fields[2][0];
            if (lat_str.length() < 4)
                return std::make_shared<GGLData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));
            uint16_t lat_deg = std::stoi(lat_str.substr(0, 2));
            double lat_min = std::stod(lat_str.substr(2));
            Coordinates latitude =
                Coordinates(lat_deg, lat_min,
                            lat_dir == 'N' ? CoordinatesDirection::NORTH
                                           : CoordinatesDirection::SOUTH);

            // Longitude
            std::string lon_str = fields[3];
            char lon_dir = fields[4][0];
            if (lon_str.length() < 5)
                return std::make_shared<GGLData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));
            uint16_t lon_deg = std::stoi(lon_str.substr(0, 3));
            double lon_min = std::stod(lon_str.substr(3));
            Coordinates longitude =
                Coordinates(lon_deg, lon_min,
                            lon_dir == 'E' ? CoordinatesDirection::EAST
                                           : CoordinatesDirection::WEST);

            // Create new object
            return std::make_shared<GGLData>(fields[6] == "A", latitude,
                                             longitude);
        }

        std::shared_ptr<RMCData> NMEA::_parse_rmc()
        {
            // Find the complete RMC sentence
            size_t start = _last_data.find("$GNRMC");
            if (start == std::string::npos)
                return std::make_shared<RMCData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));

            size_t end = _last_data.find("\n", start);
            if (end == std::string::npos)
                end = _last_data.length();

            std::string rmc_sentence = _last_data.substr(start, end - start);
            std::vector<std::string> fields;
            size_t pos = 0;
            while ((pos = rmc_sentence.find(',')) != std::string::npos)
            {
                fields.push_back(rmc_sentence.substr(0, pos));
                rmc_sentence.erase(0, pos + 1);
            }
            fields.push_back(rmc_sentence);

            if (fields.size() < 12)
                return std::make_shared<RMCData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));

            // Latitude
            std::string lat_str = fields[3];
            char lat_dir = fields[4][0];
            if (lat_str.length() < 4)
                return std::make_shared<RMCData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));
            uint16_t lat_deg = std::stoi(lat_str.substr(0, 2));
            double lat_min = std::stod(lat_str.substr(2));
            Coordinates latitude =
                Coordinates(lat_deg, lat_min,
                            lat_dir == 'N' ? CoordinatesDirection::NORTH
                                           : CoordinatesDirection::SOUTH);

            // Longitude
            std::string lon_str = fields[5];
            char lon_dir = fields[6][0];
            if (lon_str.length() < 5)
                return std::make_shared<RMCData>(false, Coordinates(0, 0.0f),
                                                 Coordinates(0, 0.0f));
            uint16_t lon_deg = std::stoi(lon_str.substr(0, 3));
            double lon_min = std::stod(lon_str.substr(3));
            Coordinates longitude =
                Coordinates(lon_deg, lon_min,
                            lon_dir == 'E' ? CoordinatesDirection::EAST
                                           : CoordinatesDirection::WEST);

            // Create new object
            return std::make_shared<RMCData>(fields[2] == "A", latitude,
                                             longitude);
        }

        void NMEA::parse()
        {
            if (_is_parsed)
                return;

            if (_last_data.empty())
            {
                _is_parsed = false;
                return;
            }

            _data.ggl = _parse_ggl();
            _data.rmc = _parse_rmc();
            _is_parsed = true;
        }

        bool NMEA::is_valid_data() const
        {
            return _is_parsed && _data.is_valid();
        }

        std::shared_ptr<GGLData> NMEA::get_ggl() const
        {
            if (!_is_parsed)
                return nullptr;
            return _data.ggl;
        }

        std::shared_ptr<RMCData> NMEA::get_rmc() const
        {
            if (!_is_parsed)
                return nullptr;
            return _data.rmc;
        }

        Coordinates NMEA::get_latitude() const
        {
            if (_data.rmc != nullptr && _data.rmc->is_valid())
                return _data.rmc->get_latitude();
            if (_data.ggl != nullptr && _data.ggl->is_valid())
                return _data.ggl->get_latitude();
            return Coordinates(0, 0.0f);
        }

        Coordinates NMEA::get_longitude() const
        {
            if (_data.rmc != nullptr && _data.rmc->is_valid())
                return _data.rmc->get_longitude();
            if (_data.ggl != nullptr && _data.ggl->is_valid())
                return _data.ggl->get_longitude();
            return Coordinates(0, 0.0f);
        }
    } // namespace parsers
} // namespace sabre