#include "Image bruitee.hpp"
#include "random.hpp"

void noisy_image(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        if (random_float(0.f, 1.f) < 0.7f) // Keep 70% of the pixels intact
            continue;
        color = glm::vec3{
            random_float(0.f, 1.f),
            random_float(0.f, 1.f),
            random_float(0.f, 1.f),
        };
    }
}