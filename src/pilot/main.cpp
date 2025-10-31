#include "sabre/app/app.hpp"
#include "simulator.hpp"
#include <thread>

class MyApp : public sabre::App
{
private:
    sabre::InputGPIOUniquePtr _button_gpio_1;
    sabre::InputGPIOUniquePtr _button_gpio_2;
    sabre::InputGPIOUniquePtr _button_gpio_3;
    sabre::OutputGPIOUniquePtr _led_gpio;
    sabre::UARTUniquePtr _uart0;
    std::ostream _uart0_out;
    std::ostream _uart1_out;
    uint32_t _timeout = 0;
    char _character = '.';
    bool _stop = false;

public:
    MyApp(uint32_t timeout, char character)
        : _timeout(timeout), _character(character), _uart0_out(0), _uart1_out(0)
    {
    }

    ~MyApp()
    {
        _stop = true;
        auto streambuf = _uart0_out.rdbuf();
        delete streambuf;
    }

    void start() override
    {

        // _uart0_out.rdbuf(
        //     _factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 256)
        //         .release());

        _uart0 = _factory->create_uart_object(0, 115200, 1, 3, 768);
        _uart0->initialize();

        _uart0_out << this << " - App starting!" << std::endl;

        // Set up objects
        _button_gpio_1 = _factory->create_input_gpio(12);
        _button_gpio_2 = _factory->create_input_gpio(13);
        _button_gpio_3 = _factory->create_input_gpio(18);
        _led_gpio = _factory->create_output_gpio(2);

        // Done!
        _uart0_out << this << " - App started" << std::endl;
        uint32_t index = 0;

        while (!_stop)
        {
            if (_button_gpio_1->get_level())
                _uart0_out << _character << std::endl;
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

            // _uart1_out << "Hello from UART1!" << std::endl;

            std::string input = _uart0->read_bytes(768, 200);
            if (input != "")
                _uart1_out << "Read " << input.size()
                           << " bytes from UART0: " << input << std::endl;

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
    auto mcu = simulator.add_mcu("ESP32-S3", config_mcu0,
                                 std::make_unique<MyApp>(500, '!'));
    // simulator.add_mcu("Pico W", config_mcu1, std::make_unique<MyApp>(320,
    // '.')); simulator.add_mcu("STM32", config_mcu1,
    // std::make_unique<MyApp>(500, '.'));
    simulator.start_mcu("ESP32-S3");
    // simulator.start_mcu("Pico W");

    std::thread uart_adder(
        [&stop, mcu]()
        {
            uint32_t uart_number = 0;
            while (!stop)
            {
                std::string data =
                    "$GPRMC,044840.00,A,3401.21044,N,11824.67722,W,0.165,,"
                    "010621,,,D*60\n$GPVTG,,T,,M,0.165,N,0.306,K,D*21\n$GPGGA,"
                    "044840.00,3401.21044,N,11824.67722,W,2,07,1.34,29.5,M,-32."
                    "9,M,,0000*56\n$GPGSA,A,3,21,32,46,27,08,22,10,,,,,,3.07,1."
                    "34,2.76*0F\n$GPGSV,3,1,12,01,18,319,17,08,27,257,20,10,44,"
                    "068,33,18,00,142,*73\n$GPGSV,3,2,12,21,39,313,23,22,20,"
                    "296,14,23,16,089,,27,22,221,32*7A\n$GPGSV,3,3,12,31,28,"
                    "168,20,32,70,025,31,46,49,199,30,51,49,161,*7E\n$GPGLL,"
                    "3401.21044,N,11824.67722,W,044840.00,A,D*7F\n";
                mcu->add_to_input_uart_buffer(0, data);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        });

    simulator.start();
    stop = true;
    uart_adder.join();

    return 0;
}