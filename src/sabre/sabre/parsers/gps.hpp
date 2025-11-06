#ifndef GPS_HPP
#define GPS_HPP

#include <memory>
#include <string>

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
        using sabre::models::Coordinate;
        using sabre::models::CoordinatesDirection;

        class GGLData
        {
        private:
            bool valid;
            Coordinate latitude;
            Coordinate longitude;

        public:
            GGLData(bool valid, Coordinate latitude, Coordinate longitude);

            bool is_valid() const;
            Coordinate get_latitude() const;
            Coordinate get_longitude() const;
        };

        class RMCData
        {
        private:
            bool valid;
            Coordinate latitude;
            Coordinate longitude;

        public:
            RMCData(bool valid, Coordinate latitude, Coordinate longitude);

            bool is_valid() const;
            Coordinate get_latitude() const;
            Coordinate get_longitude() const;
        };

        class GPSData
        {
        public:
            std::shared_ptr<GGLData> ggl;
            std::shared_ptr<RMCData> rmc;

            GPSData();
            bool is_valid() const;
        };

        class NMEA
        {
        private:
            std::string _last_data;
            bool _is_parsed;
            GPSData _data;

            std::shared_ptr<GGLData> _parse_ggl();
            std::shared_ptr<RMCData> _parse_rmc();

        public:
            NMEA();
            void set_data(const std::string data);
            bool is_valid_data() const;
            void parse();

            std::shared_ptr<GGLData> get_ggl() const;
            std::shared_ptr<RMCData> get_rmc() const;

            Coordinate get_latitude() const;
            Coordinate get_longitude() const;
        };
    } // namespace parsers
} // namespace sabre
#endif