#include "sabre/core/exceptions.hpp"
#include "sabre/core/gpio_resource_manager.hpp"
#include "sabre_test_mocks/core.hpp"
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

TEST(SabreGpioResourceManager, CreateDifferentInputGpios)
{
    using namespace sabre::core;

    sabre::impl::sabre_test_mocks::StFactory factory(false);

    GpioResourceManager manager = GpioResourceManager(factory, 26);
    const auto &gpio1 = manager.getInputGpio(26);
    const auto &gpio2 = manager.getInputGpio(27);

    ASSERT_NE(&gpio1, &gpio2);
}

TEST(SabreGpioResourceManager, CreateInputGpioTwice)
{
    using namespace sabre::core;

    sabre::impl::sabre_test_mocks::StFactory factory(false);

    GpioResourceManager manager = GpioResourceManager(factory, 26);
    const auto &gpio1 = manager.getInputGpio(26);
    const auto &gpio2 = manager.getInputGpio(26);

    ASSERT_EQ(&gpio1, &gpio2);
}

TEST(SabreGpioResourceManager, CreateDifferentOutputGpios)
{
    using namespace sabre::core;

    sabre::impl::sabre_test_mocks::StFactory factory(false);

    GpioResourceManager manager = GpioResourceManager(factory, 26);
    const auto &gpio1 = manager.getOutputGpio(26);
    const auto &gpio2 = manager.getOutputGpio(27);

    ASSERT_NE(&gpio1, &gpio2);
}

TEST(SabreGpioResourceManager, CreateOutputGpioTwice)
{
    using namespace sabre::core;

    sabre::impl::sabre_test_mocks::StFactory factory(false);

    GpioResourceManager manager = GpioResourceManager(factory, 26);
    const auto &gpio1 = manager.getOutputGpio(26);
    const auto &gpio2 = manager.getOutputGpio(26);

    ASSERT_EQ(&gpio1, &gpio2);
}

TEST(SabreGpioResourceManager, CreateOutputAfterInput)
{
    using namespace sabre::core;

    sabre::impl::sabre_test_mocks::StFactory factory(false);

    GpioResourceManager manager = GpioResourceManager(factory, 26);
    const auto &gpio1 = manager.getInputGpio(26);
    ASSERT_THROW(manager.getOutputGpio(26), GpioInUseException);
}

TEST(SabreGpioResourceManager, CreateInputAfterOuput)
{
    using namespace sabre::core;

    sabre::impl::sabre_test_mocks::StFactory factory(false);

    GpioResourceManager manager = GpioResourceManager(factory, 26);
    const auto &gpio1 = manager.getOutputGpio(26);
    ASSERT_THROW(manager.getInputGpio(26), GpioInUseException);
}