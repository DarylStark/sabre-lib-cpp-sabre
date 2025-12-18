#pragma once

#include <string>

namespace sabre::Pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_mcu(class Mcu &mcu, const std::string &name) = 0;
    };
} // namespace sabre::Pilot