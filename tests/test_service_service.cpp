#include "sabre_testing/os.hpp"
#include <gtest/gtest.h>

TEST(Service, StartingWithALambda)
{
    int var = 0;
    sabre::impl::sabre_testing::Service my_service([&var]() { ++var; });
    my_service.start();

    ASSERT_EQ(var, 1);
}

void MyVarIncrementServiceFunction(int *var)
{
    ++(*var);
}

TEST(Service, StartingWithAFunction)
{
    int var = 0;
    sabre::impl::sabre_testing::Service my_service(
        std::bind(MyVarIncrementServiceFunction, &var));
    my_service.start();
    ASSERT_EQ(var, 1);
}

class MyVarIncrementServiceFunctor
{
public:
    int var = 0;
    void operator()()
    {
        ++var;
        asm("nop");
    }
};

TEST(Service, StartingWithAFunctor)
{
    MyVarIncrementServiceFunctor fn;
    sabre::impl::sabre_testing::Service my_service(std::ref(fn));
    my_service.start();
    ASSERT_EQ(fn.var, 1);
}