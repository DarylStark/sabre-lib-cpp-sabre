#include "simulator.hpp"
#include <iostream>

namespace sabre::pilot
{
    void Simulator::add_mcu(const std::string &name, const MCUConfig &config,
                            sabre::AppUniquePtr &&app)
    {
        SimulatorMCU mcu{.mcu = std::make_unique<MCU>(config, std::move(app))};
        if (_mcus.find(name) != _mcus.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("MCU with name '" + name +
                                     "' already exists");
        }
        _mcus[name] = std::move(mcu);
    }

    void Simulator::_thread_mcu_start(std::unique_ptr<MCU> &mcu)
    {
        while (true)
            mcu->start();
    }

    void Simulator::_start_mcus()
    {
        for (auto &sim_mcu : _mcus)
        {
            if (sim_mcu.second.thread == nullptr)
            {
                std::cout << "Starting MCU: " << sim_mcu.first << std::endl;
                sim_mcu.second.thread = std::make_unique<std::jthread>(
                    &Simulator::_thread_mcu_start, this,
                    std::ref(sim_mcu.second.mcu));
            }
        }
    }

    void Simulator::start()
    {
        _start_mcus();
    }
} // namespace sabre::pilot