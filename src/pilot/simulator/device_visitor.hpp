#pragma once

#include <string>

namespace sabre::pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_mcu(class Mcu &mcu, const std::string &name) = 0;
    };
} // namespace sabre::pilot