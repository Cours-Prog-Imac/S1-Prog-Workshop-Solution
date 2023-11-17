#include "Noir et Blanc.hpp"

void black_and_white(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float const grey = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
        color            = glm::vec3{grey, grey, grey};
    }
}