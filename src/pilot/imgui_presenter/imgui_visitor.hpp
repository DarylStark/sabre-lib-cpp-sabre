#pragma once

#include "../simulator/device_visitor.hpp"

namespace sabre::pilot
{
    class ImGuiVisitor : public DeviceVisitor
    {
    public:
        ~ImGuiVisitor() = default;
        void visit_mcu(class Mcu &mcu,
                       class SimulatorDevice &simulator_device) override;
    };
} // namespace sabre::pilot