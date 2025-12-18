#pragma once

#include <string>

namespace sabre::impl::pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_mcu(class Mcu &mcu, const std::string &name) = 0;
    };
} // namespace sabre::impl::pilot