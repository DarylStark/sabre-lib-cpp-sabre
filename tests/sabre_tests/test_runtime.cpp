#include <gtest/gtest.h>
#include <sabre/core/factory.hpp>
#include <sabre_test_app/test_app.hpp>
#include <sabre_test_mocks/core.hpp>
#include <sabre_test_mocks/runtime.hpp>

#include <sabre/runtime/run_app.hpp>

using namespace sabre::impl::sabre_test_mocks;

TEST(RuntimeTest, TestAppStartWithoutArguments)
{
    ASSERT_NO_THROW(RunApp<MyAppNoArgs>());
}

TEST(RuntimeTest, TestAppStartWithOneArgument)
{
    ASSERT_NO_THROW(RunApp<MyAppOneArg>(10));
}

TEST(RuntimeTest, TestAppWithReturnValue)
{
    uint32_t retval = RunApp<MyAppOneArgReturnValue>(2610);
    ASSERT_EQ(retval, 2610);
}

TEST(RuntimeTest, TestAppWithReturnSmartPointer)
{
    std::shared_ptr<ReturnData> retval = nullptr;

    {
        retval = RunApp<MyAppReturnSmartPointer>();
    }

    ASSERT_NE(retval, nullptr);

    ASSERT_EQ(retval->returnValue, 20);
    ASSERT_EQ(retval->returnString, "Sabre framework tests");
}

TEST(RuntimeTest, TestAppGetFactory)
{
    StFactory factory;
    sabre::core::ResourceManager resourceManager(factory, {10, 20});
    MyAppNoArgs app(resourceManager);

    ASSERT_EQ(&app.getFactory(), &factory);
}