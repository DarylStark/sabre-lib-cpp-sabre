#include "device_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre
{
    namespace core
    {
        DeviceResourceManager::DeviceResourceManager(
            Factory &factory, sabre::log::LogManager &logManager)
            : _factory(factory), _logManager(logManager)
        {
        }

        void DeviceResourceManager::configureRgbPixelStrip(
            const std::string &identifier, sabre::hal::PinNumber pinNumber,
            sabre::devices::PixelIndex length)
        {
            auto it = _queues.find(identifier);
            if (it != _queues.end())
            {
                throw RgbPixelStripAlreadyConfiguredException(
                    "RgbPixelStrip " + identifier + " is already configured");
            }
            _queues[identifier] =
                _factory.createRgbPixelStrip(pinNumber, length);
            _queues[identifier]->getLogHelper().createLogger(
                _logManager, "RgbPixelStrip_" + identifier);
        }

        sabre::devices::RgbPixelStrip &DeviceResourceManager::getRgbPixelStrip(
            const std::string &identifier) const
        {
            auto it = _queues.find(identifier);
            if (it == _queues.end())
            {
                throw RgbPixelStripNotConfiguredException(
                    "RgbPixelStrip " + identifier + " is not configured yet.");
            }
            return *it->second;
        }
    } // namespace core
} // namespace sabre