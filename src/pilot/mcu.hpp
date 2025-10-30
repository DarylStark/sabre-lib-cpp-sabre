#pragma once

#include <map>
#include <sabre/app/app.hpp>
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

    struct MCUConfig
    {
        size_t gpio_count = 0;
        size_t uart_count = 1;
    };

    using GPIOVector = std::vector<MCUGPIO>;
    using UARTMap = std::map<uint32_t, std::string>;

    class MCU
    {
    private:
        MCUConfig _config;
        sabre::AppUniquePtr _app;
        GPIOVector _gpios;
        UARTMap _uart_map;

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

        // UART configuration
        bool initialize_uart(uint32_t uart_number);
        bool deinitialize_uart(uint32_t uart_number);
        bool write_uart_data(uint32_t uart_number, char data);
        const UARTMap &get_uart_map() const;
    };
} // namespace sabre::pilot