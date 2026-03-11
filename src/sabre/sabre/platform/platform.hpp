#pragma once

#include "../types/types.hpp"
#include <memory>
#include <string>

namespace sabre::platform
{
    class Platform
    {
    public:
        using Ptr = Platform *;
        using SharedPtr = std::shared_ptr<Platform>;
        using UniquePtr = std::unique_ptr<Platform>;

    public:
        virtual ~Platform() = default;

        // Operations
        virtual void restart() = 0;

        // Platform statistics
        virtual std::string getApiVersion() const = 0;
        virtual std::string getPlatform() const = 0;
        virtual std::string getDeviceId() const = 0;

        // Platform statistics
        virtual sabre::types::MsTime getUptimeMs() const = 0;

        // Memory statistics
        virtual size_t getHeapCapacity() const = 0;
        virtual size_t getHeapAvailable() const = 0;

        // Flash
        virtual size_t getFlashCapacity() const = 0;
        virtual size_t getFlashAvailable() const = 0;

        // CPU statistics
        virtual uint16_t getCpuUsage() const = 0;

        // Chip temperature
        virtual int getTemperatureMilliC() const = 0;

        // Last reset reason
        virtual std::string getLastResetReason() const = 0;
    };
} // namespace sabre::platform