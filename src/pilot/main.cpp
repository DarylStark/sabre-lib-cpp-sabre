#include "sabre/app/app.hpp"
#include "simulator.hpp"
#include <iostream>

class MyApp : public sabre::App
{
private:
    sabre::InputGPIOUniquePtr button_gpio_1;
    sabre::InputGPIOUniquePtr button_gpio_2;
    sabre::InputGPIOUniquePtr button_gpio_3;
    sabre::OutputGPIOUniquePtr led_gpio;
    uint32_t timeout = 0;
    char character = '.';

public:
    MyApp(uint32_t timeout, char character)
        : timeout(timeout), character(character)
    {
    }

    void start() override
    {
        std::cout << this << " - App starting!" << std::endl;

        // Set up objects
        button_gpio_1 = _factory->create_input_gpio(12);
        button_gpio_2 = _factory->create_input_gpio(13);
        button_gpio_3 = _factory->create_input_gpio(18);
        led_gpio = _factory->create_output_gpio(2);

        // Done!
        std::cout << this << " - App started" << std::endl;
        uint32_t index = 0;

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
            if (button_gpio_1->get_level())
                std::cout << character << std::flush;
            if (button_gpio_2->get_level())
                led_gpio->set_level(index++ % 2 == 0);
        }
    }
};

int main()
{
    using namespace sabre::pilot;

    MCUConfig config_mcu0{.gpio_count = 32};
    MCUConfig config_mcu1{.gpio_count = 24};

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