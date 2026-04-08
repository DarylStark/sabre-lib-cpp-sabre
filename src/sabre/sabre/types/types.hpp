#pragma once

#include <cstdint>

namespace sabre
{
    namespace types
    {
        using MsTime = uint64_t;

        struct Color
        {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            Color();
            Color(uint8_t red, uint8_t green, uint8_t blue);
            void clear();
            void applyBrightness(float brightness);

            bool operator==(const Color &other) const;
        };
    } // namespace types
} // namespace sabre