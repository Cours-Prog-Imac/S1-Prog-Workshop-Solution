#include "Disque.hpp"

void disk(sil::Image& image, glm::vec2 center, float radius)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 const position{x, y};
            if (glm::distance(position, center) < radius)
                image.pixel(x, y) = glm::vec3{1.f};
        }
    }
}

void circle(sil::Image& image, glm::vec2 center, float radius, float thickness)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 const position{x, y};
            float const     distance{glm::distance(position, center)};
            if (
                distance < radius + thickness / 2.f &&
                distance > radius - thickness / 2.f
            )
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

glm::vec2 from_polar_coordinates(float length, float angle_in_radians)
{
    return length * glm::vec2{
                        std::cos(angle_in_radians),
                        std::sin(angle_in_radians),
                    };
}

float const TWO_PI{6.283185307f};

void rosace(sil::Image& image, float radius, float thickness)
{
    glm::vec2 const center{image.width() / 2.f, image.height() / 2.f};
    circle(image, center, radius, thickness);

    for (int i = 0; i < 6; ++i)
    {
        glm::vec2 const outer_disk_center{center + from_polar_coordinates(radius, i * TWO_PI / 6.f)};
        circle(image, outer_disk_center, radius, thickness);
    }
}