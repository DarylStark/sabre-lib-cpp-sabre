#include "sabre/parsers/gps.hpp"
#include <gtest/gtest.h>

using namespace sabre::new_parsers;

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

TEST(ParsersNMEA, ParseGLLScentence)
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

TEST(ParsersNMEA, AddMultipleScentences)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                         "100.0,M,-34.0,M,,*7C");
    parser.add_scentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,A,A*2A");
    parser.add_scentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                         "100.0,M,-34.0,M,,*7C");
    ASSERT_NEAR(parser.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(ParsersNMEA, VoidRMC)
{
    NMEA_Parser parser;
    parser.add_scentence(
        "$GNRMC,120000.000,V,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A");
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, InvalidRMC)
{
    NMEA_Parser parser;
    parser.add_scentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125");
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, VoidGLL)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,V,A*2A");
    parser.parse();
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, InvalidGLL)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,A");
    parser.parse();
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, VoidGGA)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,0,08,0.9,"
                         "100.0,M,-34.0,M,,*7C");
    parser.parse();
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}

TEST(ParsersNMEA, InvalidGGA)
{
    NMEA_Parser parser;
    parser.add_scentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1"
                         "100.0,M,-34.0,M,,*7C");
    parser.parse();
    ASSERT_EQ(parser.get_last_position().get_latitude().get_dd(), 0);
    ASSERT_EQ(parser.get_last_position().get_longitude().get_dd(), 0);
}