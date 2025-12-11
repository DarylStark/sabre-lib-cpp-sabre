#pragma once

#include "device.hpp"
#include "simulator.hpp"
#include <string>

namespace Sabre::Pilot
{
    class Mcu : public Device
    {
    public:
        Mcu(DeviceConfig config, Sabre::AppUniquePtr &&app);
        void accept(DeviceVisitor &visitor, const std::string &name) override;
    };
} // namespace Sabre::Pilot