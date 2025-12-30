#include "sabre_test_mocks/hal.hpp"
#include <gtest/gtest.h>

TEST(InputGpio, DefaultInverseLevel)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    ASSERT_FALSE(gpio.getInverseLevel());
}

TEST(InputGpio, SetInverseLevelTrue)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.setInverseLevel(true);
    ASSERT_TRUE(gpio.getInverseLevel());
}

TEST(InputGpio, SetInverseLevelFalse)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.setInverseLevel(false);
    ASSERT_FALSE(gpio.getInverseLevel());
}

TEST(InputGpio, CheckLevelInversionFalseTrue)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = false;
    gpio.setInverseLevel(true);
    ASSERT_TRUE(gpio.getLevel());
}

TEST(InputGpio, CheckLevelInversionFalseFalse)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = false;
    gpio.setInverseLevel(false);
    ASSERT_FALSE(gpio.getLevel());
}

TEST(InputGpio, CheckLevelInversionTrueFalse)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = true;
    gpio.setInverseLevel(false);
    ASSERT_TRUE(gpio.getLevel());
}

TEST(InputGpio, CheckLevelInversionTrueTrue)
{
    sabre::impl::sabre_testing::StInputGpio gpio;
    gpio.level = true;
    gpio.setInverseLevel(true);
    ASSERT_FALSE(gpio.getLevel());
}