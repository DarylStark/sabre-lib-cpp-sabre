#pragma once

#include "mcu.hpp"
#include <map>
#include <thread>
#include <utility>

namespace sabre::pilot
{
    struct SimulatorMCU
    {
        std::unique_ptr<MCU> mcu;
        std::unique_ptr<std::jthread> thread = nullptr;
    };

    class Simulator
    {
    private:
        std::map<std::string, SimulatorMCU> _mcus;

        void _thread_mcu_start(std::unique_ptr<MCU> &mcu);
        void _start_mcus();

    public:
        void add_mcu(const std::string &name, const MCUConfig &config,
                     sabre::AppUniquePtr &&app);
        void start();
    };
} // namespace sabre::pilot