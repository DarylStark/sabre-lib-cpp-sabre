#include "sabre_test_mocks/core.hpp"
#include <gtest/gtest.h>

using sabre::impl::sabre_testing::StFactory;
using sabre::impl::sabre_testing::TestApp;

TEST(App, AppSetFactory)
{
    TestApp app;
    auto factory = std::make_unique<StFactory>();
    auto factory_ptr = factory.get();
    app.setFactory(std::move(factory));
    EXPECT_EQ(app.getFactory().get(), factory_ptr);
}

TEST(App, AppConstructorWithFactory)
{
    auto factory = std::make_unique<StFactory>();
    auto factory_ptr = factory.get();
    TestApp app(std::move(factory));
    EXPECT_EQ(app.getFactory().get(), factory_ptr);
}

TEST(App, AppDefaultConstructor)
{
    TestApp app;
    EXPECT_EQ(app.getFactory(), nullptr);
}
