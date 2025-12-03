#include "mcu.hpp"
#include "simulator.hpp"

namespace sabre::pilot
{
    Mcu::Mcu(DeviceConfig config, sabre::AppUniquePtr &&app)
        : Device(std::move(config), std::move(app))
    {
    }

    void Mcu::visit(DeviceVisitor &visitor, SimulatorDevice &simulator_device)
    {
        visitor.visit_mcu(*this, simulator_device);
    }
} // namespace sabre::pilot