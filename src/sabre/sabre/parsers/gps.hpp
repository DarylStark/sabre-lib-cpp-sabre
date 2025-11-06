#ifndef GPS_HPP
#define GPS_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

/*
Fields:

First byte   = $ = Start of scentece
Byte 2 and 3 = talker_id = who is giving you the data
- GP = GPS
- BD = BeiDou (Chinese)
- GN = Generic
- GL = Glonass (Russian)
- GA = Galileo (European)
Byte 4 and 5 = scentence = What data is it
- GLL = Geographic Position = Latitude / Longitude
- GSA = NGSS DOP and Active Satellites
- GSV = GNSS Satellites in View
- RMC = Recommended Minimum Specific GNSS Data
- VTG = Course over Ground and Ground Speed
- ZDA = Date and Time
- TXT = Text Transmission

$GNGGA,174506.000,,,,,0,00,25.5,,,,,,*7B
$GNGLL,,,,,174506.000,V,M*66
$GNGSA,A,1,,,,,,,,,,,,,25.5,25.5,25.5,1*01
$GNGSA,A,1,,,,,,,,,,,,,25.5,25.5,25.5,4*04
$GPGSV,1,1,02,25,64,265,24,29,19,196,31,0*6A
$BDGSV,1,1,00,0*74
$GNRMC,174506.000,V,,,,,,,121025,,,M,V*2E
$GNVTG,,,,,,,,,M*2D
$GNZDA,174506.000,12,10,2025,00,00*4E
$GPTXT,01,01,01,ANTENNA OK*35
*/

namespace sabre
{
    namespace models
    {
        enum class CoordinatesDirection
        {
            NORTH,
            SOUTH,
            EAST,
            WEST
        };

        enum class CoordinateType
        {
            LATITUDE,
            LONGITUDE
        };

        class Coordinate
        {
        private:
            double _coordinate;
            CoordinateType _type;

        public:
            Coordinate();
            Coordinate(uint16_t degrees, uint16_t minutes, double seconds,
                       CoordinatesDirection direction);
            Coordinate(uint16_t degrees, float minutes,
                       CoordinatesDirection direction);
            Coordinate(double coordinate, CoordinateType type);

            double get_dd() const;
            CoordinateType get_type() const;
            CoordinatesDirection get_direction() const;
            uint16_t get_degrees() const;
            uint16_t get_minutes() const;
            double get_seconds() const;
        };

        class Distance
        {
        private:
            uint64_t _distance_in_mm;

        public:
            Distance();
            Distance(uint64_t distance_in_mm);

            uint64_t millimeters() const;
            float centimeters() const;
            float meters() const;
            float kilometers() const;

            operator uint64_t() const;
        };

        class Position
        {
        private:
            Coordinate _latitude;
            Coordinate _longitude;

        public:
            Position();
            Position(Coordinate latitude, Coordinate longitude);
            Coordinate get_latitude() const;
            Coordinate get_longitude() const;

            Distance get_distance(const Position &other) const;
        };
    } // namespace models

    namespace parsers
    {
        using namespace sabre::models;

        class NMEA_Parser
        {
        private:
            Position _last_position;
            std::map<std::string, std::string> _scentences;

            std::string _get_type(std::string scentence) const;
            std::string _get_talker(std::string scentence) const;

            bool _parse_rmc(std::string scentence);
            bool _parse_gll(std::string scentence);
            bool _parse_gga(std::string scentence);

            std::vector<std::string> _get_fields(std::string scentence) const;

        public:
            NMEA_Parser();
            void add_scentence(const std::string &scentence);
            void parse();

            Position get_last_position();

            size_t get_scentence_count() const;
        };
    } // namespace parsers
} // namespace sabre
#endif