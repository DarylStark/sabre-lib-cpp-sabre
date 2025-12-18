#pragma once

#include "device.hpp"
#include <GLFW/glfw3.h>
#include <map>
#include <thread>
#include <utility>

namespace sabre::Pilot
{
    struct SimulatorDevice
    {
        std::string name;
        std::shared_ptr<Device> device;
        std::unique_ptr<std::jthread> thread = nullptr;
    };

    using DeviceList = std::map<std::string, SimulatorDevice>;

    class Simulator
    {
    private:
        DeviceList _devices;

        void _thread_device_start(std::shared_ptr<Device> device);
        void _start_device(SimulatorDevice &sim_device);
        void _start_all_devices();

    public:
        Simulator();

        Device *add_mcu(const std::string &name, const DeviceConfig &config,
                        sabre::AppUniquePtr &&app);
        void start_device(const std::string &name);

        DeviceList &get_device_list();
    };
} // namespace sabre::Pilot