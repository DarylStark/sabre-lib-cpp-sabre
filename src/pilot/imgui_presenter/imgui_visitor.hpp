#pragma once

#include "../simulator/device_visitor.hpp"

namespace sabre::pilot
{
    class ImGuiVisitor : public DeviceVisitor
    {
    public:
        ~ImGuiVisitor() = default;
        void visit_mcu(class Mcu &mcu, const std::string &name) override;
    };
} // namespace sabre::pilot