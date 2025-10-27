#include "mcu.hpp"
#include "sabre/app/app.hpp"
#include <iostream>

class MyApp : public sabre::App
{
private:
    sabre::InputGPIOUniquePtr button_gpio;

public:
    void start() override
    {
        std::cout << "App starting!" << std::endl;

        // Set up objects
        button_gpio = _factory->create_input_gpio(18);

        // Done!
        std::cout << "App started" << std::endl;
    }
};

int main()
{
    using namespace sabre::pilot;

    MCUConfig config_mcu0{.gpio_count = 32};
    MCU mcu0(config_mcu0, std::make_unique<MyApp>());

    MCUConfig config_mcu1{.gpio_count = 22};
    MCU mcu1(config_mcu1, std::make_unique<MyApp>());

    mcu0.start();
    mcu1.start();

    return 0;
}