#include "Diamond Square.hpp"
#include "random.hpp"

bool is_power_of_2(int n)
{
    // A number is a power of 2 if and only if it has only one set bit (1) in its binary representation.
    // For example: 2 (binary: 10), 4 (binary: 100), 8 (binary: 1000), etc.

    // Check if the number is positive and has only one set bit.
    return n > 0 && (n & (n - 1)) == 0;
}

void diamond_square(sil::Image& image)
{
    assert(is_power_of_2(image.width() - 1));
    assert(image.width() == image.height());

    // Init the four corners
    image.pixel(0, 0)                                  = glm::vec3{random_float(0.f, 1.f)};
    image.pixel(0, image.height() - 1)                 = glm::vec3{random_float(0.f, 1.f)};
    image.pixel(image.width() - 1, image.height() - 1) = glm::vec3{random_float(0.f, 1.f)};
    image.pixel(image.width() - 1, 0)                  = glm::vec3{random_float(0.f, 1.f)};

    // Repeatedly apply the square and diamond steps
    float roughness{0.9f};
    int   chunk_size{image.width() - 1};
    while (chunk_size > 1)
    {
        int const half{chunk_size / 2};
        // Square step
        for (int x{0}; x < image.width() - 1; x += chunk_size)
        {
            for (int y{0}; y < image.height() - 1; y += chunk_size)
            {
                image.pixel(x + half, y + half) =
                    (image.pixel(x, y) +
                     image.pixel(x, y + chunk_size) +
                     image.pixel(x + chunk_size, y + chunk_size) +
                     image.pixel(x + chunk_size, y)
                    ) / 4.f +
                    random_float(-roughness, +roughness);
            }
        }
        // Diamond step
        for (int x{0}; x < image.width(); x += half)
        {
            for (int y{(x + half) % chunk_size}; y < image.height(); y += chunk_size)
            {
                int        count{0};
                auto const try_count_neighbor = [&](int xx, int yy) {
                    if (0 <= xx && xx < image.width() &&
                        0 <= yy && yy < image.height())
                    {
                        count += 1;
                        image.pixel(x, y) += image.pixel(xx, yy);
                    }
                };
                try_count_neighbor(x - half, y);
                try_count_neighbor(x + half, y);
                try_count_neighbor(x, y - half);
                try_count_neighbor(x, y + half);
                image.pixel(x, y) /= static_cast<float>(count);
                image.pixel(x, y) += random_float(-roughness, +roughness);
            }
        }
        chunk_size /= 2;
        roughness /= 2.f;
    }
}

glm::vec3 threshold(glm::vec3 const& color)
{
    float const N{12};
    return glm::floor(color * N) / N;
}

glm::vec3 const DARK_BLUE{0.000f, 0.003f, 0.230f};
glm::vec3 const LIGHT_BLUE{0.233f, 0.635f, 1.000f};
glm::vec3 const GREEN{0.205f, 0.652f, 0.188f};
glm::vec3 const BROWN{0.166f, 0.114f, 0.000f};

void colorize_heightmap(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = threshold(color);
        if (color.r < 0.5f)
            color = glm::mix(DARK_BLUE, LIGHT_BLUE, color.r * 2.f);
        else
            color = glm::mix(GREEN, BROWN, (color.r - 0.5f) * 2.f);
    }
}