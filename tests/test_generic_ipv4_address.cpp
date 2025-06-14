#include <gtest/gtest.h>
#include <sabre/generic/ipv4_address.h>
#include <sstream>
#include <string>

TEST(IPv4Address, EmptyConstructor)
{
    sabre::IPv4Address add;
    ASSERT_EQ(static_cast<uint32_t>(add), 0);
}

TEST(IPv4Address, Setting)
{
    sabre::IPv4Address add;
    add.set(3232242232);
    ASSERT_EQ(static_cast<uint32_t>(add), 3232242232);
}

TEST(IPv4Address, Octets)
{
    sabre::IPv4Address add(3232242231);
    ASSERT_EQ(add[0], 192);
    ASSERT_EQ(add[1], 168);
    ASSERT_EQ(add[2], 26);
    ASSERT_EQ(add[3], 55);
}

TEST(IPv4Address, StringConversion)
{
    sabre::IPv4Address add(3232242231);
    std::string ip = static_cast<std::string>(add);
    ASSERT_EQ(ip, "192.168.26.55");
}

TEST(IPv4Address, UInt32Conversion)
{
    sabre::IPv4Address add(3232242231);
    uint32_t ip = static_cast<uint32_t>(add);
    ASSERT_EQ(ip, 3232242231);
}

TEST(IPv4Address, OStreamOperator)
{
    std::stringstream oss;
    std::streambuf *old_cout = std::cout.rdbuf(oss.rdbuf());
    sabre::IPv4Address add(3232242231);

    std::cout << add;

    std::cout.rdbuf(old_cout);

    ASSERT_EQ(oss.str(), "192.168.26.55");
}
