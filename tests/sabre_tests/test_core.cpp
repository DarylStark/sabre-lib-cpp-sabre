#include "test_core.hpp"
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

TEST_F(SabreGpioResourceManagerTest, CreateDifferentInputGpios)
{
    const auto &gpio1 = _manager.getInputGpio(26);
    const auto &gpio2 = _manager.getInputGpio(25);
    ASSERT_NE(&gpio1, &gpio2);
}

TEST_F(SabreGpioResourceManagerTest, CreateInputGpioTwice)
{
    const auto &gpio1 = _manager.getInputGpio(26);
    const auto &gpio2 = _manager.getInputGpio(26);
    ASSERT_EQ(&gpio1, &gpio2);
}

TEST_F(SabreGpioResourceManagerTest, CreateDifferentOutputGpios)
{
    const auto &gpio1 = _manager.getOutputGpio(26);
    const auto &gpio2 = _manager.getOutputGpio(25);
    ASSERT_NE(&gpio1, &gpio2);
}

TEST_F(SabreGpioResourceManagerTest, CreateOutputGpioTwice)
{
    const auto &gpio1 = _manager.getOutputGpio(26);
    const auto &gpio2 = _manager.getOutputGpio(26);
    ASSERT_EQ(&gpio1, &gpio2);
}

TEST_F(SabreGpioResourceManagerTest, CreateOutputAfterInput)
{
    const auto &gpio1 = _manager.getInputGpio(26);
    ASSERT_THROW(_manager.getOutputGpio(26), sabre::core::GpioInUseException);
}

TEST_F(SabreGpioResourceManagerTest, CreateInputAfterOuput)
{
    const auto &gpio1 = _manager.getOutputGpio(26);
    ASSERT_THROW(_manager.getInputGpio(26), sabre::core::GpioInUseException);
}

TEST_F(SabreGpioResourceManagerTest, CreateInputGpioToHigh)
{
    ASSERT_THROW(const auto &gpio1 = _manager.getInputGpio(30),
                 sabre::core::GpioUnavailableException);
}

TEST_F(SabreGpioResourceManagerTest, CreateOutputGpioToHigh)
{
    ASSERT_THROW(const auto &gpio1 = _manager.getOutputGpio(30),
                 sabre::core::GpioUnavailableException);
}

TEST_F(SabreGpioResourceManagerTest, CreateInputGpioToLow)
{
    ASSERT_THROW(const auto &gpio1 = _manager.getInputGpio(-1),
                 sabre::core::GpioUnavailableException);
}

TEST_F(SabreGpioResourceManagerTest, CreateOutputGpioToLow)
{
    ASSERT_THROW(const auto &gpio1 = _manager.getOutputGpio(-1),
                 sabre::core::GpioUnavailableException);
}

TEST_F(SabreGpioResourceManagerTest, CreateInputGpioZero)
{
    ASSERT_NO_THROW(const auto &gpio1 = _manager.getInputGpio(0));
}

TEST_F(SabreGpioResourceManagerTest, CreateOutputGpioZero)
{
    ASSERT_NO_THROW(const auto &gpio1 = _manager.getOutputGpio(0));
}

TEST_F(SabreGpioResourceManagerTest, CreateInputGpioExactlyUpperBound)
{
    ASSERT_NO_THROW(const auto &gpio1 = _manager.getInputGpio(26));
}

TEST_F(SabreGpioResourceManagerTest, CreateOutputGpioExactlyUpperBound)
{
    ASSERT_NO_THROW(const auto &gpio1 = _manager.getOutputGpio(26));
}

TEST_F(SabreGpioResourceManagerTest, CreateGpioTwice)
{
    const auto &gpio1 = _manager.getGpio(26);
    const auto &gpio2 = _manager.getGpio(26);
    ASSERT_EQ(&gpio1, &gpio2);
}

TEST_F(SabreGpioResourceManagerTest, CreateDifferentGpios)
{
    const auto &gpio1 = _manager.getGpio(26);
    const auto &gpio2 = _manager.getGpio(25);
    ASSERT_NE(&gpio1, &gpio2);
}

TEST_F(SabreGpioResourceManagerTest, CreateGpioAfterOuput)
{
    const auto &gpio1 = _manager.getOutputGpio(26);
    ASSERT_THROW(_manager.getGpio(26), sabre::core::GpioInUseException);
}

TEST_F(SabreGpioResourceManagerTest, CreateGpioToHigh)
{
    ASSERT_THROW(const auto &gpio1 = _manager.getGpio(30),
                 sabre::core::GpioUnavailableException);
}

TEST_F(SabreGpioResourceManagerTest, CreateGpioToLow)
{
    ASSERT_THROW(const auto &gpio1 = _manager.getGpio(-1),
                 sabre::core::GpioUnavailableException);
}

TEST_F(SabreGpioResourceManagerTest, CreateGpioZero)
{
    ASSERT_NO_THROW(const auto &gpio1 = _manager.getGpio(0));
}
