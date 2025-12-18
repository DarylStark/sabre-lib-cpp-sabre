#include "sabre/parsers/nmea_validator.hpp"
#include <gtest/gtest.h>

using namespace sabre::parsers;

TEST(NmeaValidator, TestConstruction)
{
    NmeaValidator validator;
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "");
}

TEST(NmeaValidator, TestStartWithDollar)
{
    NmeaValidator validator;
    validator.add_character('$');
    ASSERT_TRUE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
}

TEST(NmeaValidator, TestStartWithNotDollar)
{
    NmeaValidator validator;
    validator.add_character('#');
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
}

TEST(NmeaValidator, TestStartWithDollarThenEndWithNewLine_Accepted)
{
    NmeaValidator validator;
    validator.add_character('$');
    validator.add_character('.');
    validator.add_character('\n');
    ASSERT_FALSE(validator.is_started());
    ASSERT_TRUE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "$.");
}

TEST(NmeaValidator, TestStartWithDollarThenEndWithCarrieReturn_Accepted)
{
    NmeaValidator validator;
    validator.add_character('$');
    validator.add_character('.');
    validator.add_character('\r');
    ASSERT_FALSE(validator.is_started());
    ASSERT_TRUE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "$.");
}

TEST(NmeaValidator, TestStartWithDollarThenAnotherDollar_Error)
{
    NmeaValidator validator;
    validator.add_character('$');
    validator.add_character('.');
    validator.add_character('$');
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_TRUE(validator.is_error());
}

TEST(NmeaValidator, TestStringTooLong)
{
    NmeaValidator validator;
    validator.add_character('$');
    for (uint32_t x = 0; x < 82; x++)
        validator.add_character('a');
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_TRUE(validator.is_error());
}

TEST(NmeaValidator, TestEndToEnd)
{
    NmeaValidator validator;

    validator.add_character('t');
    validator.add_character('e');
    validator.add_character('s');
    validator.add_character('t');
    validator.add_character('$');
    validator.add_character('m');
    validator.add_character('t');
    validator.add_character('\r');
    ASSERT_FALSE(validator.is_started());
    ASSERT_TRUE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "$mt");
    validator.reset();
    ASSERT_EQ(validator.get_buffer(), "");
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
}

TEST(NmeaValidator, TestDataAfterFinished)
{
    NmeaValidator validator;

    validator.add_character('t');
    validator.add_character('e');
    validator.add_character('s');
    validator.add_character('t');
    validator.add_character('$');
    validator.add_character('m');
    validator.add_character('t');
    validator.add_character('\r');
    validator.add_character('$');
    validator.add_character('a');
    validator.add_character('b');
    ASSERT_FALSE(validator.is_started());
    ASSERT_TRUE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "$mt");
    validator.reset();
    ASSERT_EQ(validator.get_buffer(), "");
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
}