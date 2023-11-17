#include "Ne garder que le vert.hpp"

void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}