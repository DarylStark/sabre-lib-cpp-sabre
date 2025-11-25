#include "device.hpp"
#include "../sabre_pilot/factory.hpp"
#include <iostream>

namespace sabre::pilot
{
    DeviceEventData::~DeviceEventData() {}

    UartEventData::UartEventData(uint32_t uart_number, char data)
        : uart_number(uart_number), data(data)
    {
    }

    Device::Device(DeviceConfig config, sabre::AppUniquePtr &&app)
        : _config(config), _app(std::move(app)), _gpios(config.gpio_count)
    {
        uint32_t gpio_index = 0;
        for (auto &gpio : _gpios)
            gpio.number = gpio_index++;
        asm("nop");
    }

    void Device::_raise_event(DeviceEventType type,
                              std::unique_ptr<DeviceEventData> data)
    {
        auto range = _event_callbacks.equal_range(type);
        for (auto it = range.first; it != range.second; ++it)
        {
            DeviceEventCallback callback = it->second;
            if (callback)
                callback({type, this, std::move(data)});
        }
    }

    void Device::start()
    {
        _app->set_factory(std::make_unique<Factory>(this));
        _app->start();
    }

    void Device::register_event_callback(DeviceEventType type,
                                         DeviceEventCallback callback)
    {
        _event_callbacks.emplace(type, callback);
    }

    DeviceGPIO &Device::get_gpio(size_t index)
    {
        if (index >= _gpios.size())
            throw std::out_of_range("GPIO index out of range");
        return _gpios[index];
    }

    void Device::set_gpio_type(size_t index, GPIOType type)
    {
        get_gpio(index).type = type;
    }

    void Device::reset_gpio(size_t index)
    {
        auto &gpio = get_gpio(index);
        gpio.type = GPIOType::GENERIC;
        gpio.state = 0;
    }

    void Device::set_gpio_state(size_t index, uint32_t state)
    {
        get_gpio(index).state = state;
        // TODO: Call ISR if this is a Input GPIO
    }

    GPIOVector Device::get_gpios(GPIOType type) const
    {
        GPIOVector gpios;
        std::copy_if(_gpios.begin(), _gpios.end(), std::back_inserter(gpios),
                     [&type](DeviceGPIO gpio) { return gpio.type == type; });
        return gpios;
    }

    bool Device::initialize_uart(uint32_t uart_number, size_t input_buffer_size)
    {
        if (uart_number >= _config.uart_count)
            return false;

        if (_uart_map.find(uart_number) != _uart_map.end())
            return false; // UART already initialized

        _uart_map[uart_number] =
            UartBuffers{.input_buffer_max_size = input_buffer_size};
        return true;
    }

    bool Device::deinitialize_uart(uint32_t uart_number)
    {
        auto it = _uart_map.find(uart_number);
        if (it == _uart_map.end())
            return false; // UART not initialized

        _uart_map.erase(it);
        return true;
    }

    bool Device::write_uart_data(uint32_t uart_number, char data)
    {
        auto it = _uart_map.find(uart_number);
        if (it == _uart_map.end())
            return false; // UART not initialized

        it->second.output_data.push_back(data);
        // TODO: only on flush.
        _raise_event(DeviceEventType::UART_DATA_SEND,
                     std::make_unique<UartEventData>(uart_number, data));

        return true;
    }

    std::string Device::read_uart_data(uint32_t uart_number, size_t max_bytes,
                                       uint32_t timeout_ms)
    {
        auto it = _uart_map.find(uart_number);
        if (it == _uart_map.end())
            return ""; // UART not initialized

        std::string &input_buffer = it->second.input_buffer;
        std::string result = input_buffer.substr(0, max_bytes);
        it->second.input_data_consumed += result;
        input_buffer.erase(0, result.size());
        return result;
    }

    void Device::add_to_input_uart_buffer(uint32_t uart_number,
                                          const std::string &data)
    {
        auto it = _uart_map.find(uart_number);
        if (it == _uart_map.end())
            return; // UART not initialized

        // Make sure the input buffer does not exceed max size
        size_t max_size = it->second.input_buffer_max_size;
        if (it->second.input_buffer.size() + data.size() > max_size)
        {
            size_t excess_size =
                (it->second.input_buffer.size() + data.size()) - max_size;
            std::string to_add = data.substr(excess_size);
            it->second.input_buffer += to_add;
        }
        else
        {
            it->second.input_buffer += data;
        }
    }

    const UARTMap &Device::get_uart_map() const
    {
        return _uart_map;
    }

    void Device::visit(DeviceVisitor &visitor)
    {
        visitor.visit_device(*this);
    }
} // namespace sabre::pilot
