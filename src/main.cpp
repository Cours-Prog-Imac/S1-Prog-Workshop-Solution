#include <sil/sil.hpp>

void pixel_sorting(sil::Image& image)
{
    int const group_length = 101;
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
    static constexpr int offset = 30;

    auto result = sil::Image{image.width(), image.height()};
    for (int x = 0; x < result.width(); x++)
    {
        for (int y = 0; y < result.height(); y++)
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

int main()
{
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
}