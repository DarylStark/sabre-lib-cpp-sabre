#pragma once

#include "mcu.hpp"
#include <GLFW/glfw3.h>
#include <map>
#include <thread>
#include <utility>

namespace sabre::pilot
{
    struct SimulatorMCU
    {
        std::unique_ptr<MCU> mcu;
        std::unique_ptr<std::jthread> thread = nullptr;
        bool show = true;
    };

    class Simulator
    {
    private:
        std::map<std::string, SimulatorMCU> _mcus;

        void _thread_mcu_start(std::unique_ptr<MCU> &mcu);
        void _start_mcu(SimulatorMCU &sim_mcu);
        void _start_all_mcus();

        // UI members
        float _ui_scale = 1.0f;
        bool _auto_ui_scale = false;
        GLFWwindow *_window = nullptr;
        bool _show_debug = false;

        void _ui_handle_key_events();
        void _ui_setup_menubar();
        void _ui_set_scale_to_auto();
        void _ui_set_scale(float scale);
        void _ui_zoom_in();
        void _ui_zoom_out();

        void _ui_mcu(const std::string &name, SimulatorMCU &sim_mcu);

        void _ui_create_window();
        void _ui_create_imgui_context();
        void _ui_loop();
        void _ui_destroy_window();

        void _ui_debug_window();
        void _ui_mcu_windows();

    public:
        MCU *add_mcu(const std::string &name, const MCUConfig &config,
                     sabre::AppUniquePtr &&app);
        void start_mcu(const std::string &name);

        void start();

        // GUI methods
        void start_gui();
    };
} // namespace sabre::pilot