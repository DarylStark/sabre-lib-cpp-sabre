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
    ASSERT_NEAR(c.get_seconds(), 30.24, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_South)
{
    Coordinate c(48, 51, 30.24, CoordinatesDirection::SOUTH);
    ASSERT_NEAR(c.get_dd(), -48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::SOUTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 51);
    ASSERT_NEAR(c.get_seconds(), 30.24, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_East)
{
    Coordinate c(2, 17, 40.2, CoordinatesDirection::EAST);
    ASSERT_NEAR(c.get_dd(), 2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::EAST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 17);
    ASSERT_NEAR(c.get_seconds(), 40.2, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMS_West)
{
    Coordinate c(2, 17, 40.2, CoordinatesDirection::WEST);
    ASSERT_NEAR(c.get_dd(), -2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::WEST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 17);
    ASSERT_NEAR(c.get_seconds(), 40.2, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_North)
{
    Coordinate c(40, 42.603, CoordinatesDirection::NORTH);
    ASSERT_NEAR(c.get_dd(), 40.71005, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::NORTH);
    ASSERT_EQ(c.get_degrees(), 40);
    ASSERT_EQ(c.get_minutes(), 42);
    ASSERT_NEAR(c.get_seconds(), 36.17523, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_South)
{
    Coordinate c(40, 42.603, CoordinatesDirection::SOUTH);
    ASSERT_NEAR(c.get_dd(), -40.71005, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::SOUTH);
    ASSERT_EQ(c.get_degrees(), 40);
    ASSERT_EQ(c.get_minutes(), 42);
    ASSERT_NEAR(c.get_seconds(), 36.17523, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_East)
{
    Coordinate c(74, 0.602, CoordinatesDirection::EAST);
    ASSERT_NEAR(c.get_dd(), 74.01003, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::EAST);
    ASSERT_EQ(c.get_degrees(), 74);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_NEAR(c.get_seconds(), 36.11755, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingDMSNoSec_West)
{
    Coordinate c(74, 0.602, CoordinatesDirection::WEST);
    ASSERT_NEAR(c.get_dd(), -74.01003, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::WEST);
    ASSERT_EQ(c.get_degrees(), 74);
    ASSERT_EQ(c.get_minutes(), 0);
    ASSERT_NEAR(c.get_seconds(), 36.11755, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_North)
{
    Coordinate c(48.8584, CoordinateType::LATITUDE);
    ASSERT_NEAR(c.get_dd(), 48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::NORTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 51);
    ASSERT_NEAR(c.get_seconds(), 30.24, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_South)
{
    Coordinate c(-48.8584, CoordinateType::LATITUDE);
    ASSERT_NEAR(c.get_dd(), -48.8584, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LATITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::SOUTH);
    ASSERT_EQ(c.get_degrees(), 48);
    ASSERT_EQ(c.get_minutes(), 51);
    ASSERT_NEAR(c.get_seconds(), 0, 30.24);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_East)
{
    Coordinate c(2.2945, CoordinateType::LONGITUDE);
    ASSERT_NEAR(c.get_dd(), 2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::EAST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 17);
    ASSERT_NEAR(c.get_seconds(), 40.2, 0.01);
}

TEST(ModelsLocation, CoordinateConstructUsingFloat_West)
{
    Coordinate c(-2.2945, CoordinateType::LONGITUDE);
    ASSERT_NEAR(c.get_dd(), -2.2945, 1e-5);
    ASSERT_EQ(c.get_type(), CoordinateType::LONGITUDE);
    ASSERT_EQ(c.get_direction(), CoordinatesDirection::WEST);
    ASSERT_EQ(c.get_degrees(), 2);
    ASSERT_EQ(c.get_minutes(), 17);
    ASSERT_NEAR(c.get_seconds(), 40.2, 0.01);
}

TEST(ModelsLocation, DistanceConstructWithoutValue)
{
    Distance d;
    ASSERT_EQ(d.millimeters(), 0);
}

TEST(ModelsLocation, DistanceConstructWithValue)
{
    Distance d(1000);
    ASSERT_EQ(d.millimeters(), 1000);
}

TEST(ModelsLocation, DistanceConvertToCentimeterLowValue)
{
    Distance d(5);
    ASSERT_EQ(d.centimeters(), 0.5);
}

TEST(ModelsLocation, DistanceConvertToCentimeterHighValue)
{
    Distance d(265);
    ASSERT_EQ(d.centimeters(), 26.5);
}

TEST(ModelsLocation, DistanceConvertToMeterLowValue)
{
    Distance d(265);
    ASSERT_NEAR(d.meters(), 0.265, 1e-06);
}

TEST(ModelsLocation, DistanceConvertToMeterHighValue)
{
    Distance d(5633);
    ASSERT_NEAR(d.meters(), 5.633, 1e-6);
}

TEST(ModelsLocation, DistanceConvertToKilometerLowValue)
{
    Distance d(5633);
    ASSERT_NEAR(d.kilometers(), 0.005633, 1e-9);
}

TEST(ModelsLocation, DistanceConvertToKilometerHighValue)
{
    Distance d(5833145690);
    ASSERT_NEAR(d.kilometers(), 5833.14569, 0.001);
}

TEST(ModelsLocation, PositionConstructWithoutLocation)
{
    Position pos;
    ASSERT_EQ(pos.get_latitude().get_dd(), 0);
    ASSERT_EQ(pos.get_longitude().get_dd(), 0);
}

TEST(ModelsLocation, PositionConstructWithLocation)
{
    Position pos({48, 51, 30.24, CoordinatesDirection::NORTH},
                 {2, 17, 40.2, CoordinatesDirection::EAST});
    ASSERT_NEAR(pos.get_latitude().get_dd(), 48.8584, 1e-5);
    ASSERT_NEAR(pos.get_longitude().get_dd(), 2.2945, 1e-5);
}

TEST(ModelsLocation, PositionDistanceParisNewYork)
{
    Position eiffel_tower({48, 51, 30.24, CoordinatesDirection::NORTH},
                          {2, 17, 40.2, CoordinatesDirection::EAST});
    Position statue_of_liberty({40, 42, 51.0, CoordinatesDirection::NORTH},
                               {74, 0, 21.0, CoordinatesDirection::WEST});
    Distance distance = eiffel_tower.get_distance(statue_of_liberty);
    ASSERT_EQ(distance, 5833145381);
}

TEST(ModelsLocation, PositionDistanceZero)
{
    Position point1({10, 0, 0.0, CoordinatesDirection::NORTH},
                    {20, 0, 0.0, CoordinatesDirection::EAST});
    Position point2({10, 0, 0.0, CoordinatesDirection::NORTH},
                    {20, 0, 0.0, CoordinatesDirection::EAST});
    Distance distance = point1.get_distance(point2);
    ASSERT_EQ(distance, 0);
}

TEST(ModelsLocation, PositionDistanceSabreDunderMifflin)
{
    Position sabre_office({34.1554188, CoordinateType::LATITUDE},
                          {-118.8188163, CoordinateType::LONGITUDE});
    Position dm_office({34.21092250221861, CoordinateType::LATITUDE},
                       {-118.4363868768214, CoordinateType::LONGITUDE});
    Distance distance = sabre_office.get_distance(dm_office);
    ASSERT_NEAR(distance.kilometers(), 35.71523, 0.00001);
}

TEST(ModelsLocation, CoordinateEqualOperator_EqualCoordinates)
{
    Coordinate x(34.1554188, CoordinateType::LATITUDE);
    Coordinate y(34.1554188, CoordinateType::LATITUDE);
    ASSERT_TRUE(x == y);
}

TEST(ModelsLocation, CoordinateEqualOperator_InequalCoordinates)
{
    Coordinate x(34.1554188, CoordinateType::LATITUDE);
    Coordinate y(35.1554188, CoordinateType::LATITUDE);
    ASSERT_FALSE(x == y);
}

TEST(ModelsLocation, CoordinateEqualOperator_InequalTypes)
{
    Coordinate x(34.1554188, CoordinateType::LATITUDE);
    Coordinate y(34.1554188, CoordinateType::LONGITUDE);
    ASSERT_FALSE(x == y);
}

TEST(ModelsLocation, CoordinateEqualOperator_InequalTypesAndCoordinate)
{
    Coordinate x(34.1554188, CoordinateType::LATITUDE);
    Coordinate y(35.1554188, CoordinateType::LONGITUDE);
    ASSERT_FALSE(x == y);
}

TEST(ModelsLocation, PositionEqualOperator_EqualPositions)
{
    Position x({34.1554188, CoordinateType::LATITUDE},
               {35.1554188, CoordinateType::LONGITUDE});
    Position y({34.1554188, CoordinateType::LATITUDE},
               {35.1554188, CoordinateType::LONGITUDE});
    ASSERT_TRUE(x == y);
}

TEST(ModelsLocation, PositionEqualOperator_InequalCoordinates)
{
    Position x({34.1554188, CoordinateType::LATITUDE},
               {35.1554188, CoordinateType::LONGITUDE});
    Position y({34.1554188, CoordinateType::LATITUDE},
               {36.1554188, CoordinateType::LONGITUDE});
    ASSERT_FALSE(x == y);
}
