#pragma once

#include <sabre/app/app.hpp>
#include <variant>
#include <vector>

namespace sabre::pilot
{
    enum class GPIOType
    {
        GENERIC,
        INPUT,
        OUTPUT
    };
    struct MCUGPIO
    {
        uint32_t number;
        GPIOType type;
        uint32_t state = 0;
    };
    using GPIOVector = std::vector<MCUGPIO>;

    struct MCUConfig
    {
        size_t gpio_count;
    };

    class MCU
    {
    private:
        MCUConfig _config;
        sabre::AppUniquePtr _app;
        GPIOVector _gpios;

    public:
        MCU(MCUConfig config, sabre::AppUniquePtr &&app);

        // MCU control
        void start();

        // GPIO configuration
        MCUGPIO &get_gpio(size_t index);
        void set_gpio_type(size_t index, GPIOType type);
        void reset_gpio(size_t index);
        void set_gpio_state(size_t index, uint32_t state);
        GPIOVector get_gpios(GPIOType type) const;
    };
} // namespace sabre::pilot