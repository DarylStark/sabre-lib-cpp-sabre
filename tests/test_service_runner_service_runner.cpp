#include "sabre_testing/service_runner/service_runner.hpp"
#include <gtest/gtest.h>

TEST(ServiceRunner, Functor)
{
    sabre::testing::ServiceRunner runner;
    runner();
    ASSERT_TRUE(runner.is_running());
}