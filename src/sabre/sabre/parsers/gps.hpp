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

namespace sabre::parsers
{
    enum class CoordinatesDirection
    {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    class Coordinates
    {
        uint16_t _degrees;
        double _minutes;
        CoordinatesDirection _direction;

    public:
        Coordinates(
            uint16_t degrees, double minutes,
            CoordinatesDirection direction = CoordinatesDirection::NORTH);
        double to_decimal() const;
    };

    class GGLData
    {
    private:
        bool valid;
        Coordinates latitude;
        Coordinates longitude;

    public:
        GGLData(bool valid, Coordinates latitude, Coordinates longitude);

        bool is_valid() const;
        Coordinates get_latitude() const;
        Coordinates get_longitude() const;
    };

    class RMCData
    {
    private:
        bool valid;
        Coordinates latitude;
        Coordinates longitude;

    public:
        RMCData(bool valid, Coordinates latitude, Coordinates longitude);

        bool is_valid() const;
        Coordinates get_latitude() const;
        Coordinates get_longitude() const;
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

        Coordinates get_latitude() const;
        Coordinates get_longitude() const;
    };
} // namespace sabre::parsers

#endif