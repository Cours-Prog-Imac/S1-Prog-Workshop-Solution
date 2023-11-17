#include "Tramage.hpp"

float greyscale(glm::vec3 const& color)
{
    return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
}

void ordered_dithering(sil::Image& image)
{
    std::vector<std::vector<float>> const bayer_matrix = {
        {-0.5000f, +0.0000f, -0.3750f, +0.1250f},
        {+0.2500f, -0.2500f, +0.3750f, -0.1250f},
        {-0.3125f, +0.1875f, -0.4375f, +0.0625f},
        {+0.4375f, -0.0625f, +0.3125f, -0.1875f},
    };

    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            float const bayer_value{bayer_matrix[x % bayer_matrix.size()][y % bayer_matrix.size()]};
            float const value{greyscale(image.pixel(x, y)) + bayer_value};
            image.pixel(x, y) = value < 0.5f
                                    ? glm::vec3{0.f}
                                    : glm::vec3{1.f};
        }
    }
}