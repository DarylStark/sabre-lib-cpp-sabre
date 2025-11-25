#pragma once

namespace sabre::pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_mcu(class Mcu &mcu) = 0;
    };
} // namespace sabre::pilot