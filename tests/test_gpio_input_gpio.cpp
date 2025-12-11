#include "sabre_testing/gpio/input_gpio.hpp"
#include <gtest/gtest.h>

TEST(InputGPIO, DefaultInverseLevel)
{
    Sabre::Testing::InputGPIO gpio;
    ASSERT_FALSE(gpio.get_inverse_level());
}

TEST(InputGPIO, SetInverseLevelTrue)
{
    Sabre::Testing::InputGPIO gpio;
    gpio.set_inverse_level(true);
    ASSERT_TRUE(gpio.get_inverse_level());
}

TEST(InputGPIO, SetInverseLevelFalse)
{
    Sabre::Testing::InputGPIO gpio;
    gpio.set_inverse_level(false);
    ASSERT_FALSE(gpio.get_inverse_level());
}

TEST(InputGPIO, CheckLevelInversionFalseTrue)
{
    Sabre::Testing::InputGPIO gpio;
    gpio.level = false;
    gpio.set_inverse_level(true);
    ASSERT_TRUE(gpio.get_level());
}

TEST(InputGPIO, CheckLevelInversionFalseFalse)
{
    Sabre::Testing::InputGPIO gpio;
    gpio.level = false;
    gpio.set_inverse_level(false);
    ASSERT_FALSE(gpio.get_level());
}

TEST(InputGPIO, CheckLevelInversionTrueFalse)
{
    Sabre::Testing::InputGPIO gpio;
    gpio.level = true;
    gpio.set_inverse_level(false);
    ASSERT_TRUE(gpio.get_level());
}

TEST(InputGPIO, CheckLevelInversionTrueTrue)
{
    Sabre::Testing::InputGPIO gpio;
    gpio.level = true;
    gpio.set_inverse_level(true);
    ASSERT_FALSE(gpio.get_level());
}