#ifndef GPS_HPP
#define GPS_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

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

            // Helper to extract coordinates from fields
            bool _extract_position_from_fields(
                const std::vector<std::string> &fields, size_t lat_idx,
                size_t lat_dir_idx, size_t lon_idx, size_t lon_dir_idx,
                Position &out_position) const;

        public:
            NMEA_Parser();
            void add_scentence(const std::string &scentence);
            void parse();

            Position get_last_position() const;

            size_t get_scentence_count() const;
        };
    } // namespace parsers
} // namespace sabre
#endif