#include "sabre_testing/gpio/input_gpio.hpp"
#include <gtest/gtest.h>

TEST(InputGPIO, DefaultInverseLevel)
{
    sabre::testing::InputGPIO gpio;
    ASSERT_FALSE(gpio.get_inverse_level());
}

TEST(InputGPIO, SetInverseLevelTrue)
{
    sabre::testing::InputGPIO gpio;
    gpio.set_inverse_level();
    ASSERT_TRUE(gpio.get_inverse_level());
}

TEST(InputGPIO, SetInverseLevelFalse)
{
    sabre::testing::InputGPIO gpio;
    gpio.set_original_level();
    ASSERT_FALSE(gpio.get_inverse_level());
}

TEST(InputGPIO, CheckLevelInversionFalseTrue)
{
    sabre::testing::InputGPIO gpio;
    gpio.level = false;
    gpio.set_inverse_level();
    ASSERT_TRUE(gpio.get_level());
}

TEST(InputGPIO, CheckLevelInversionFalseFalse)
{
    sabre::testing::InputGPIO gpio;
    gpio.level = false;
    gpio.set_original_level();
    ASSERT_FALSE(gpio.get_level());
}

TEST(InputGPIO, CheckLevelInversionTrueFalse)
{
    sabre::testing::InputGPIO gpio;
    gpio.level = true;
    gpio.set_original_level();
    ASSERT_TRUE(gpio.get_level());
}

TEST(InputGPIO, CheckLevelInversionTrueTrue)
{
    sabre::testing::InputGPIO gpio;
    gpio.level = true;
    gpio.set_inverse_level();
    ASSERT_FALSE(gpio.get_level());
}