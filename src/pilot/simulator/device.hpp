#pragma once

#include "device_visitor.hpp"
#include <functional>
#include <list>
#include <map>
#include <sabre/runtime/app.hpp>
#include <unordered_map>
#include <vector>

namespace sabre::impl::pilot
{
    class Device;

    enum class GPIOType
    {
        GENERIC,
        INPUT,
        OUTPUT
    };

    struct DeviceGPIO
    {
        uint32_t number;
        GPIOType type;
        uint32_t state = 0;
    };

    struct UartBuffers
    {
        std::string outputData = "";
        std::string input_buffer = "";
        std::string inputDataConsumed = "";
        size_t inputBufferMaxSize = 0;
    };

    struct DeviceConfig
    {
        size_t gpioCount = 0;
        size_t uartCount = 1;
    };

    enum class DeviceEventType
    {
        UART_DATA_SEND
    };

    class DeviceEventData
    {
    public:
        virtual ~DeviceEventData() = 0;
    };

    class UartEventData : public DeviceEventData
    {
    public:
        uint32_t uartNumber;
        char data;

        UartEventData(uint32_t uartNumber, char data);
    };

    struct DeviceEvent
    {
        DeviceEventType type;
        Device *device;
        std::unique_ptr<DeviceEventData> data;
    };

    using GPIOVector = std::vector<DeviceGPIO>;
    using UARTMap = std::map<uint32_t, UartBuffers>;
    using DeviceEventCallback = std::function<void(const DeviceEvent &)>;
    using EventCallbacks =
        std::unordered_multimap<DeviceEventType, DeviceEventCallback>;

    class Device
    {
    private:
        DeviceConfig _config;
        sabre::runtime::App::UniquePtr _app;
        GPIOVector _gpios;
        UARTMap _uartMap;
        EventCallbacks _eventCallback;

        void _raise_event(DeviceEventType type,
                          std::unique_ptr<DeviceEventData> data);

    public:
        Device(DeviceConfig config, sabre::runtime::App::UniquePtr &&app);

        // Device control
        void start();

        // Event control
        void register_event_callback(DeviceEventType type,
                                     const DeviceEventCallback &callback);

        // GPIO management
        DeviceGPIO &get_gpio(size_t index);
        void set_gpio_type(size_t index, GPIOType type);
        void reset_gpio(size_t index);
        void set_gpio_state(size_t index, uint32_t state);
        GPIOVector get_gpios(GPIOType type) const;

        // UART management
        bool initialize_uart(uint32_t uartNumber, size_t inputBufferSize);
        bool deinitialize_uart(uint32_t uartNumber);
        bool write_uart_data(uint32_t uartNumber, char data);
        std::string read_uart_data(uint32_t uartNumber, size_t maxBytes,
                                   uint32_t timeoutInMs);
        void add_to_input_uart_buffer(uint32_t uartNumber,
                                      const std::string &data);
        const UARTMap &get_uart_map() const;

        // Method for the Visitor pattern. The Visitor class will call the
        // appropriate visit_<device_type> method.
        virtual void accept(DeviceVisitor &visitor,
                            const std::string &name) = 0;
    };
} // namespace sabre::impl::pilot