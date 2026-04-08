#include "queue.hpp"

namespace sabre
{
    namespace os
    {
        sabre::log::LogHelper &Queue::getLogHelper()
        {
            return _log_helper;
        }

        Queue::~Queue() {} // LCOV_EXCL_LINE
    } // namespace os
} // namespace sabre