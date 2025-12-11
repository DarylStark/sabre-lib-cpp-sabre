#pragma once

#include <string>

namespace Sabre::Pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_mcu(class Mcu &mcu, const std::string &name) = 0;
    };
} // namespace Sabre::Pilot