#pragma once

#include "sabre/core/gpio_resource_manager.hpp"
#include "sabre_test_mocks/core.hpp"
#include <gtest/gtest.h>

class SabreGpioResourceManagerTest : public ::testing::Test
{
protected:
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::GpioResourceManager _manager{_factory, 26};
};