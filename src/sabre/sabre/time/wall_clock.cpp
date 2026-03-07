#include "wall_clock.hpp"

namespace sabre::time
{
    sabre::log::LogHelper &WallClock::getLogHelper()
    {
        return _log_helper;
    }
} // namespace sabre::time