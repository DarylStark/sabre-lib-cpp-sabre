#include "sabre/core/exceptions.hpp"
#include <gtest/gtest.h>

TEST(SabreExceptionTest, CustomMessage)
{
    sabre::core::SabreException ex("Custom error message");
    ASSERT_STREQ(ex.what(), "Custom error message");
}

TEST(SabreExceptionTest, APIErrorDefaultMessage)
{
    sabre::core::ApiError apiError;
    ASSERT_STREQ(apiError.what(), "Unknown API error");
}

TEST(SabreExceptionTest, APIErrorCustomMessage)
{
    class DerivedAPIError : public sabre::core::ApiError
    {
    public:
        DerivedAPIError(const std::string &msg) : sabre::core::ApiError(msg) {}
    };
    DerivedAPIError apiError("Specific API error occurred");
    ASSERT_STREQ(apiError.what(), "Specific API error occurred");
}
