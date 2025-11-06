#include "sabre/parsers/gps.hpp"
#include <gtest/gtest.h>

using namespace sabre::new_parsers;

TEST(ParsersGPS, IsValidData)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
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
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().get_dd(), 40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().get_dd(), -74.01003, 1e-5);
}

TEST(ParsersGPS, CorrectGGLLocationSE)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,S,07400.602,E,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,S,07400.602,E,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().get_dd(), -40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().get_dd(), 74.01003, 1e-5);
}

TEST(ParsersGPS, InvalidGGLLocation)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
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
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data("$GNGLL,,,,,192612.000,V,M*68\n$GNRMC,192612.000,V,,,,"
                         ",,,121025,,,M,V*20");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, MissingGGLLocation)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data("$GNRMC,192612.000,V,,,,,,,121025,,,M,V*20");
    nmea_parser.parse();

    const auto data = nmea_parser.get_ggl();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, CorrectRMCLocationNW)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().get_dd(), 40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().get_dd(), -74.01003, 1e-5);
}

TEST(ParsersGPS, CorrectRMCLocationSE)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,S,07400.602,E,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "4042.603,S,07400.602,E,0.0,0.0,240925,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), true);
    ASSERT_NEAR(data->get_latitude().get_dd(), -40.71005, 1e-5);
    ASSERT_NEAR(data->get_longitude().get_dd(), 74.01003, 1e-5);
}

TEST(ParsersGPS, InvalidRMCLocation)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
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
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data("$GNGLL,,,,,192612.000,V,M*68\n$GNRMC,192612.000,V,,,,"
                         ",,,121025,,,M,V*20");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, MissingGRMCocation)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data("$GNGLL,,,,,192612.000,V,M*68");
    nmea_parser.parse();

    const auto data = nmea_parser.get_rmc();

    ASSERT_NE(data, nullptr);
    ASSERT_EQ(data->is_valid(), false);
}

TEST(ParsersGPS, ValidLocationViaRMC)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,A,"
        "5222.212,N,00453.712,E,0.0,0.0,121025,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();
    ASSERT_NEAR(nmea_parser.get_latitude().get_dd(), 52.37019, 0.05);
    ASSERT_NEAR(nmea_parser.get_longitude().get_dd(), 4.8952, 0.05);
}

TEST(ParsersGPS, ValidLocationViaGGL)
{
    using sabre::parsers::Old_NMEA;

    Old_NMEA nmea_parser;
    nmea_parser.set_data(
        "$GNGLL,4042.603,N,07400.602,W,123456.00,A,A*6B\n$GNRMC,123456.00,V,"
        "5222.212,N,00453.712,E,0.0,0.0,121025,,,A*7B\n$GNGGA,123456.00,4042."
        "603,N,07400.602,W,1,08,1.0,10.0,M,0.0,M,,*6E");
    nmea_parser.parse();
    ASSERT_NEAR(nmea_parser.get_latitude().get_dd(), 40.71005, 1e-5);
    ASSERT_NEAR(nmea_parser.get_longitude().get_dd(), -74.01003, 1e-5);
}

// -----------------------------------------------------------------------------

TEST(ParsersNMEA, ConstructEmpty)
{
    NMEA_Parser parser;
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, ConstructParseEmpty)
{
    NMEA_Parser parser;
    parser.parse();
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, AddScentence)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNTXT,4042.603,N,07400.602,W,123456.00,A,A*6B");
    ASSERT_EQ(parser.get_scentence_count(), 1);
}

TEST(ParsersNMEA, AddTwoScentences)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNTXT,4042.603,N,07400.602,W,123456.00,A,A*6B");
    parser.add_scentence(
        "$GNZDA,123456.00,A,4042.603,N,07400.602,W,0.0,0.0,240925,,,A*7B");
    ASSERT_EQ(parser.get_scentence_count(), 2);
}

TEST(ParsersNMEA, AddTwoScentencesFromSameSource)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNZDA,4042.603,N,07400.602,W,123456.00,A,A*6B");
    parser.add_scentence("$GNZDA,4042.603,N,07400.602,W,123456.00,A,A*6B");
    ASSERT_EQ(parser.get_scentence_count(), 1);
}

TEST(ParsersNMEA, AddOneScentenceFromRMC)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNRMC,112832.000,A,5157.15453,N,00515.01568,E,6.43,"
                         "122.59,031125,,,A,V*02");
    ASSERT_EQ(parser.get_scentence_count(), 0);
}

TEST(ParsersNMEA, AddOneScentenceFromGLL)
{
    NMEA_Parser parser;
    parser.add_scentence(
        "$GPRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A");
    ASSERT_EQ(parser.get_scentence_count(), 0);
}

TEST(ParsersNMEA, ParseRMCScentence)
{
    NMEA_Parser parser;
    parser.add_scentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A");
    ASSERT_NEAR(parser.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(ParsersNMEA, ParseGGLScentence)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,A,A*2A");
    parser.parse();
    ASSERT_NEAR(parser.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(ParsersNMEA, ParseGGAScentence)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                         "100.0,M,-34.0,M,,*7C");
    parser.parse();
    ASSERT_NEAR(parser.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}