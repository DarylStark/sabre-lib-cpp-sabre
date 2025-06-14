#include <gtest/gtest.h>
#include <sabre/generic/ipv4_address.h>
#include <string>

TEST(IPv4Address, Octets)
{
    sabre::IPv4Address add(3232242231);
    ASSERT_TRUE(add[0] == 192);
    ASSERT_TRUE(add[1] == 168);
    ASSERT_TRUE(add[2] == 26);
    ASSERT_TRUE(add[3] == 55);
}

TEST(IPv4Address, StringConversion)
{
    sabre::IPv4Address add(3232242231);
    std::string ip = static_cast<std::string>(add);
    ASSERT_TRUE(ip == "192.168.26.55");
}
