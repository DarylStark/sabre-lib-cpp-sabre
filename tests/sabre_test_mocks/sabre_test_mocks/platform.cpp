#include "platform.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StPlatform::~StPlatform() {}

    void StPlatform::restart() {}

    std::string StPlatform::getApiVersion() const
    {
        return "1.0.0";
    }

    std::string StPlatform::getPlatform() const
    {
        return "Sabre Test Mocks";
    }

    std::string StPlatform::getDeviceId() const
    {
        return "DeviceID";
    }

    sabre::types::MsTime StPlatform::getUptimeMs() const
    {
        return 0;
    }

    size_t StPlatform::getHeapCapacity() const
    {
        return 0;
    }

    size_t StPlatform::getHeapAvailable() const
    {
        return 0;
    }

    size_t StPlatform::getFlashCapacity() const
    {
        return 0;
    }

    size_t StPlatform::getFlashAvailable() const
    {
        return 0;
    }

    uint16_t StPlatform::getCpuUsage() const
    {
        return 0;
    }

    int StPlatform::getTemperatureMilliC() const
    {
        return 0;
    }

    std::string StPlatform::getLastResetReason() const
    {
        return "";
    }
} // namespace sabre::impl::sabre_test_mocks