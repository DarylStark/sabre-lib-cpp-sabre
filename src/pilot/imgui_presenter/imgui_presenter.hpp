#pragma once

#include "imgui_visitor.hpp"
#include <presenter.hpp>

namespace sabre::Pilot
{
    enum class ImGuiTheme
    {
        DARK,
        LIGHT,
        CLASSIC
    };

    class ImGuiPresenter : public Presenter
    {
    private:
        // Essential ImGui variables
        GLFWwindow *_window = nullptr;

        std::unordered_map<std::string, bool> _device_visibility;

        // Concrete visitor for devices
        ImGuiVisitor _imgui_visitor{_device_visibility};

        // Scaling variables
        float _scale = 1.0f;
        bool _auto_scale = false;

        // Window toggles
        bool _show_imgui_demo = false;
        bool _show_imgui_metrics = false;

        // Theming variables
        ImGuiTheme _current_theme = ImGuiTheme::DARK;

        // Scaling methods
        void _set_scale_to_auto();
        void _set_scale(float scale);
        void _zoom_in();
        void _zoom_out();

        // Event handeling
        void _handle_key_events();

        // Menu creation
        void _main_menu();
        void _main_menu_file();
        void _main_menu_view();
        void _main_menu_view_device_list();
        void _main_menu_view_scale();
        void _main_menu_view_theme();
        void _main_menu_debug();

        // Windows
        void _device(const std::string &name, SimulatorDevice &sim_device);
        void _device_windows();
        void _imgui_demo_window();
        void _imgui_metrics_window();

        // Essential ImGui setup and loop methods
        void _create_window();
        void _create_imgui_context();
        void _loop();
        void _destroy_window();

    public:
        ImGuiPresenter(Simulator &simulator);
        void start() override;
    };
} // namespace sabre::Pilot