#pragma once

#include <presenter.hpp>

namespace sabre::pilot
{
    class ImGuiPresenter : public Presenter
    {
    private:
        float _ui_scale = 1.0f;
        bool _auto_ui_scale = false;
        GLFWwindow *_window = nullptr;
        bool _show_imgui_demo = false;
        bool _show_imgui_metrics = false;

        void _ui_handle_key_events();
        void _ui_set_scale_to_auto();
        void _ui_set_scale(float scale);
        void _ui_zoom_in();
        void _ui_zoom_out();

        void _ui_main_menu();
        void _ui_main_menu_file();
        void _ui_main_menu_view();
        void _ui_main_menu_view_scale();
        void _ui_main_menu_debug();

        void _ui_mcu(const std::string &name, SimulatorMCU &sim_mcu);

        void _ui_create_window();
        void _ui_create_imgui_context();
        void _ui_loop();
        void _ui_destroy_window();
        void _ui_mcu_windows();

        void _ui_imgui_demo_window();
        void _ui_imgui_metrics_window();

    public:
        ImGuiPresenter(Simulator &simulator);
        void start() override;
    };
} // namespace sabre::pilot