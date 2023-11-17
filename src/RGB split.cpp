#include "RGB split.hpp"

void rgb_split(sil::Image& image)
{
    int const offset{30};

    sil::Image result{image.width(), image.height()};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = glm::vec3{
                image.pixel(std::max(x - offset, 0), y).r,
                image.pixel(x, y).g,
                image.pixel(std::min(x + offset, image.width() - 1), y).b,
            };
        }
    }

    image = result;
}