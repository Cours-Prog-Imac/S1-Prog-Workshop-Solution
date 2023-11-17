#include "Vortex.hpp"
#include <algorithm>
#include "glm/gtx/matrix_transform_2d.hpp"

void vortex(sil::Image& image)
{
    auto result = sil::Image{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            auto const  position     = glm::vec2{x, y};
            auto const  center       = glm::vec2{image.width() / 2, image.height() / 2};
            float const rotation     = glm::distance(position, center) * 0.1f;
            auto const  new_position = center + glm::vec2{glm::rotate(glm::mat3{1.f}, rotation) * glm::vec3{position - center, 0.f}};
            result.pixel(x, y)       = image.pixel(
                std::clamp(static_cast<int>(new_position.x), 0, image.width() - 1),
                std::clamp(static_cast<int>(new_position.y), 0, image.height() - 1)
            );
        }
    }
    image = result;
}