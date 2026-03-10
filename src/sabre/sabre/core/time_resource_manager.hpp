#pragma once

#include "../time/ntp.hpp"
#include "../time/wall_clock.hpp"
#include "factory.hpp"
#include <unordered_map>

namespace sabre::core
{
    class TimeResourceManager
    {
    private:
        Factory &_factory;
        sabre::log::LogManager &_logManager;

        // Local lazy resources
        sabre::time::WallClock::UniquePtr _wallClock;
        std::unordered_map<std::string, sabre::time::NtpClient::UniquePtr>
            _ntpClients;

    public:
        TimeResourceManager(Factory &factory,
                            sabre::log::LogManager &logManager);
        // Lazy resources
        sabre::time::WallClock &getWallClock();
        void configureNtpClient(const std::string &identifier,
                                const std::string &server);
        sabre::time::NtpClient &
        getNtpClient(const std::string &identifier) const;
    };
} // namespace sabre::core