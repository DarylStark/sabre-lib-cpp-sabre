#include "sabre/parsers/gps.hpp"
#include <gtest/gtest.h>

TEST(ParsersGPS, IsValidData)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    ASSERT_FALSE(nmea_parser.is_valid_data());
    nmea_parser.parse();
    ASSERT_TRUE(nmea_parser.is_valid_data());
}

TEST(ParsersGPS, CorrectGGLLocationNW)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().to_decimal(), 40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().to_decimal(), -74.01003, 1e-5);
}

TEST(ParsersGPS, CorrectGGLLocationSE)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,S,07400.602,E,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,S,07400.602,E,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().to_decimal(), -40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().to_decimal(), 74.01003, 1e-5);
}

TEST(ParsersGPS, InvalidGGLLocation)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,E,123456.00,V,A*6B\n$GNRMC,123456.00,V,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, EmptyGGLLocation)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data("$GNGLL,,,,,192612.000,V,M*68\n$GNRMC,192612.000,V,,,,"
                         ",,,121025,,,M,V*20");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, MissingGGLLocation)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data("$GNRMC,192612.000,V,,,,,,,121025,,,M,V*20");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, CorrectRMCLocationNW)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().to_decimal(), 40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().to_decimal(), -74.01003, 1e-5);
}

TEST(ParsersGPS, CorrectRMCLocationSE)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,S,07400.602,E,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,S,07400.602,E,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().to_decimal(), -40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().to_decimal(), 74.01003, 1e-5);
}

TEST(ParsersGPS, InvalidRMCLocation)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,E,123456.00,V,A*6B\n$GNRMC,123456.00,V,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, EmptyRMCLocation)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data("$GNGLL,,,,,192612.000,V,M*68\n$GNRMC,192612.000,V,,,,"
                         ",,,121025,,,M,V*20");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, MissingGRMCocation)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data("$GNGLL,,,,,192612.000,V,M*68");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, ValidLocationViaRMC)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "5222.212,N,00453.712,E,0.0,0.0,121025,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();
    ASSERT_NEAR(nmea_parser.get_latitude().to_decimal(), 52.37019, 1e-5);
    ASSERT_NEAR(nmea_parser.get_longitude().to_decimal(), 4.8952, 1e-5);
}

TEST(ParsersGPS, ValidLocationViaGGL)
{
    using sabre::parsers::NMEA;

    NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,V,"
        "5222.212,N,00453.712,E,0.0,0.0,121025,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();
    ASSERT_NEAR(nmea_parser.get_latitude().to_decimal(), 40.71005, 1e-5);
    ASSERT_NEAR(nmea_parser.get_longitude().to_decimal(), -74.01003, 1e-5);
}