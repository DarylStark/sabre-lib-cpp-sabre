#pragma once

#include "../time/wall_clock.hpp"
#include "factory.hpp"

namespace sabre::core
{
    class TimeResourceManager
    {
    private:
        Factory &_factory;
        sabre::log::LogManager &_logManager;

        // Local lazy resources
        sabre::time::WallClock::UniquePtr _wallClock;

    public:
        TimeResourceManager(Factory &factory,
                            sabre::log::LogManager &logManager);
        // Lazy resources
        sabre::time::WallClock &getWallClock();
    };
} // namespace sabre::core