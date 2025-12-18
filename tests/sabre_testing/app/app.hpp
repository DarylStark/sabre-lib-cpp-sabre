#pragma once

#include <sabre/core/app.hpp>
#include <sabre/core/factory.hpp>

namespace sabre::impl::sabre_testing
{
    class TestApp : public sabre::core::App
    {
    public:
        TestApp();
        TestApp(sabre::core::Factory::UniquePtr factory);
        void start() override;
    };
} // namespace sabre::impl::sabre_testing