#include "sabre/app/app.hpp"
#include "simulator.hpp"
#include <iostream>

class MyApp : public sabre::App
{
private:
    sabre::InputGPIOUniquePtr button_gpio;
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
        button_gpio = _factory->create_input_gpio(18);

        // Done!
        std::cout << this << " - App started" << std::endl;

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
            std::cout << character;
        }
    }
};

int main()
{
    using namespace sabre::pilot;

    MCUConfig config_mcu0{.gpio_count = 32};
    MCUConfig config_mcu1{.gpio_count = 24};

    Simulator simulator;
    simulator.add_mcu("mcu0", config_mcu0, std::make_unique<MyApp>(500, '!'));
    simulator.add_mcu("mcu1", config_mcu1, std::make_unique<MyApp>(175, '.'));
    simulator.start();

    return 0;
}