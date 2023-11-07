#include "normalize_histogram.hpp"

struct Histogram {
    float min_luminosity;
    float max_luminosity;
};

Histogram compute_histogram(sil::Image const& image)
{
    Histogram histogram{1.f, 0.f}; // Init with values
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 const color    = image.pixel(x, y);
            float const     grey     = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
            histogram.min_luminosity = std::min(histogram.min_luminosity, grey);
            histogram.max_luminosity = std::max(histogram.max_luminosity, grey);
        }
    }
    return histogram;
}

void normalize_histogram(sil::Image& image)
{
    Histogram const histogram = compute_histogram(image);
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = (image.pixel(x, y) - histogram.min_luminosity) / (histogram.max_luminosity - histogram.min_luminosity);
        }
    }
}