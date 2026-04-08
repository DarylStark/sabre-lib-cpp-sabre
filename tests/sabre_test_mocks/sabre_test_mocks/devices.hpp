#pragma once

#include <sabre/devices/rgb_led_strip.hpp>
#include <sabre/hal/gpio.hpp>

namespace sabre::impl::sabre_test_mocks
{
    class StRgbPixelStrip : public sabre::devices::RgbPixelStrip
    {
    private:
        std::unique_ptr<sabre::types::Color[]> _buffer;

    public:
        StRgbPixelStrip(sabre::hal::PinNumber dataPin,
                        sabre::devices::PixelIndex length);
        void _setPixel(sabre::devices::PixelIndex pixel,
                       const sabre::types::Color &color) override;
        void show() override;

        // Non-overrides
        const sabre::types::Color &
        getPixel(sabre::devices::PixelIndex index) const;
    };
} // namespace sabre::impl::sabre_test_mocks