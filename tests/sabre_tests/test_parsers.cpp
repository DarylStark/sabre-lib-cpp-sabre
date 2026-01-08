#include "sabre/parsers/gps.hpp"
#include "sabre/parsers/nmea_validator.hpp"
#include <gtest/gtest.h>

using namespace sabre::parsers;

TEST(ParsersNMEA, ConstructEmpty)
{
    NmeaParser parser;
    ASSERT_EQ(parser.getLastPosition().getLatitude().getDD(), 0);
    ASSERT_EQ(parser.getLastPosition().getLongitude().getDD(), 0);
}

TEST(ParsersNMEA, ConstructParseEmpty)
{
    NmeaParser parser;
    parser.parse();
    ASSERT_EQ(parser.getLastPosition().getLatitude().getDD(), 0);
    ASSERT_EQ(parser.getLastPosition().getLongitude().getDD(), 0);
}

TEST(ParsersNMEA, AddScentence)
{
    NmeaParser parser;
    parser.addSentence("$GNTXT,4042.603,N,07400.602,W,123456.00,A,A*7D");
    ASSERT_EQ(parser.getSentenceCount(), 1);
}

TEST(ParsersNMEA, AddTwoScentences)
{
    NmeaParser parser;
    parser.addSentence("$GNTXT,4042.603,N,07400.602,W,123456.00,A,A*7D");
    parser.addSentence(
        "$GNZDA,123456.00,A,4042.603,N,07400.602,W,0.0,0.0,240925,,,A*5E");
    ASSERT_EQ(parser.getSentenceCount(), 2);
}

TEST(ParsersNMEA, AddTwoScentencesFromSameSource)
{
    NmeaParser parser;
    parser.addSentence("$GNZDA,4042.603,N,07400.602,W,123456.00,A,A*7A");
    parser.addSentence("$GNZDA,4042.603,N,07400.602,W,123456.00,A,A*7A");
    ASSERT_EQ(parser.getSentenceCount(), 1);
}

TEST(ParsersNMEA, AddOneScentenceFromRMC)
{
    NmeaParser parser;
    parser.addSentence("$GNRMC,112832.000,A,5157.15453,N,00515.01568,E,6.43,"
                       "122.59,031125,,,A,V*02");
    ASSERT_EQ(parser.getSentenceCount(), 0);
}

TEST(ParsersNMEA, AddOneScentenceFromGLL)
{
    NmeaParser parser;
    parser.addSentence(
        "$GPRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A");
    ASSERT_EQ(parser.getSentenceCount(), 0);
}

