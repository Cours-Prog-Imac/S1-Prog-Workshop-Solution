#include "Negatif.hpp"

void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = 1.f - color;
    }
}