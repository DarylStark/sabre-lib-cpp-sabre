#include "geo.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

namespace sabre::models::geo
{
    Coordinate::Coordinate() noexcept
        : _coordinate(0), _type(CoordinateType::LATITUDE)
    {
    }

    Coordinate::Coordinate(uint16_t degrees, uint16_t minutes, double seconds,
                           CoordinatesDirection direction) noexcept
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
                           CoordinatesDirection direction) noexcept
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

    Coordinate::Coordinate(double coordinate, CoordinateType type) noexcept
        : _coordinate(coordinate), _type(type)
    {
    }

    bool Coordinate::operator==(const Coordinate &other) const noexcept
    {
        return other._coordinate == _coordinate && other._type == _type;
    }

    double Coordinate::getDD() const noexcept
    {
        return _coordinate;
    }

    CoordinateType Coordinate::getType() const noexcept
    {
        return _type;
    }

    CoordinatesDirection Coordinate::getDirection() const noexcept
    {

        if (_type == CoordinateType::LONGITUDE)
            return _coordinate >= 0 ? CoordinatesDirection::EAST
                                    : CoordinatesDirection::WEST;
        return _coordinate >= 0 ? CoordinatesDirection::NORTH
                                : CoordinatesDirection::SOUTH;
    }

    uint16_t Coordinate::getDegrees() const noexcept
    {
        return static_cast<uint16_t>(std::floor(std::abs(_coordinate)));
    }

    uint16_t Coordinate::getMinutes() const noexcept
    {
        double abs_coord = std::abs(_coordinate);
        double fractional = abs_coord - std::floor(abs_coord);
        return static_cast<uint16_t>(std::floor(fractional * 60.0));
    }

    double Coordinate::getSeconds() const noexcept
    {
        double abs_coord = std::abs(_coordinate);
        double fractional = abs_coord - std::floor(abs_coord);
        double minutes = fractional * 60.0;
        double min_fractional = minutes - std::floor(minutes);
        // Round to nearest millisecond for higher precision
        return std::round(min_fractional * 60.0 * 1000.0) / 1000.0;
    }

    Position::Position() noexcept : _latitude(), _longitude(), _version(0) {}

    Position::Position(Coordinate latitude, Coordinate longitude) noexcept
        : _latitude(latitude), _longitude(longitude), _version(0)
    {
    }

    bool Position::operator==(const Position &other) const noexcept
    {
        return other._latitude == _latitude && other._longitude == _longitude;
    }

    Coordinate Position::getLatitude() const noexcept
    {
        return _latitude;
    }

    Coordinate Position::getLongitude() const noexcept
    {
        return _longitude;
    }

    Distance::Distance() noexcept : _distanceInMm(0) {}

    Distance::Distance(uint64_t distanceInMM) noexcept
        : _distanceInMm(distanceInMM)
    {
    }

    uint64_t Distance::millimeters() const noexcept
    {
        return _distanceInMm;
    }

    float Distance::centimeters() const noexcept
    {
        return static_cast<float>(_distanceInMm) / 10.0f;
    }

    float Distance::meters() const noexcept
    {
        return static_cast<float>(_distanceInMm) / 1000.0f;
    }

    float Distance::kilometers() const noexcept
    {
        return static_cast<float>(_distanceInMm) / 1'000'000.0f;
    }

    Distance::operator uint64_t() const noexcept
    {
        return _distanceInMm;
    }

    Distance Position::getDistance(const Position &other) const noexcept
    {
        const double R = 6371000; // Radius of the Earth in meters
        double lat1_rad = _latitude.getDD() * M_PI / 180.0;
        double lat2_rad = other._latitude.getDD() * M_PI / 180.0;
        double delta_lat =
            (other._latitude.getDD() - _latitude.getDD()) * M_PI / 180.0;
        double delta_lon =
            (other._longitude.getDD() - _longitude.getDD()) * M_PI / 180.0;

        double a = std::sin(delta_lat / 2) * std::sin(delta_lat / 2) +
                   std::cos(lat1_rad) * std::cos(lat2_rad) *
                       std::sin(delta_lon / 2) * std::sin(delta_lon / 2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

        return Distance(static_cast<uint64_t>(R * c * 100.0 * 10.0));
    }

    bool Position::isValid() const noexcept
    {
        return _latitude.getDD() != 0.0 || _longitude.getDD() != 0.0;
    }

    uint32_t Position::getVersion() const noexcept
    {
        return _version;
    }

    void Position::setVersion(uint32_t version) noexcept
    {
        _version = version;
    }
} // namespace sabre::models::geo