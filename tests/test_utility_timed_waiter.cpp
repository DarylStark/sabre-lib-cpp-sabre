#include "sabre_testing/utility/wait_for.hpp"
#include <gtest/gtest.h>

TEST(WaitFor, RunSuccessfulPredicate)
{
    sabre::WaitForPred pred = []() -> bool { return true; };
    sabre::testing::WaitFor tw(pred, 100, 10);
    ASSERT_TRUE(tw());
    ASSERT_TRUE(tw.get_result());
}

TEST(WaitFor, RunFailingPredicate)
{
    sabre::WaitForPred pred = []() -> bool { return false; };
    sabre::testing::WaitFor tw(pred, 100, 10);
    ASSERT_FALSE(tw());
    ASSERT_FALSE(tw.get_result());
}

TEST(WaitFor, RunSuccessfulPredicateAfterAFewIterations)
{
    int n = 0;
    sabre::WaitForPred pred = [&n]() -> bool { return n++ == 5; };
    sabre::testing::WaitFor tw(pred, 1000, 10);
    ASSERT_TRUE(tw());
    ASSERT_TRUE(tw.get_result());
    ASSERT_GT(tw.get_result_runtime(), 50);
}