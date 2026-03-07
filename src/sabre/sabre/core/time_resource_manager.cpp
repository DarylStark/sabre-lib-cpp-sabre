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
        }
        return *_wallClock;
    }
} // namespace sabre::core