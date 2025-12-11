#include "sabre_testing/app/app.hpp"
#include "sabre_testing/factory.hpp"
#include <gtest/gtest.h>

using Sabre::Testing::Factory;
using Sabre::Testing::TestApp;

TEST(App, AppSetFactory)
{
    TestApp app;
    auto factory = std::make_unique<Factory>();
    auto factory_ptr = factory.get();
    app.set_factory(std::move(factory));
    EXPECT_EQ(app.get_factory().get(), factory_ptr);
}

TEST(App, AppConstructorWithFactory)
{
    auto factory = std::make_unique<Factory>();
    auto factory_ptr = factory.get();
    TestApp app(std::move(factory));
    EXPECT_EQ(app.get_factory().get(), factory_ptr);
}

TEST(App, AppDefaultConstructor)
{
    TestApp app;
    EXPECT_EQ(app.get_factory(), nullptr);
}

TEST(App, RunAppFunctionNoFactory)
{
    TestApp app;
    EXPECT_ANY_THROW(Sabre::run_app(app));
}

TEST(App, RunAppFunction)
{
    TestApp app;
    auto factory = std::make_unique<Factory>();
    app.set_factory(std::move(factory));
    EXPECT_NO_THROW(Sabre::run_app(app));
}