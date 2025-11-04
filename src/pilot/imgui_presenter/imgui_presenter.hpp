#pragma once

#include <presenter.hpp>

namespace sabre::pilot
{
    class ImGuiPresenter : public Presenter
    {
    private:
        float _scale = 1.0f;
        bool _auto_scale = false;
        GLFWwindow *_window = nullptr;

        // Window toggles
        bool _show_imgui_demo = false;
        bool _show_imgui_metrics = false;

        void _handle_key_events();
        void _set_scale_to_auto();
        void _set_scale(float scale);
        void _zoom_in();
        void _zoom_out();

        void _main_menu();
        void _main_menu_file();
        void _main_menu_view();
        void _main_menu_view_scale();
        void _main_menu_debug();

        void _mcu(const std::string &name, SimulatorMCU &sim_mcu);

        void _create_window();
        void _create_imgui_context();
        void _loop();
        void _destroy_window();
        void _mcu_windows();

        void _imgui_demo_window();
        void _imgui_metrics_window();

    public:
        ImGuiPresenter(Simulator &simulator);
        void start() override;
    };
} // namespace sabre::pilot