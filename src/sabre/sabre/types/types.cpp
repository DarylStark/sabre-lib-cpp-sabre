#include "types.hpp"

namespace sabre
{
    namespace types
    {
        Color::Color() {}

        Color::Color(uint8_t red, uint8_t green, uint8_t blue)
        {
            this->red = red;
            this->green = green;
            this->blue = blue;
        }

        void Color::clear()
        {
            red = 0;
            green = 0;
            blue = 0;
        }

        void Color::applyBrightness(float brightness)
        {
            red *= brightness;
            green *= brightness;
            blue *= brightness;
        }

        bool Color::operator==(const Color &other) const
        {
            return other.red == red && other.green == green &&
                   other.blue == blue;
        }
    } // namespace types
} // namespace sabre