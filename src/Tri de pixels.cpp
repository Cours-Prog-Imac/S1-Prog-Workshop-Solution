#include "Tri de pixels.hpp"
#include <algorithm>
#include "random.hpp"

void pixel_sorting(sil::Image& image)
{
    int const group_length{101};

    for (int i = 0; i < image.pixels().size() / group_length; ++i)
    {
        if (random_float(0.f, 1.f) < 0.7f)
            continue;
        int const begin{i * group_length};
        int const end{std::min(
            (i + 1) * group_length,
            static_cast<int>(image.pixels().size())
        )};
        std::sort(image.pixels().begin() + begin, image.pixels().begin() + end, [](glm::vec3 col1, glm::vec3 col2) {
            glm::vec3 const channel_brightness{1.f / 3.f};
            return glm::dot(col1, channel_brightness) < glm::dot(col2, channel_brightness);
        });
    }
}