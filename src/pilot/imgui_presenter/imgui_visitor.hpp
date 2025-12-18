#pragma once

#include "../simulator/device_visitor.hpp"
#include <unordered_map>

namespace sabre::Pilot
{
    class ImGuiVisitor : public DeviceVisitor
    {
    private:
        std::unordered_map<std::string, bool> &_device_visibility;

    public:
        ImGuiVisitor(std::unordered_map<std::string, bool> &device_visibility);
        ~ImGuiVisitor() = default;
        void visit_mcu(class Mcu &mcu, const std::string &name) override;
    };
} // namespace sabre::Pilot