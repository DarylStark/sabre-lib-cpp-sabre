#pragma once

#include "sabre_test_mocks/core.hpp"
#include <gtest/gtest.h>
#include <sabre/core/gpio_resource_manager.hpp>
#include <sabre/core/network_resource_manager.hpp>
#include <sabre/core/os_resource_manager.hpp>
#include <sabre/core/resource_manager.hpp>
#include <sabre/core/serial_resource_manager.hpp>
#include <sabre/core/time_resource_manager.hpp>

class GpioResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager _logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::GpioResourceManager _gpio_rm{_factory, 26, _logManager};
};

class SerialResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager _logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::SerialResourceManager _serial_rm{_factory, 3, _logManager};
};

class TimeResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager _logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::TimeResourceManager _time_rm{_factory, _logManager};
};

class NetworkResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager _logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::NetworkResourceManager _net_rm{_factory, _logManager};
};

class OsResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager _logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::OsResourceManager _os_rm{_factory, _logManager};
};

class DeviceResourceManagerTest : public ::testing::Test
{
protected:
    sabre::log::LogManager _logManager;
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::DeviceResourceManager _device_rm{_factory, _logManager};
};

class ResourceManagerTest : public ::testing::Test
{
protected:
    sabre::impl::sabre_test_mocks::StFactory _factory{false};
    sabre::core::ResourceManager _manager{_factory, {26, 3}};
};