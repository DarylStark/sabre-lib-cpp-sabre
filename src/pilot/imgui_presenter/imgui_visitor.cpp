#include "imgui_visitor.hpp"
#include <cstdint>
#include <imgui.h>
#include <string>

#include <simulator.hpp>
#include <sstream>

namespace sabre::pilot
{
    void ImGuiVisitor::visit_mcu(Mcu &mcu, SimulatorDevice &simulator_device)
    {
        std::stringstream title_stream;
        title_stream << "MCU Device Visitor for " << simulator_device.name;
        std::string title = title_stream.str();
        ImGui::Begin(title.c_str());

        ImGui::End();
    }
} // namespace sabre::pilot