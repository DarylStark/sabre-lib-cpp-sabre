#include <sabre/platform/platform.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StPlatform : public sabre::platform::Platform
    {
    public:
        ~StPlatform();
        void restart();
        std::string getApiVersion() const;
        std::string getPlatform() const;
        std::string getDeviceId() const;
        sabre::types::MsTime getUptimeMs() const;
        size_t getHeapCapacity() const;
        size_t getHeapAvailable() const;
        size_t getFlashCapacity() const;
        size_t getFlashAvailable() const;
        uint16_t getCpuUsage() const;
        int getTemperatureMilliC() const;
        std::string getLastResetReason() const;
    };
} // namespace sabre::impl::sabre_test_mocks