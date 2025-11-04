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

int main()
{
    using namespace sabre::pilot;

    MCUConfig config_mcu0{.gpio_count = 32, .uart_count = 2};
    MCUConfig config_mcu1{.gpio_count = 24, .uart_count = 2};
    bool stop = false;

    Simulator simulator;
    ImGuiPresenter presenter(simulator);

    simulator.add_mcu("ESP32-S3", config_mcu0, std::make_unique<MyApp>(100));
    simulator.start_mcu("ESP32-S3");

    stop = true;

    presenter.start();

    return 0;
}