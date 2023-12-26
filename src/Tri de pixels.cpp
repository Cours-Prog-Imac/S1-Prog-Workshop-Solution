#include "Tri de pixels.hpp"
#include <algorithm>
#include "random.hpp"

float brightness(glm::vec3 const& color)
{
    return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
}

void pixel_sorting(sil::Image& image)
{
    int const group_length{101};

    for (int i = 0; i < image.pixels().size() / group_length; ++i)
    {
        if (true_with_probability(0.7f))
            continue;
        int const begin{i * group_length};
        int const end{std::min(
            (i + 1) * group_length,
            static_cast<int>(image.pixels().size())
        )};
        std::sort(image.pixels().begin() + begin, image.pixels().begin() + end, [](glm::vec3 const& col1, glm::vec3 const& col2) {
            return brightness(col1) < brightness(col2);
        });
    }
}