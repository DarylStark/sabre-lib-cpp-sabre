#include "time_resource_manager.hpp"

namespace sabre::core
{
    TimeResourceManager::TimeResourceManager(Factory &factory,
                                             sabre::log::LogManager &logManager)
        : _factory(factory), _logManager(logManager)
    {
    }

    sabre::time::WallClock &TimeResourceManager::getWallClock()
    {
        if (!_wallClock)
        {
            _wallClock = _factory.createWallClock();
            _wallClock->getLogHelper().createLogger(_logManager, "WallClock");
        }
        return *_wallClock;
    }

    void TimeResourceManager::configureNtpClient(const std::string &identifier,
                                                 const std::string &server)
    {
        auto it = _ntpClients.find(identifier);
        if (it != _ntpClients.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("NtpClient " + identifier +
                                     " is already configured");
        }
        _ntpClients[identifier] = _factory.createNtpClient(server);
        _ntpClients[identifier]->getLogHelper().createLogger(
            _logManager, "NtpClient_" + identifier);
    }

    sabre::time::NtpClient &
    TimeResourceManager::getNtpClient(const std::string &identifier) const
    {
        auto it = _ntpClients.find(identifier);
        if (it == _ntpClients.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("NtpClient " + identifier +
                                     " is not configured yet.");
        }
        return *it->second;
    }
} // namespace sabre::core