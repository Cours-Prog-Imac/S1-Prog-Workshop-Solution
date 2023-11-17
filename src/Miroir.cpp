#include "Miroir.hpp"

void mirror(sil::Image& image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(
                image.pixel(x, y),
                image.pixel(image.width() - 1 - x, y)
            );
        }
    }
}