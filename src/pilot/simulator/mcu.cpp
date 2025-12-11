#include "mcu.hpp"
#include "simulator.hpp"

namespace Sabre::Pilot
{
    Mcu::Mcu(DeviceConfig config, Sabre::AppUniquePtr &&app)
        : Device(std::move(config), std::move(app))
    {
    }

    void Mcu::accept(DeviceVisitor &visitor, const std::string &name)
    {
        visitor.visit_mcu(*this, name);
    }
} // namespace Sabre::Pilot