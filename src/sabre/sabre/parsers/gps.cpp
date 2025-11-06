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
    } // namespace models

    namespace parsers
    {
        GGLData::GGLData(bool valid, Coordinate latitude, Coordinate longitude)
            : valid(valid), latitude(latitude), longitude(longitude)
        {
        }

        bool GGLData::is_valid() const
        {
            return valid;
        }

        Coordinate GGLData::get_latitude() const
        {
            return latitude;
        }
        Coordinate GGLData::get_longitude() const
        {
            return longitude;
        }

        RMCData::RMCData(bool valid, Coordinate latitude, Coordinate longitude)
            : valid(valid), latitude(latitude), longitude(longitude)
        {
        }

        bool RMCData::is_valid() const
        {
            return valid;
        }

        Coordinate RMCData::get_latitude() const
        {
            return latitude;
        }

        Coordinate RMCData::get_longitude() const
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
                return std::make_shared<GGLData>(false, Coordinate(),
                                                 Coordinate());

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
                return std::make_shared<GGLData>(false, Coordinate(),
                                                 Coordinate());

            // Latitude
            std::string lat_str = fields[1];
            char lat_dir = fields[2][0];
            if (lat_str.length() < 4)
                return std::make_shared<GGLData>(false, Coordinate(),
                                                 Coordinate());
            uint16_t lat_deg = std::stoi(lat_str.substr(0, 2));
            float lat_min = std::stof(lat_str.substr(2));
            Coordinate latitude =
                Coordinate(lat_deg, lat_min,
                           lat_dir == 'N' ? CoordinatesDirection::NORTH
                                          : CoordinatesDirection::SOUTH);

            // Longitude
            std::string lon_str = fields[3];
            char lon_dir = fields[4][0];
            if (lon_str.length() < 5)
                return std::make_shared<GGLData>(false, Coordinate(),
                                                 Coordinate());
            uint16_t lon_deg = std::stoi(lon_str.substr(0, 3));
            float lon_min = std::stof(lon_str.substr(3));
            Coordinate longitude =
                Coordinate(lon_deg, lon_min,
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
                return std::make_shared<RMCData>(false, Coordinate(),
                                                 Coordinate());

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
                return std::make_shared<RMCData>(false, Coordinate(),
                                                 Coordinate());

            // Latitude
            std::string lat_str = fields[3];
            char lat_dir = fields[4][0];
            if (lat_str.length() < 4)
                return std::make_shared<RMCData>(false, Coordinate(),
                                                 Coordinate());
            uint16_t lat_deg = std::stoi(lat_str.substr(0, 2));
            double lat_min = std::stod(lat_str.substr(2));
            Coordinate latitude =
                Coordinate(lat_deg, lat_min,
                           lat_dir == 'N' ? CoordinatesDirection::NORTH
                                          : CoordinatesDirection::SOUTH);

            // Longitude
            std::string lon_str = fields[5];
            char lon_dir = fields[6][0];
            if (lon_str.length() < 5)
                return std::make_shared<RMCData>(false, Coordinate(),
                                                 Coordinate());
            uint16_t lon_deg = std::stoi(lon_str.substr(0, 3));
            double lon_min = std::stod(lon_str.substr(3));
            Coordinate longitude =
                Coordinate(lon_deg, lon_min,
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

        Coordinate NMEA::get_latitude() const
        {
            if (_data.rmc != nullptr && _data.rmc->is_valid())
                return _data.rmc->get_latitude();
            if (_data.ggl != nullptr && _data.ggl->is_valid())
                return _data.ggl->get_latitude();
            return Coordinate();
        }

        Coordinate NMEA::get_longitude() const
        {
            if (_data.rmc != nullptr && _data.rmc->is_valid())
                return _data.rmc->get_longitude();
            if (_data.ggl != nullptr && _data.ggl->is_valid())
                return _data.ggl->get_longitude();
            return Coordinate();
        }
    } // namespace parsers
} // namespace sabre