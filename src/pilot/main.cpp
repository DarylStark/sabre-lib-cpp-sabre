#include "imgui_presenter/imgui_presenter.hpp"
#include "sabre/app/app.hpp"
#include "simulator/device_connector.hpp"
#include "simulator/simulator.hpp"
#include <iostream>
#include <thread>

class MyApp : public sabre::App
{
private:
    sabre::UARTUniquePtr _uart0;
    bool _stop = false;

public:
    MyApp() {}

    void start() override
    {
        _uart0 = _factory->create_uart_object(0, 9600, 1, 2, 512);
        _uart0->initialize();

        while (true)
        {
            std::string received_data = _uart0->read_bytes(1, 16);
            for (const auto &b : received_data)
                _uart0->write_byte(b);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

class MyGpsApp : public sabre::App
{
public:
    void start() override
    {
        // Simulate GPS data output
        auto uart1 = _factory->create_uart_object(0, 9600, 0, 1, 512);
        uart1->initialize();
        while (true)
        {
            std::string nmea_sentence = "$GPGGA,123519,4807.038,N,01131.000,E,"
                                        "1,08,0.9,545.4,M,46.9,M,,*47\n";
            for (const char &p : nmea_sentence)
            {
                uart1->write_byte(p);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main()
{
    using namespace sabre::pilot;

    DeviceConfig config_mcu{.gpio_count = 32, .uart_count = 2};
    DeviceConfig config_gps{.gpio_count = 2, .uart_count = 1};

    Simulator simulator;
    ImGuiPresenter presenter(simulator);

    auto mcu =
        simulator.add_device("ESP32-S3", config_mcu, std::make_unique<MyApp>());
    auto gps =
        simulator.add_device("GPS", config_gps, std::make_unique<MyGpsApp>());
    UartConnector uart_connector(*gps, 0, *mcu, 0);

    simulator.start_device("ESP32-S3");
    simulator.start_device("GPS");

    presenter.start();

    return 0;
}