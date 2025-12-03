#pragma once

#include "device.hpp"
#include "simulator.hpp"

namespace sabre::pilot
{
    class Mcu : public Device
    {
    public:
        Mcu(DeviceConfig config, sabre::AppUniquePtr &&app);
        void visit(DeviceVisitor &visitor,
                   SimulatorDevice &simulator_device) override;
    };
} // namespace sabre::pilot