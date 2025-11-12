#include "imgui_presenter/imgui_presenter.hpp"
#include "sabre/app/app.hpp"
#include "simulator/simulator.hpp"
#include <iostream>
#include <thread>

class MyApp : public sabre::App
{
private:
    sabre::UARTUniquePtr _uart0;
    std::ostream _uart0_out;
    uint32_t _timeout = 0;
    bool _stop = false;

public:
    MyApp(uint32_t timeout) : _timeout(timeout), _uart0_out(0) {}

    ~MyApp()
    {
        _stop = true;
        auto streambuf = _uart0_out.rdbuf();
        delete streambuf;
    }

    void start() override
    {
        auto streambuf =
            _factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 1024);
        _uart0_out.rdbuf(streambuf.get());
        _uart0_out << this << " - App starting!" << std::endl;
        _uart0_out << this << " - App started" << std::endl;

        while (!_stop)
        {
            _uart0_out << "Dit is text. " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(_timeout));
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

    MCUConfig config_mcu{.gpio_count = 32, .uart_count = 2};
    MCUConfig config_gps{.gpio_count = 2, .uart_count = 1};

    Simulator simulator;
    ImGuiPresenter presenter(simulator);

    simulator.add_mcu("ESP32-S3", config_mcu, std::make_unique<MyApp>(100));
    simulator.add_mcu("GPS", config_gps, std::make_unique<MyGpsApp>());
    simulator.start_mcu("ESP32-S3");
    simulator.start_mcu("GPS");

    presenter.start();

    return 0;
}