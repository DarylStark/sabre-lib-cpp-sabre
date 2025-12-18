#pragma once

#include "device.hpp"
#include "simulator.hpp"
#include <string>

namespace sabre::Pilot
{
    class Mcu : public Device
    {
    public:
        Mcu(DeviceConfig config, sabre::AppUniquePtr &&app);
        void accept(DeviceVisitor &visitor, const std::string &name) override;
    };
} // namespace sabre::Pilot