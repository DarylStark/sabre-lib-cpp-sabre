#pragma once

#include <sabre/app/app.hpp>

namespace Sabre::Testing
{
    class TestApp : public Sabre::App
    {
    public:
        using Sabre::App::App;

        void start() override;
    };
} // namespace Sabre::Testing