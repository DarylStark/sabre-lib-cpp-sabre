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

    using MCUList = std::map<std::string, SimulatorMCU>;

    class Simulator
    {
    private:
        MCUList _mcus;

        void _thread_mcu_start(std::unique_ptr<MCU> &mcu);
        void _start_mcu(SimulatorMCU &sim_mcu);
        void _start_all_mcus();

    public:
        Simulator();

        MCU *add_mcu(const std::string &name, const MCUConfig &config,
                     sabre::AppUniquePtr &&app);
        void start_mcu(const std::string &name);

        MCUList &get_mcu_list();
    };
} // namespace sabre::pilot