#pragma once

#include "../log/logging.hpp"
#include "../types/types.hpp"
#include <memory>

namespace sabre
{
    namespace devices
    {
        using PixelIndex = uint16_t;

        class RgbPixelStrip
        {
        public:
            using Ptr = RgbPixelStrip *;
            using UniquePtr = std::unique_ptr<RgbPixelStrip>;
            using SharedPtr = std::shared_ptr<RgbPixelStrip>;

        private:
            float _brightness;
            PixelIndex _length;
            sabre::log::LogHelper _log_helper;

            void _raiseOnExceedingLength(PixelIndex index) const;

            virtual void _setPixel(PixelIndex pixel,
                                   const sabre::types::Color &color) = 0;

        public:
            RgbPixelStrip(PixelIndex length);
            virtual ~RgbPixelStrip();

            sabre::log::LogHelper &getLogHelper();
            void setPixel(PixelIndex index, const sabre::types::Color &color);
            PixelIndex getLength() const;
            void clearPixel(PixelIndex index);
            void setAll(const sabre::types::Color &color);
            void clear();

            virtual void show() = 0;
        };
    } // namespace devices
} // namespace sabre