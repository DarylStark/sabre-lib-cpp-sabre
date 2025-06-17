#include "sabre_testing/utility/timed_waiter.hpp"
#include <gtest/gtest.h>

TEST(TimedWaiter, RunSuccessfulPredicate)
{
    sabre::TimedWaiterPred pred = []() -> bool { return true; };
    sabre::testing::TimedWaiter tw(pred, 100, 10);
    ASSERT_TRUE(tw());
    ASSERT_TRUE(tw.get_result());
}

TEST(TimedWaiter, RunFailingPredicate)
{
    sabre::TimedWaiterPred pred = []() -> bool { return false; };
    sabre::testing::TimedWaiter tw(pred, 100, 10);
    ASSERT_FALSE(tw());
    ASSERT_FALSE(tw.get_result());
}

TEST(TimedWaiter, RunSuccessfulPredicateAfterAFewIterations)
{
    int n = 0;
    sabre::TimedWaiterPred pred = [&n]() -> bool { return n++ == 5; };
    sabre::testing::TimedWaiter tw(pred, 1000, 10);
    ASSERT_TRUE(tw());
    ASSERT_TRUE(tw.get_result());
    ASSERT_GT(tw.get_result_runtime(), 50);
}