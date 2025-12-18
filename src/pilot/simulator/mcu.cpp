#include "mcu.hpp"
#include "simulator.hpp"

namespace sabre::Pilot
{
    Mcu::Mcu(DeviceConfig config, sabre::core::App::UniquePtr &&app)
        : Device(std::move(config), std::move(app))
    {
    }

    void Mcu::accept(DeviceVisitor &visitor, const std::string &name)
    {
        visitor.visit_mcu(*this, name);
    }
} // namespace sabre::Pilot