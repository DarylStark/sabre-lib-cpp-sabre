#pragma once

#include <sabre/app/app.hpp>

namespace sabre::Testing
{
    class TestApp : public sabre::App
    {
    public:
        using sabre::App::App;

        void start() override;
    };
} // namespace sabre::Testing