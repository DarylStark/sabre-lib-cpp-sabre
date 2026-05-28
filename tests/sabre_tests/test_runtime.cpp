#include <gtest/gtest.h>
#include <sabre_test_app/test_app.hpp>
#include <sabre_test_mocks/runtime.hpp>

#include <sabre/runtime/run_app.hpp>
#include <type_traits>
#include <utility>

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

TEST(RuntimeTest, AppGetResourceManagerReturnsMutableReference)
{
    static_assert(std::is_same_v<
                  decltype(std::declval<MyAppNoArgs &>().getResourceManager()),
                  sabre::core::ResourceManager &>);

    StFactory factory;
    sabre::core::ResourceManager resourceManager(factory, {10, 20});
    MyAppNoArgs app(resourceManager);

    auto &manager = app.getResourceManager();
    manager.getLogManager().setLevel(sabre::log::LoggingLevel::DEBUG);

    ASSERT_EQ(resourceManager.getLogManager().getLevel(),
              sabre::log::LoggingLevel::DEBUG);
}
