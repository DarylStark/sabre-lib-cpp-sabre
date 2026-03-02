#pragma once

#include "sabre/core/gpio_resource_manager.hpp"
#include "sabre/core/resource_manager.hpp"
#include "sabre/core/serial_resource_manager.hpp"
#include "sabre_test_mocks/core.hpp"
#include <gtest/gtest.h>

class GpioResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::GpioResourceManager _gpio_rm{_factory, 26, logManager};
};

class SerialResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::SerialResourceManager _serial_rm{_factory, 3, logManager};
};

class ResourceManagerTest : public ::testing::Test
{
protected:
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::ResourceManager _manager{_factory, 26, 3};
};