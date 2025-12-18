#pragma once

#include <sabre/core/app.hpp>
#include <sabre/factory.hpp>

namespace sabre::Testing
{
    class TestApp : public sabre::core::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::Testing