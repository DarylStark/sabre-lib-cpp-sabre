#include "sabre/parsers/nmea_validator.hpp"
#include <gtest/gtest.h>

using namespace Sabre::Parsers;

TEST(NMEAValidator, TestConstruction)
{
    NMEAValidator validator;
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "");
}

TEST(NMEAValidator, TestStartWithDollar)
{
    NMEAValidator validator;
    validator.add_character('$');
    ASSERT_TRUE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
}

TEST(NMEAValidator, TestStartWithNotDollar)
{
    NMEAValidator validator;
    validator.add_character('#');
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
}

TEST(NMEAValidator, TestStartWithDollarThenEndWithNewLine_Accepted)
{
    NMEAValidator validator;
    validator.add_character('$');
    validator.add_character('.');
    validator.add_character('\n');
    ASSERT_FALSE(validator.is_started());
    ASSERT_TRUE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "$.");
}

TEST(NMEAValidator, TestStartWithDollarThenEndWithCarrieReturn_Accepted)
{
    NMEAValidator validator;
    validator.add_character('$');
    validator.add_character('.');
    validator.add_character('\r');
    ASSERT_FALSE(validator.is_started());
    ASSERT_TRUE(validator.is_accepted());
    ASSERT_FALSE(validator.is_error());
    ASSERT_EQ(validator.get_buffer(), "$.");
}

TEST(NMEAValidator, TestStartWithDollarThenAnotherDollar_Error)
{
    NMEAValidator validator;
    validator.add_character('$');
    validator.add_character('.');
    validator.add_character('$');
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_TRUE(validator.is_error());
}

TEST(NMEAValidator, TestStringTooLong)
{
    NMEAValidator validator;
    validator.add_character('$');
    for (uint32_t x = 0; x < 82; x++)
        validator.add_character('a');
    ASSERT_FALSE(validator.is_started());
    ASSERT_FALSE(validator.is_accepted());
    ASSERT_TRUE(validator.is_error());
}

TEST(NMEAValidator, TestEndToEnd)
{
    NMEAValidator validator;

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

TEST(NMEAValidator, TestDataAfterFinished)
{
    NMEAValidator validator;

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