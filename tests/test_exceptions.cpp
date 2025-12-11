#include "sabre/exceptions/exceptions.hpp"
#include <gtest/gtest.h>

TEST(SabreExceptionTest, CustomMessage)
{
    Sabre::SabreException ex("Custom error message");
    ASSERT_STREQ(ex.what(), "Custom error message");
}

TEST(SabreExceptionTest, APIErrorDefaultMessage)
{
    Sabre::APIError apiError;
    ASSERT_STREQ(apiError.what(), "Unknown API error");
}

TEST(SabreExceptionTest, APIErrorCustomMessage)
{
    class DerivedAPIError : public Sabre::APIError
    {
    public:
        DerivedAPIError(const std::string &msg) : Sabre::APIError(msg) {}
    };
    DerivedAPIError apiError("Specific API error occurred");
    ASSERT_STREQ(apiError.what(), "Specific API error occurred");
}