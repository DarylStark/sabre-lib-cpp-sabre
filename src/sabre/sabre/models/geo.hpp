#pragma once

#include <cstdint>

namespace sabre::models::geo
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
        Coordinate() noexcept;

        /**
         * @brief Construct from degrees, minutes, seconds, and direction.
         * @param degrees Degrees part.
         * @param minutes Minutes part.
         * @param seconds Seconds part.
         * @param direction Cardinal direction.
         */
        Coordinate(uint16_t degrees, uint16_t minutes, double seconds,
                   CoordinatesDirection direction) noexcept;

        /**
         * @brief Construct from degrees, minutes, and direction.
         * @param degrees Degrees part.
         * @param minutes Minutes part (fractional).
         * @param direction Cardinal direction.
         */
        Coordinate(uint16_t degrees, float minutes,
                   CoordinatesDirection direction) noexcept;

        /**
         * @brief Construct from decimal degrees and type.
         * @param coordinate Decimal degrees value.
         * @param type Coordinate type.
         */
        Coordinate(double coordinate, CoordinateType type) noexcept;

        bool operator==(const Coordinate &other) const noexcept;

        /**
         * @brief Get decimal degrees value.
         * @return Decimal degrees.
         */
        double getDD() const noexcept;

        /**
         * @brief Get coordinate type.
         * @return CoordinateType.
         */
        CoordinateType getType() const noexcept;

        /**
         * @brief Get cardinal direction.
         * @return CoordinatesDirection.
         */
        CoordinatesDirection getDirection() const noexcept;

        /**
         * @brief Get degrees part.
         * @return Degrees as integer.
         */
        uint16_t getDegrees() const noexcept;

        /**
         * @brief Get minutes part.
         * @return Minutes as integer.
         */
        uint16_t getMinutes() const noexcept;

        /**
         * @brief Get seconds part.
         * @return Seconds as double.
         */
        double getSeconds() const noexcept;
    };

    /**
     * @brief Represents a distance in millimeters, centimeters, meters, or
     * kilometers.
     */
    class Distance
    {
    private:
        uint64_t _distanceInMm; /**< Distance in millimeters. */

    public:
        /**
         * @brief Default constructor. Initializes to 0 mm.
         */
        Distance() noexcept;

        /**
         * @brief Construct from millimeters.
         * @param distanceInMm Distance in millimeters.
         */
        Distance(uint64_t distanceInMm) noexcept;

        /**
         * @brief Get distance in millimeters.
         * @return Millimeters.
         */
        uint64_t millimeters() const noexcept;

        /**
         * @brief Get distance in centimeters.
         * @return Centimeters.
         */
        float centimeters() const noexcept;

        /**
         * @brief Get distance in meters.
         * @return Meters.
         */
        float meters() const noexcept;

        /**
         * @brief Get distance in kilometers.
         * @return Kilometers.
         */
        float kilometers() const noexcept;

        /**
         * @brief Cast to uint64_t (millimeters).
         */
        operator uint64_t() const noexcept;
    };

    /**
     * @brief Represents a geographic position (latitude and longitude).
     */
    class Position
    {
    private:
        Coordinate _latitude;  /**< Latitude coordinate. */
        Coordinate _longitude; /**< Longitude coordinate. */
        uint32_t _version;

    public:
        /**
         * @brief Default constructor. Initializes to (0,0).
         */
        Position() noexcept;

        /**
         * @brief Construct from latitude and longitude.
         * @param latitude Latitude coordinate.
         * @param longitude Longitude coordinate.
         */
        Position(Coordinate latitude, Coordinate longitude) noexcept;

        bool operator==(const Position &other) const noexcept;

        /**
         * @brief Get latitude coordinate.
         * @return Latitude.
         */
        Coordinate getLatitude() const noexcept;

        /**
         * @brief Get longitude coordinate.
         * @return Longitude.
         */
        Coordinate getLongitude() const noexcept;

        /**
         * @brief Calculate distance to another position.
         * @param other The other position.
         * @return Distance between positions.
         */
        Distance getDistance(const Position &other) const noexcept;

        bool isValid() const noexcept;

        uint32_t getVersion() const noexcept;
        void setVersion(uint32_t version) noexcept;
    };
} // namespace sabre::models::geo