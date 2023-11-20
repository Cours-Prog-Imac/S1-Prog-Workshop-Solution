#include "RGB split.hpp"

// If the (x, y) coordinates are invalid, returns black instead of returning the pixel of the image.
glm::vec3 sample_with_check(sil::Image const& image, int x, int y)
{
    if (x < 0 || x >= image.width() ||
        y < 0 || y >= image.height())
    {
        return glm::vec3{0.f};
    }
    return image.pixel(x, y);
}

void rgb_split(sil::Image& image)
{
    int const offset{30};

    sil::Image result{image.width(), image.height()};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = glm::vec3{
                sample_with_check(image, x - offset, y).r,
                image.pixel(x, y).g,
                sample_with_check(image, x + offset, y).b,
            };
        }
    }

    image = result;
}