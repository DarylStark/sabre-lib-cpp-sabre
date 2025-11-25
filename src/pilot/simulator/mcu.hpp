#pragma once

#include "device.hpp"

namespace sabre::pilot
{
    class Mcu : public Device
    {
    public:
        Mcu(DeviceConfig config, sabre::AppUniquePtr &&app);
        void visit(DeviceVisitor &visitor) override;
    };
} // namespace sabre::pilot