#include "K-means.hpp"
#include "random.hpp"

size_t find_closest_mean_index(glm::vec3 const& color, std::vector<glm::vec3> const& current_means)
{
    float  min_dist{std::numeric_limits<float>::max()};
    size_t index{};
    for (size_t i{0}; i < current_means.size(); ++i)
    {
        float const dist{glm::distance(color, current_means[i])};
        if (dist < min_dist)
        {
            min_dist = dist;
            index    = i;
        }
    }
    return index;
}

glm::vec3 find_closest_mean(glm::vec3 const& color, std::vector<glm::vec3> const& current_means)
{
    return current_means[find_closest_mean_index(color, current_means)];
}

std::vector<glm::vec3> find_new_means(sil::Image const& image, std::vector<glm::vec3> const& current_means)
{
    std::vector<glm::vec3> new_means(current_means.size());
    std::vector<int>       nb_colors_per_mean(current_means.size());
    for (glm::vec3 const& color : image.pixels())
    {
        size_t const index{find_closest_mean_index(color, current_means)};
        new_means[index] += color;
        nb_colors_per_mean[index] += 1;
    }
    for (size_t i{0}; i < new_means.size(); ++i)
    {
        if (nb_colors_per_mean[i] != 0)
            new_means[i] /= nb_colors_per_mean[i];
    }
    return new_means;
}

void k_means(sil::Image& image, int nb_colors)
{
    std::vector<glm::vec3> means(nb_colors);
    // Initialize means
    for (glm::vec3& mean : means)
    {
        mean = image.pixels()[random_int(0, image.pixels().size())];
    }
    // Iterate k-means process
    for (int i = 0; i < 10; ++i) // 10 is an empiric number that gives good quality and good performance
    {
        means = find_new_means(image, means);
    }
    // Assign each pixel to its closest mean color
    for (glm::vec3& color : image.pixels())
    {
        color = find_closest_mean(color, means);
    }
}