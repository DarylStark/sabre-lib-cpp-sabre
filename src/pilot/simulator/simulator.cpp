#include "simulator.hpp"

#include <iostream>
#include <sstream>

namespace sabre::pilot
{
    Simulator::Simulator() {}

    MCU *Simulator::add_mcu(const std::string &name, const MCUConfig &config,
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
        return _mcus[name].mcu.get();
    }

    void Simulator::_start_mcu(SimulatorMCU &sim_mcu)
    {
        if (sim_mcu.thread == nullptr)
        {
            std::clog << "Starting MCU in new thread..." << std::endl;
            sim_mcu.thread = std::make_unique<std::jthread>(
                &Simulator::_thread_mcu_start, this, std::ref(sim_mcu.mcu));
            sim_mcu.thread->detach();
        }
    }

    void Simulator::start_mcu(const std::string &name)
    {
        auto it = _mcus.find(name);
        if (it == _mcus.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("MCU with name '" + name + "' not found");
        }
        _start_mcu(it->second);
    }

    void Simulator::_thread_mcu_start(std::unique_ptr<MCU> &mcu)
    {
        while (true)
            mcu->start();
    }

    void Simulator::_start_all_mcus()
    {
        for (auto &sim_mcu : _mcus)
            _start_mcu(sim_mcu.second);
    }

    MCUList &Simulator::get_mcu_list()
    {
        return _mcus;
    }

} // namespace sabre::pilot