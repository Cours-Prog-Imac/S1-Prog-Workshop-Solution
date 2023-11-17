#include "Echanger les canaux.hpp"

void channels_swap(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}