TEST(ParsersNMEA, ParseRMCScentence)
{
    NmeaParser parser;
    parser.addSentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A*64");
    ASSERT_NEAR(parser.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(ParsersNMEA, ParseGLLScentence)
{
    NmeaParser parser;
    parser.addSentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,A,A*62");
    parser.parse();
    ASSERT_NEAR(parser.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(ParsersNMEA, ParseGGAScentence)
{
    NmeaParser parser;
    parser.addSentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                       "100.0,M,-34.0,M,,*4D");
    parser.parse();
    ASSERT_NEAR(parser.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(ParsersNMEA, AddMultipleScentences)
{
    NmeaParser parser;
    parser.addSentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                       "100.0,M,-34.0,M,,*4D");
    parser.addSentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,A,A*62");
    parser.addSentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                       "100.0,M,-34.0,M,,*4D");
    ASSERT_NEAR(parser.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(parser.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(ParsersNMEA, VoidRMC)
{
    NmeaParser parser;
    parser.addSentence(
        "$GNRMC,120000.000,V,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A");
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, InvalidRMC)
{
    NmeaParser parser;
    parser.addSentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125");
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, VoidGLL)
{
    NmeaParser parser;
    parser.addSentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,V,A*2A");
    parser.parse();
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, InvalidGLL)
{
    NmeaParser parser;
    parser.addSentence("$GNGLL,3409.3251,N,11849.1290,W,120000.00,A");
    parser.parse();
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, VoidGGA)
{
    NmeaParser parser;
    parser.addSentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,0,08,0.9,"
                       "100.0,M,-34.0,M,,*7C");
    parser.parse();
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, InvalidGGA)
{
    NmeaParser parser;
    parser.addSentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1"
                       "100.0,M,-34.0,M,,*7C");
    parser.parse();
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, InvalidChecksum)
{
    NmeaParser parser;
    parser.addSentence("$GNGGA,120000.00,3409.3251,N,11849.1290,W,1,08,0.9,"
                       "100.0,M,-34.0,M,,*AA");
    parser.parse();
    ASSERT_FALSE(parser.getLastPosition().isValid());
}

TEST(ParsersNMEA, AddMultipleScentencesIncreasedVersion)
{
    NmeaParser parser;
    parser.addSentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A*64");
    ASSERT_EQ(parser.getLastPosition().getVersion(), 1);
    parser.addSentence(
        "$GNRMC,120000.000,A,3409.3251,N,11949.1290,W,0.00,0.00,061125,,,A*65");
    ASSERT_EQ(parser.getLastPosition().getVersion(), 2);
}

TEST(ParsersNMEA, AddMultipleSameScentencesDontIncreaseVersion)
{
    NmeaParser parser;
    parser.addSentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A*64");
    ASSERT_EQ(parser.getLastPosition().getVersion(), 1);
    parser.addSentence(
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,061125,,,A*64");
    ASSERT_EQ(parser.getLastPosition().getVersion(), 1);
}

TEST(NmeaValidator, TestConstruction)
{
    NmeaValidator validator;
    ASSERT_FALSE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
    ASSERT_EQ(validator.getBuffer(), "");
}

TEST(NmeaValidator, TestStartWithDollar)
{
    NmeaValidator validator;
    validator.addCharacter('$');
    ASSERT_TRUE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
}

TEST(NmeaValidator, TestStartWithNotDollar)
{
    NmeaValidator validator;
    validator.addCharacter('#');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
}

TEST(NmeaValidator, TestStartWithDollarThenEndWithNewLine_Accepted)
{
    NmeaValidator validator;
    validator.addCharacter('$');
    validator.addCharacter('.');
    validator.addCharacter('\n');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_TRUE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
    ASSERT_EQ(validator.getBuffer(), "$.");
}

TEST(NmeaValidator, TestStartWithDollarThenEndWithCarrieReturn_Accepted)
{
    NmeaValidator validator;
    validator.addCharacter('$');
    validator.addCharacter('.');
    validator.addCharacter('\r');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_TRUE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
    ASSERT_EQ(validator.getBuffer(), "$.");
}

TEST(NmeaValidator, TestStartWithDollarThenAnotherDollar_Error)
{
    NmeaValidator validator;
    validator.addCharacter('$');
    validator.addCharacter('.');
    validator.addCharacter('$');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_TRUE(validator.isError());
}

TEST(NmeaValidator, TestStringTooLong)
{
    NmeaValidator validator;
    validator.addCharacter('$');
    for (uint32_t x = 0; x < 82; x++)
        validator.addCharacter('a');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_TRUE(validator.isError());
}

TEST(NmeaValidator, TestEndToEnd)
{
    NmeaValidator validator;

    validator.addCharacter('t');
    validator.addCharacter('e');
    validator.addCharacter('s');
    validator.addCharacter('t');
    validator.addCharacter('$');
    validator.addCharacter('m');
    validator.addCharacter('t');
    validator.addCharacter('\r');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_TRUE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
    ASSERT_EQ(validator.getBuffer(), "$mt");
    validator.reset();
    ASSERT_EQ(validator.getBuffer(), "");
    ASSERT_FALSE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
}

TEST(NmeaValidator, TestDataAfterFinished)
{
    NmeaValidator validator;

    validator.addCharacter('t');
    validator.addCharacter('e');
    validator.addCharacter('s');
    validator.addCharacter('t');
    validator.addCharacter('$');
    validator.addCharacter('m');
    validator.addCharacter('t');
    validator.addCharacter('\r');
    validator.addCharacter('$');
    validator.addCharacter('a');
    validator.addCharacter('b');
    ASSERT_FALSE(validator.isStarted());
    ASSERT_TRUE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
    ASSERT_EQ(validator.getBuffer(), "$mt");
    validator.reset();
    ASSERT_EQ(validator.getBuffer(), "");
    ASSERT_FALSE(validator.isStarted());
    ASSERT_FALSE(validator.isAccepted());
    ASSERT_FALSE(validator.isError());
}
