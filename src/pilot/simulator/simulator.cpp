#include "simulator.hpp"

#include "mcu.hpp"
#include <iostream>
#include <sstream>

namespace sabre::Pilot
{
    Simulator::Simulator() {}

    Device *Simulator::add_mcu(const std::string &name,
                               const DeviceConfig &config,
                               sabre::AppUniquePtr &&app)
    {
        SimulatorDevice device{
            .name = name,
            .device = std::make_shared<Mcu>(config, std::move(app))};
        if (_devices.find(name) != _devices.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("Device with name '" + name +
                                     "' already exists");
        }
        _devices[name] = std::move(device);
        return _devices[name].device.get();
    }

    void Simulator::_start_device(SimulatorDevice &sim_device)
    {
        if (sim_device.thread == nullptr)
        {
            std::clog << "Starting device in new thread..." << std::endl;
            sim_device.thread = std::make_unique<std::jthread>(
                &Simulator::_thread_device_start, this, sim_device.device);
            sim_device.thread->detach();
        }
    }

    void Simulator::start_device(const std::string &name)
    {
        auto it = _devices.find(name);
        if (it == _devices.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("Device with name '" + name +
                                     "' not found");
        }
        _start_device(it->second);
    }

    void Simulator::_thread_device_start(std::shared_ptr<Device> device)
    {
        while (true)
            device->start();
    }

    void Simulator::_start_all_devices()
    {
        for (auto &sim_device : _devices)
            _start_device(sim_device.second);
    }

    DeviceList &Simulator::get_device_list()
    {
        return _devices;
    }

} // namespace sabre::Pilot