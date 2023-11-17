#include "Rotation de 90.hpp"

sil::Image rotate_90_degrees(sil::Image const& image)
{
    sil::Image result{image.height(), image.width()};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = image.pixel(y, image.height() - 1 - x);
        }
    }
    return result;
}