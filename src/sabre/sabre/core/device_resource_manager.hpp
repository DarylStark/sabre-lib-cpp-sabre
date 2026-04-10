#pragma once

#include "../devices/rgb_pixel_strip.hpp"
#include "factory.hpp"
#include <unordered_map>

namespace sabre::core
{
    class DeviceResourceManager
    {
    private:
        Factory &_factory;
        sabre::log::LogManager &_logManager;

        std::unordered_map<std::string,
                           sabre::devices::RgbPixelStrip::UniquePtr>
            _queues;

    public:
        DeviceResourceManager(Factory &factory,
                              sabre::log::LogManager &logManager);
        void configureRgbPixelStrip(const std::string &identifier,
                                    sabre::hal::PinNumber pinNumber,
                                    sabre::devices::PixelIndex length);
        sabre::devices::RgbPixelStrip &
        getRgbPixelStrip(const std::string &identifier) const;
    };
} // namespace sabre::core