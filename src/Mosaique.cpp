#include "Mosaique.hpp"

sil::Image mosaic(sil::Image const& image)
{
    sil::Image result{image.width() * 5, image.height() * 5};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = image.pixel(
                x % image.width(),
                y % image.height()
            );
        }
    }
    return result;
}

static int flip_at_middle(int x, int middle)
{
    if (x >= middle)
        x = 2 * middle - x - 1;
    return x;
}

sil::Image mosaic_flip(sil::Image const& image)
{
    sil::Image result{image.width() * 5, image.height() * 5};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = image.pixel(
                flip_at_middle(x % (2 * image.width()), image.width()),
                flip_at_middle(y % (2 * image.height()), image.height())
            );
        }
    }
    return result;
}