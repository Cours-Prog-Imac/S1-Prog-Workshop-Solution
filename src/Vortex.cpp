#include "Vortex.hpp"
#include <algorithm>
#include "glm/gtx/matrix_transform_2d.hpp"

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void vortex(sil::Image& image)
{
    sil::Image result{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 const position{x, y};
            glm::vec2 const center{image.width() / 2, image.height() / 2};
            float const     rotation{glm::distance(position, center) * 0.1f};
            glm::vec2 const new_position{rotated(position, center, rotation)};
            result.pixel(x, y) = image.pixel(
                std::clamp(static_cast<int>(new_position.x), 0, image.width() - 1),
                std::clamp(static_cast<int>(new_position.y), 0, image.height() - 1)
            );
        }
    }
    image = result;
}