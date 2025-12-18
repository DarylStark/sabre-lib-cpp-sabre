#include "sabre_testing/core.hpp"
#include <gtest/gtest.h>

using sabre::impl::sabre_testing::StFactory;
using sabre::impl::sabre_testing::TestApp;

TEST(App, AppSetFactory)
{
    TestApp app;
    auto factory = std::make_unique<StFactory>();
    auto factory_ptr = factory.get();
    app.set_factory(std::move(factory));
    EXPECT_EQ(app.get_factory().get(), factory_ptr);
}

TEST(App, AppConstructorWithFactory)
{
    auto factory = std::make_unique<StFactory>();
    auto factory_ptr = factory.get();
    TestApp app(std::move(factory));
    EXPECT_EQ(app.get_factory().get(), factory_ptr);
}

TEST(App, AppDefaultConstructor)
{
    TestApp app;
    EXPECT_EQ(app.get_factory(), nullptr);
}
