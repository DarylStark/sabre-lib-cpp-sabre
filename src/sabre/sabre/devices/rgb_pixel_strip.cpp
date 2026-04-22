#include "rgb_pixel_strip.hpp"
#include "../core/exceptions.hpp"

namespace sabre
{
    namespace devices
    {
        RgbPixelStrip::RgbPixelStrip(PixelIndex length)
            : _brightness(0), _length(length)
        {
            if (_length == 0)
            {
                throw sabre::core::RgbSizeTooSmallException(
                    "RgbPixelStrip should be 1 LED at the least.");
            }
        }

        RgbPixelStrip::~RgbPixelStrip() {} // LCOV_EXCL_LINE

        sabre::log::LogHelper &RgbPixelStrip::getLogHelper()
        {
            return _log_helper;
        }

        void RgbPixelStrip::_raiseOnExceedingLength(PixelIndex index) const
        {
            if (index >= _length)
            {
                throw sabre::core::RgbIndexTooHighException(
                    "Index" + std::to_string(index) +
                    " too big (max: " + std::to_string(_length - 1) + ").");
            }
        }

        void RgbPixelStrip::setPixel(PixelIndex index,
                                     const sabre::types::Color &color)
        {
            _raiseOnExceedingLength(index);
            _setPixel(index, color);
        }

        PixelIndex RgbPixelStrip::getLength() const
        {
            return _length;
        }

        void RgbPixelStrip::clearPixel(PixelIndex index)
        {
            _raiseOnExceedingLength(index);
            _setPixel(index, sabre::types::Color());
        }

        void RgbPixelStrip::setAll(const sabre::types::Color &color)
        {
            for (PixelIndex idx = 0; idx < _length; idx++)
            {
                _setPixel(idx, color);
            }
        }

        void RgbPixelStrip::clear()
        {
            setAll(sabre::types::Color());
        }
    } // namespace devices
} // namespace sabre