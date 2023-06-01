#include <sil/sil.hpp>

void pixel_sorting(sil::Image& image)
{
    int const group_length = 100;
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

int main()
{
    {
        sil::Image image{"images/imac.png"};
        pixel_sorting(image);
        image.save("output/pixel_sorting.png");
    }
}