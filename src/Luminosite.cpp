#include "Luminosite.hpp"

void luminosity(sil::Image& image, float luminosity)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::pow(color, glm::vec3{luminosity});
    }
}