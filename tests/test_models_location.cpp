#include <gtest/gtest.h>
#include <sabre/parsers/gps.hpp>

using namespace sabre::models;

TEST(ModelsLocation, CoordinateConstructWithoutLocation)
{
    Coordinate c;
    ASSERT_EQ(c.get_dd(), 0);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::NORTH);
    ASSERT_EQ(c.get_degrees(), 0);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_North)
{
    Coordinate c(48, 51, 30.24, CoordinatesDirection::NORTH);
    ASSERT_NEAR(c.get_dd(), 48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::NORTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 51);
    ASSERT_EQ(c.get_seconds(), 30.24);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_South)
{
    Coordinate c(48, 51, 30.24, CoordinatesDirection::SOUTH);
    ASSERT_NEAR(c.get_dd(), -48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::SOUTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 51);
    ASSERT_EQ(c.get_seconds(), 30.24);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_East)
{
    Coordinate c(2, 17, 40.2, CoordinatesDirection::EAST);
    ASSERT_NEAR(c.get_dd(), 2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::EAST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 17);
    ASSERT_EQ(c.get_seconds(), 40.2);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_West)
{
    Coordinate c(2, 17, 40.2, CoordinatesDirection::WEST);
    ASSERT_NEAR(c.get_dd(), -2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::WEST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 17);
    ASSERT_EQ(c.get_seconds(), 40.2);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_North)
{
    Coordinate c(40, 42.603, CoordinatesDirection::NORTH);
    ASSERT_NEAR(c.get_dd(), 40.71005, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::NORTH);
    ASSERT_EQ(c.get_degrees(), 40);
    ASSERT_EQ(c.get_minutes(), 42);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_South)
{
    Coordinate c(40, 42.603, CoordinatesDirection::SOUTH);
    ASSERT_NEAR(c.get_dd(), -40.71005, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::SOUTH);
    ASSERT_EQ(c.get_degrees(), 40);
    ASSERT_EQ(c.get_minutes(), 42);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_East)
{
    Coordinate c(74, 0.602, CoordinatesDirection::EAST);
    ASSERT_NEAR(c.get_dd(), 74.01003, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::EAST);
    ASSERT_EQ(c.get_degrees(), 74);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_West)
{
    Coordinate c(74, 0.602, CoordinatesDirection::WEST);
    ASSERT_NEAR(c.get_dd(), -74.01003, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::WEST);
    ASSERT_EQ(c.get_degrees(), 74);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_North)
{
    Coordinate c(48.8584, CoordinateType::LATITUDE);
    ASSERT_NEAR(c.get_dd(), 48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::NORTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_South)
{
    Coordinate c(-48.8584, CoordinateType::LATITUDE);
    ASSERT_NEAR(c.get_dd(), -48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::SOUTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_East)
{
    Coordinate c(2.2945, CoordinateType::LONGITUDE);
    ASSERT_NEAR(c.get_dd(), 2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::EAST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_West)
{
    Coordinate c(-2.2945, CoordinateType::LONGITUDE);
    ASSERT_NEAR(c.get_dd(), -2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::WEST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_EQ(c.get_seconds(), 0);
}
