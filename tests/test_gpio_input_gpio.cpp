#include "sabre_testing/hal.hpp"
#include <gtest/gtest.h>

TEST(InputGpio, DefaultInverseLevel)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    ASSERT_FALSE(gpio.get_inverse_level());
}

TEST(InputGpio, SetInverseLevelTrue)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.set_inverse_level(true);
    ASSERT_TRUE(gpio.get_inverse_level());
}

TEST(InputGpio, SetInverseLevelFalse)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.set_inverse_level(false);
    ASSERT_FALSE(gpio.get_inverse_level());
}

TEST(InputGpio, CheckLevelInversionFalseTrue)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = false;
    gpio.set_inverse_level(true);
    ASSERT_TRUE(gpio.get_level());
}

TEST(InputGpio, CheckLevelInversionFalseFalse)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = false;
    gpio.set_inverse_level(false);
    ASSERT_FALSE(gpio.get_level());
}

TEST(InputGpio, CheckLevelInversionTrueFalse)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = true;
    gpio.set_inverse_level(false);
    ASSERT_TRUE(gpio.get_level());
}

TEST(InputGpio, CheckLevelInversionTrueTrue)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = true;
    gpio.set_inverse_level(true);
    ASSERT_FALSE(gpio.get_level());
}