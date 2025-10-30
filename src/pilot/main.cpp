#include "sabre/app/app.hpp"
#include "simulator.hpp"

class MyApp : public sabre::App
{
private:
    sabre::InputGPIOUniquePtr _button_gpio_1;
    sabre::InputGPIOUniquePtr _button_gpio_2;
    sabre::InputGPIOUniquePtr _button_gpio_3;
    sabre::OutputGPIOUniquePtr _led_gpio;
    std::ostream _uart0_out;
    std::ostream _uart1_out;
    uint32_t _timeout = 0;
    char _character = '.';

public:
    MyApp(uint32_t timeout, char character)
        : _timeout(timeout), _character(character), _uart0_out(0), _uart1_out(0)
    {
    }

    ~MyApp()
    {
        auto streambuf = _uart0_out.rdbuf();
        delete streambuf;
    }

    void start() override
    {

        _uart0_out.rdbuf(
            _factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 256)
                .release());

        _uart0_out << this << " - App starting!" << std::endl;

        // Set up objects
        _button_gpio_1 = _factory->create_input_gpio(12);
        _button_gpio_2 = _factory->create_input_gpio(13);
        _button_gpio_3 = _factory->create_input_gpio(18);
        _led_gpio = _factory->create_output_gpio(2);

        // Done!
        _uart0_out << this << " - App started" << std::endl;
        uint32_t index = 0;

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(_timeout));
            if (_button_gpio_1->get_level())
                _uart0_out << _character << std::flush;
            if (_button_gpio_2->get_level())
                _led_gpio->set_level(index++ % 2 == 0);
            if (_button_gpio_3->get_level())
            {
                if (!_uart1_out.rdbuf())
                {
                    auto uart1_buf = _factory->create_uart_output_stream_buffer(
                        1, 9600, 4, 5, 128);
                    _uart1_out.rdbuf(uart1_buf.release());
                }
            }

            _uart1_out << "Hello from UART1!" << std::endl;
        }
    }
};

int main()
{
    using namespace sabre::pilot;

    MCUConfig config_mcu0{.gpio_count = 32, .uart_count = 2};
    MCUConfig config_mcu1{.gpio_count = 24, .uart_count = 2};

    Simulator simulator;
    simulator.add_mcu("ESP32-S3", config_mcu0,
                      std::make_unique<MyApp>(250, '!'));
    simulator.add_mcu("Pico W", config_mcu1, std::make_unique<MyApp>(320, '.'));
    simulator.add_mcu("STM32", config_mcu1, std::make_unique<MyApp>(500, '.'));
    simulator.start_mcu("ESP32-S3");
    simulator.start_mcu("Pico W");
    simulator.start();

    return 0;
}