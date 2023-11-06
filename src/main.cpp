#include <algorithm>
#include <sil/sil.hpp>
#include "glm/gtx/matrix_transform_2d.hpp"

void black_and_white(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 const color = image.pixel(x, y);
            float const     grey  = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
            image.pixel(x, y)     = glm::vec3{grey, grey, grey};
        }
    }
}

void channels_swap(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(
                image.pixel(x, y).r,
                image.pixel(x, y).b
            );
        }
    }
}

void pixel_sorting(sil::Image& image)
{
    int const group_length{101};

    for (int i = 0; i < image.pixels().size() / group_length; ++i)
    {
        float const random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (random < 0.7f)
            continue;
        int const begin = i * group_length;
        int const end   = std::min(
            (i + 1) * group_length,
            static_cast<int>(image.pixels().size())
        );
        std::sort(image.pixels().begin() + begin, image.pixels().begin() + end, [](glm::vec3 col1, glm::vec3 col2) {
            glm::vec3 const channel_brightness{1.f / 3.f};
            return glm::dot(col1, channel_brightness) < glm::dot(col2, channel_brightness);
        });
    }
}

void rgb_split(sil::Image& image)
{
    int const offset{30};

    auto result = sil::Image{image.width(), image.height()};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = glm::vec3{
                image.pixel(std::max(x - offset, 0), y).r,
                image.pixel(x, y).g,
                image.pixel(std::min(x + offset, image.width() - 1), y).b,
            };
        }
    }

    image = result;
}

void miroir(sil::Image& image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(
                image.pixel(x, y),
                image.pixel(image.width() - 1 - x, y)
            );
        }
    }
}

int random_int(int min, int max)
{
    return rand() % (max - min) + min;
}

void position_glitch(sil::Image& image)
{
    int const nb_squares{100};

    for (int i{0}; i < nb_squares; ++i)
    {
        int const width{random_int(1, 30)};
        int const height{random_int(1, 10)};

        int const x1{random_int(0, image.width() - 1 - width)};
        int const x2{random_int(0, image.width() - 1 - width)};
        int const y1{random_int(0, image.height() - 1 - height)};
        int const y2{random_int(0, image.height() - 1 - height)};

        for (int x_offset{0}; x_offset < width; ++x_offset)
        {
            for (int y_offset{0}; y_offset < height; ++y_offset)
            {
                std::swap(
                    image.pixel(x1 + x_offset, y1 + y_offset),
                    image.pixel(x2 + x_offset, y2 + y_offset)
                );
            }
        }
    }
}

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

int main()
{
    {
        sil::Image image{"images/imac.png"};
        black_and_white(image);
        image.save("output/black_and_white.png");
    }
    {
        sil::Image image{"images/imac.png"};
        channels_swap(image);
        image.save("output/channels_swap.png");
    }
    {
        sil::Image image{"images/imac.png"};
        pixel_sorting(image);
        image.save("output/pixel_sorting.png");
    }
    {
        sil::Image image{"images/imac.png"};
        rgb_split(image);
        image.save("output/rgb_split.png");
    }
    {
        sil::Image image{"images/imac.png"};
        miroir(image);
        image.save("output/miroir.png");
    }
    {
        sil::Image image{"images/imac.png"};
        position_glitch(image);
        image.save("output/position_glitch.png");
    }
    {
        sil::Image image{"images/imac.png"};
        vortex(image);
        image.save("output/vortex.png");
    }
}