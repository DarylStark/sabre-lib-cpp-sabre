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

        /**
         * @brief Cardinal directions for coordinates.
         */
        enum class CoordinatesDirection
        {
            NORTH, /**< North direction */
            SOUTH, /**< South direction */
            EAST,  /**< East direction */
            WEST   /**< West direction */
        };

        /**
         * @brief Type of coordinate (latitude or longitude).
         */
        enum class CoordinateType
        {
            LATITUDE, /**< Latitude coordinate */
            LONGITUDE /**< Longitude coordinate */
        };

        /**
         * @brief Represents a geographic coordinate (latitude or longitude).
         */
        class Coordinate
        {
        private:
            double _coordinate;   /**< Decimal degrees value. */
            CoordinateType _type; /**< Type of coordinate. */

        public:
            /**
             * @brief Default constructor. Initializes to 0 latitude.
             */
            Coordinate();

            /**
             * @brief Construct from degrees, minutes, seconds, and direction.
             * @param degrees Degrees part.
             * @param minutes Minutes part.
             * @param seconds Seconds part.
             * @param direction Cardinal direction.
             */
            Coordinate(uint16_t degrees, uint16_t minutes, double seconds,
                       CoordinatesDirection direction);

            /**
             * @brief Construct from degrees, minutes, and direction.
             * @param degrees Degrees part.
             * @param minutes Minutes part (fractional).
             * @param direction Cardinal direction.
             */
            Coordinate(uint16_t degrees, float minutes,
                       CoordinatesDirection direction);

            /**
             * @brief Construct from decimal degrees and type.
             * @param coordinate Decimal degrees value.
             * @param type Coordinate type.
             */
            Coordinate(double coordinate, CoordinateType type);

            /**
             * @brief Get decimal degrees value.
             * @return Decimal degrees.
             */
            double get_dd() const;

            /**
             * @brief Get coordinate type.
             * @return CoordinateType.
             */
            CoordinateType get_type() const;

            /**
             * @brief Get cardinal direction.
             * @return CoordinatesDirection.
             */
            CoordinatesDirection get_direction() const;

            /**
             * @brief Get degrees part.
             * @return Degrees as integer.
             */
            uint16_t get_degrees() const;

            /**
             * @brief Get minutes part.
             * @return Minutes as integer.
             */
            uint16_t get_minutes() const;

            /**
             * @brief Get seconds part.
             * @return Seconds as double.
             */
            double get_seconds() const;
        };

        /**
         * @brief Represents a distance in millimeters, centimeters, meters, or
         * kilometers.
         */
        class Distance
        {
        private:
            uint64_t _distance_in_mm; /**< Distance in millimeters. */

        public:
            /**
             * @brief Default constructor. Initializes to 0 mm.
             */
            Distance();

            /**
             * @brief Construct from millimeters.
             * @param distance_in_mm Distance in millimeters.
             */
            Distance(uint64_t distance_in_mm);

            /**
             * @brief Get distance in millimeters.
             * @return Millimeters.
             */
            uint64_t millimeters() const;

            /**
             * @brief Get distance in centimeters.
             * @return Centimeters.
             */
            float centimeters() const;

            /**
             * @brief Get distance in meters.
             * @return Meters.
             */
            float meters() const;

            /**
             * @brief Get distance in kilometers.
             * @return Kilometers.
             */
            float kilometers() const;

            /**
             * @brief Cast to uint64_t (millimeters).
             */
            operator uint64_t() const;
        };

        /**
         * @brief Represents a geographic position (latitude and longitude).
         */
        class Position
        {
        private:
            Coordinate _latitude;  /**< Latitude coordinate. */
            Coordinate _longitude; /**< Longitude coordinate. */

        public:
            /**
             * @brief Default constructor. Initializes to (0,0).
             */
            Position();

            /**
             * @brief Construct from latitude and longitude.
             * @param latitude Latitude coordinate.
             * @param longitude Longitude coordinate.
             */
            Position(Coordinate latitude, Coordinate longitude);

            /**
             * @brief Get latitude coordinate.
             * @return Latitude.
             */
            Coordinate get_latitude() const;

            /**
             * @brief Get longitude coordinate.
             * @return Longitude.
             */
            Coordinate get_longitude() const;

            /**
             * @brief Calculate distance to another position.
             * @param other The other position.
             * @return Distance between positions.
             */
            Distance get_distance(const Position &other) const;

            bool is_valid() const;
        };
    } // namespace models

    namespace parsers
    {
        using namespace sabre::models;

        /**
         * @brief NMEA sentence parser for extracting position data.
         */
        class NMEA_Parser
        {
        private:
            Position _last_position; /**< Last parsed position. */
            std::map<std::string, std::string>
                _scentences; /**< Buffered sentences. */

            /**
             * @brief Extracts the sentence type (e.g., RMC, GGA).
             * @param scentence The NMEA sentence.
             * @return The type string.
             */
            std::string _get_type(std::string scentence) const;

            /**
             * @brief Extracts the talker ID (e.g., GP, GN).
             * @param scentence The NMEA sentence.
             * @return The talker string.
             */
            std::string _get_talker(std::string scentence) const;

            bool _is_valid_checksum(const std::string &scentence) const;

            /**
             * @brief Parse RMC sentence.
             * @param scentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_rmc(std::string scentence);

            /**
             * @brief Parse GLL sentence.
             * @param scentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_gll(std::string scentence);

            /**
             * @brief Parse GGA sentence.
             * @param scentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_gga(std::string scentence);

            /**
             * @brief Split a sentence into fields.
             * @param scentence The NMEA sentence.
             * @return Vector of fields.
             */
            std::vector<std::string> _get_fields(std::string scentence) const;

            /**
             * @brief Helper to extract coordinates from fields.
             * @param fields The split fields.
             * @param lat_idx Latitude field index.
             * @param lat_dir_idx Latitude direction field index.
             * @param lon_idx Longitude field index.
             * @param lon_dir_idx Longitude direction field index.
             * @param out_position Output position.
             * @return True if extraction was successful.
             */
            bool _extract_position_from_fields(
                const std::vector<std::string> &fields, size_t lat_idx,
                size_t lat_dir_idx, size_t lon_idx, size_t lon_dir_idx,
                Position &out_position) const;

        public:
            /**
             * @brief Default constructor.
             */
            NMEA_Parser();

            /**
             * @brief Add a sentence to the buffer.
             * @param scentence The NMEA sentence.
             */
            void add_scentence(const std::string &scentence);

            /**
             * @brief Parse buffered sentences and update last position.
             */
            void parse();

            /**
             * @brief Get the last parsed position.
             * @return Last position.
             */
            Position get_last_position() const;

            /**
             * @brief Get the number of buffered sentences.
             * @return Sentence count.
             */
            size_t get_scentence_count() const;
        };
    } // namespace parsers
} // namespace sabre
#endif