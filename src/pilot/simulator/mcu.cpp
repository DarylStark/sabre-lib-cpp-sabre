#include "mcu.hpp"
#include "simulator.hpp"

namespace sabre::pilot
{
    Mcu::Mcu(DeviceConfig config, sabre::AppUniquePtr &&app)
        : Device(std::move(config), std::move(app))
    {
    }

    void Mcu::accept(DeviceVisitor &visitor, const std::string &name)
    {
        visitor.visit_mcu(*this, name);
    }
} // namespace sabre::pilot