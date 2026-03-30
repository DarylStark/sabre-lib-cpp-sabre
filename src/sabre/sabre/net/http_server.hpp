#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

namespace sabre
{
    namespace net
    {
        enum class HttpStatus
        {
            OK = 200,
            Created = 201,
            NoContent = 204,
            BadRequest = 400,
            Unauthorized = 401,
            Forbidden = 403,
            NotFound = 404,
            MethodNotAllowed = 405,
            InternalServerError = 500,
            NotImplemented = 501
        };

        enum class HttpMethod
        {
            GET,
            POST,
            PUT,
            DELETE,
            PATCH,
            ANY
        };

        struct HttpRequest
        {
            std::string uri;
            HttpMethod method;
            std::unordered_map<std::string, std::string> headers;
            std::string body;
        };

        struct HttpResponse
        {
            HttpStatus statusCode = HttpStatus::OK;
            std::unordered_map<std::string, std::string> headers;
            std::string body;
        };

        using HttpServerPageHandler =
            std::function<void(const HttpRequest &, HttpResponse &)>;

        class HttpServer
        {
        public:
            using Ptr = HttpServer *;
            using SharedPtr = std::shared_ptr<HttpServer>;
            using UniquePtr = std::unique_ptr<HttpServer>;

        public:
            virtual void addRoute(HttpMethod method, const std::string &uri,
                                  HttpServerPageHandler handler) = 0;
            virtual void removeRoute(HttpMethod method,
                                     const std::string &uri) = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual ~HttpServer() = default;
        };
    } // namespace net
} // namespace sabre