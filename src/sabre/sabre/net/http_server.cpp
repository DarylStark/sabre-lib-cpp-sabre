#include "http_server.hpp"

namespace sabre
{
    namespace net
    {
        sabre::log::LogHelper &HttpServer::getLogHelper()
        {
            return _log_helper;
        }
    } // namespace net
} // namespace sabre