#include "Glitch.hpp"
#include "random.hpp"

void glitch(sil::Image& image)
{
    int const nb_squares{100};

    for (int i{0}; i < nb_squares; ++i)
    {
        int const width{random_int(1, 30)};
        int const height{random_int(1, 10)};

        int const x1{random_int(0, image.width() - width)};
        int const x2{random_int(0, image.width() - width)};
        int const y1{random_int(0, image.height() - height)};
        int const y2{random_int(0, image.height() - height)};

        for (int x_offset{0}; x_offset < width; ++x_offset)
        {
            for (int y_offset{0}; y_offset < height; ++y_offset)
            {
                std::swap(
                    image.pixel(x1 + x_offset, y1 + y_offset),
                    image.pixel(x2 + x_offset, y2 + y_offset)
                );
            }
        }
    }
}