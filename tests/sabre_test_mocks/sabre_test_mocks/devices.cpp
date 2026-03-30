#include "devices.hpp"

namespace sabre::impl::sabre_test_mocks
{
    StRgbPixelStrip::StRgbPixelStrip(sabre::hal::PinNumber dataPin,
                                     sabre::devices::PixelIndex length)
        : sabre::devices::RgbPixelStrip(length)
    {
        _buffer = std::make_unique<sabre::types::Color[]>(length);
    }

    void StRgbPixelStrip::_setPixel(sabre::devices::PixelIndex pixel,
                                    const sabre::types::Color &color)
    {
        _buffer[pixel] = color;
    }

    void StRgbPixelStrip::show() {}

    const sabre::types::Color &
    StRgbPixelStrip::getPixel(sabre::devices::PixelIndex index) const
    {
        return _buffer[index];
    }
} // namespace sabre::impl::sabre_test_mocks