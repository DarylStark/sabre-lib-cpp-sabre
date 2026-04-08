#include <gtest/gtest.h>
#include <sabre/types/types.hpp>

using sabre::types::Color;

TEST(TypesColor, DefaultConstructor)
{
    Color c;
    ASSERT_EQ(c.red, 0);
    ASSERT_EQ(c.green, 0);
    ASSERT_EQ(c.blue, 0);
}

TEST(TypesColor, ArgumentedConstructor)
{
    Color c(10, 20, 30);
    ASSERT_EQ(c.red, 10);
    ASSERT_EQ(c.green, 20);
    ASSERT_EQ(c.blue, 30);
}

TEST(TypesColor, Clear)
{

    Color c(10, 20, 30);
    c.clear();
    ASSERT_EQ(c.red, 0);
    ASSERT_EQ(c.green, 0);
    ASSERT_EQ(c.blue, 0);
}

TEST(TypesColor, SetBrightness)
{
    Color c(100, 200, 150);
    c.applyBrightness(0.5);
    ASSERT_EQ(c.red, 50);
    ASSERT_EQ(c.green, 100);
    ASSERT_EQ(c.blue, 75);
}

TEST(TypesColor, Equality)
{
    Color a(100, 200, 150);
    Color b(100, 200, 150);
    ASSERT_EQ(a, b);
}

TEST(TypesColor, Inequality)
{
    Color a(100, 200, 150);
    Color b(200, 100, 150);
    ASSERT_NE(a, b);
}