#pragma once

namespace sabre::pilot
{
    class DeviceVisitor
    {
    public:
        virtual ~DeviceVisitor() = default;
        virtual void visit_mcu(class Mcu &mcu,
                               class SimulatorDevice &simulator_device) = 0;
    };
} // namespace sabre::pilot