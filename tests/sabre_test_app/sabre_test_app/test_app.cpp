#include "test_app.hpp"

MyAppNoArgs::MyAppNoArgs(sabre::core::ResourceManager &rm)
    : sabre::runtime::App<void>(rm)
{
}

void MyAppNoArgs::run() {}

MyAppOneArg::MyAppOneArg(sabre::core::ResourceManager &rm, uint32_t argument)
    : sabre::runtime::App<void>(rm)
{
}

void MyAppOneArg::run() {}

MyAppOneArgReturnValue::MyAppOneArgReturnValue(sabre::core::ResourceManager &rm,
                                               uint32_t returnValue)
    : sabre::runtime::App<uint32_t>(rm), _returnValue(returnValue)
{
}

uint32_t MyAppOneArgReturnValue::run()
{
    return _returnValue;
}

MyAppReturnSmartPointer::MyAppReturnSmartPointer(
    sabre::core::ResourceManager &rm)
    : sabre::runtime::App<std::shared_ptr<ReturnData>>(rm)
{
}

std::shared_ptr<ReturnData> MyAppReturnSmartPointer::run()
{
    return std::make_shared<ReturnData>(
        ReturnData{20, "Sabre framework tests"});
}
