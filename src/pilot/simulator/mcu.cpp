#include "mcu.hpp"

namespace sabre::pilot
{
    Mcu::Mcu(DeviceConfig config, sabre::AppUniquePtr &&app)
        : Device(std::move(config), std::move(app))
    {
    }
    void Mcu::visit(DeviceVisitor &visitor)
    {
        visitor.visit_mcu(*this);
    }
} // namespace sabre::pilot