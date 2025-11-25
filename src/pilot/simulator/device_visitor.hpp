#pragma once

namespace sabre::pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_device(class Device &device) = 0;
    };
} // namespace sabre::pilot