#include "diamond_square.hpp"
#include "glm/common.hpp"
#include "random.hpp"

bool is_power_of_2(int n)
{
    // A number is a power of 2 if and only if it has only one set bit (1) in its binary representation.
    // For example: 2 (binary: 10), 4 (binary: 100), 8 (binary: 1000), etc.

    // Check if the number is positive and has only one set bit.
    return n > 0 && (n & (n - 1)) == 0;
}

// float random_variation()
// {
//     return random_float(-0.1f, +0.1f);
// }

// void square_step(sil::Image& image, int min_x, int min_y, int max_x, int max_y)
// {
//     image.pixel((min_x + max_x) / 2, (min_y + max_y) / 2) =
//         // Random variation
//         random_variation() +
//         // Average of the four corners
//         (image.pixel(min_x, min_y) +
//          image.pixel(min_x, max_y) +
//          image.pixel(max_x, max_y) +
//          image.pixel(max_x, min_y)
//         ) / 4.f;
// }

// void compute_diamond(sil::Image& image, int x, int y, int size)
// {
//     int count{0};

//     auto const try_count_neighbor = [&](int xx, int yy) {
//         if (0 <= xx && xx < image.width() &&
//             0 <= yy && yy < image.height())
//         {
//             count += 1;
//             image.pixel(x, y) += image.pixel(xx, yy);
//         }
//     };
//     try_count_neighbor(x - size, y);
//     try_count_neighbor(x + size, y);
//     try_count_neighbor(x, y - size);
//     try_count_neighbor(x, y + size);
//     image.pixel(x, y) /= static_cast<float>(count);
//     image.pixel(x, y) += random_variation();
// }

// void diamond_step(sil::Image& image, int min_x, int min_y, int max_x, int max_y)
// {
//     int const size{(max_x - min_x) / 2};
//     compute_diamond(image, (min_x + max_x) / 2, min_y, size);
//     compute_diamond(image, (min_x + max_x) / 2, max_y, size);
//     compute_diamond(image, min_x, (min_y + max_y) / 2, size);
//     compute_diamond(image, max_x, (min_y + max_y) / 2, size);
// }

// void diamond_square_step(sil::Image& image, int min_x, int min_y, int max_x, int max_y)
// {
//     if (max_x - min_x <= 1)
//         return;
//     square_step(image, min_x, min_y, max_x, max_y);
//     diamond_step(image, min_x, min_y, max_x, max_y);
//     int const mid_x{(min_x + max_x) / 2};
//     int const mid_y{(min_y + max_y) / 2};
//     // TODO do steps breadth first, not depth first
//     diamond_square_step(image, min_x, min_y, mid_x, mid_y);
//     diamond_square_step(image, min_x, mid_y, mid_x, max_y);
//     diamond_square_step(image, mid_x, min_y, max_x, mid_y);
//     diamond_square_step(image, mid_x, mid_y, max_x, max_y);
// }

// void diamond_square(sil::Image& image)
// {
//     assert(is_power_of_2(image.width() - 1));
//     assert(image.width() == image.height());

//     // Init the four corners
//     image.pixel(0, 0)                                  = glm::vec3{random_float(0.f, 1.f)};
//     image.pixel(0, image.height() - 1)                 = glm::vec3{random_float(0.f, 1.f)};
//     image.pixel(image.width() - 1, image.height() - 1) = glm::vec3{random_float(0.f, 1.f)};
//     image.pixel(image.width() - 1, 0)                  = glm::vec3{random_float(0.f, 1.f)};

//     // Recursively apply the steps
//     diamond_square_step(image, 0, 0, image.width() - 1, image.height() - 1);
// }

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
        // Square step
        int const half{chunk_size / 2};
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
        // for (int x{0}; x < image.width() - chunk_size; x += chunk_size)
        // {
        //     for (int y{0}; y < image.height() - chunk_size; y += chunk_size)
        //     {
        //         auto const compute_one_diamond = [&](int diamond_x, int diamond_y) {
        //             int        count{0};
        //             auto const try_count_neighbor = [&](int xx, int yy) {
        //                 if (0 <= xx && xx < image.width() &&
        //                     0 <= yy && yy < image.height())
        //                 {
        //                     count += 1;
        //                     image.pixel(diamond_x, diamond_y) += image.pixel(xx, yy);
        //                 }
        //             };
        //             try_count_neighbor(diamond_x - half, diamond_y);
        //             try_count_neighbor(diamond_x + half, diamond_y);
        //             try_count_neighbor(diamond_x, diamond_y - half);
        //             try_count_neighbor(diamond_x, diamond_y + half);
        //             image.pixel(diamond_x, diamond_y) /= static_cast<float>(count);
        //             image.pixel(diamond_x, diamond_y) += random_float(-roughness, +roughness);
        //         };
        //         compute_one_diamond(x + half, y);
        //         compute_one_diamond(x, y + half);
        //         compute_one_diamond(x + chunk_size, y + half);
        //         compute_one_diamond(x + half, y + chunk_size);
        //     }
        // }
        //

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
                image.pixel(x, y) = image.pixel(x, y);
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