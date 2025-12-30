#include "sabre/parsers/nmea_validator.hpp"
#include <gtest/gtest.h>

using namespace sabre::parsers;

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