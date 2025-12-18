#include "sabre_testing/utility/wait_for.hpp"
#include <gtest/gtest.h>

TEST(WaitFor, RunSuccessfulPredicate)
{
    sabre::utility::WaitForPred pred = []() -> bool { return true; };
    sabre::impl::sabre_testing::WaitFor tw(pred, 100, 10);
    ASSERT_TRUE(tw());
    ASSERT_TRUE(tw.get_result());
}

TEST(WaitFor, RunFailingPredicate)
{
    sabre::utility::WaitForPred pred = []() -> bool { return false; };
    sabre::impl::sabre_testing::WaitFor tw(pred, 100, 10);
    ASSERT_FALSE(tw());
    ASSERT_FALSE(tw.get_result());
}

TEST(WaitFor, RunSuccessfulPredicateAfterAFewIterations)
{
    int n = 0;
    sabre::utility::WaitForPred pred = [&n]() -> bool { return n++ == 5; };
    sabre::impl::sabre_testing::WaitFor tw(pred, 1000, 10);
    ASSERT_TRUE(tw());
    ASSERT_TRUE(tw.get_result());
    ASSERT_GT(tw.get_result_runtime(), 50);
}