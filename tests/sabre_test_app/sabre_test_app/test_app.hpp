#pragma once

#include <sabre/runtime/app.hpp>

class MyAppNoArgs : public sabre::runtime::App<void>
{
public:
    MyAppNoArgs(sabre::core::ResourceManager &rm);
    void run() override;
};

class MyAppOneArg : public sabre::runtime::App<void>
{
public:
    MyAppOneArg(sabre::core::ResourceManager &rm, uint32_t argument);
    void run() override;
};

class MyAppOneArgReturnValue : public sabre::runtime::App<uint32_t>
{
private:
    uint32_t _returnValue;

public:
    MyAppOneArgReturnValue(sabre::core::ResourceManager &rm,
                           uint32_t returnValue);
    uint32_t run() override;
};

struct ReturnData
{
    int32_t returnValue;
    std::string returnString;
};

class MyAppReturnSmartPointer
    : public sabre::runtime::App<std::shared_ptr<ReturnData>>
{
public:
    MyAppReturnSmartPointer(sabre::core::ResourceManager &rm);
    std::shared_ptr<ReturnData> run() override;
};