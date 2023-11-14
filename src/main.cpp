#include <algorithm>
#include <complex>
#include <limits>
#include <sil/sil.hpp>
#include "convolution.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"
#include "normalize_histogram.hpp"

void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void black_and_white(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float const grey = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
        color            = glm::vec3{grey, grey, grey};
    }
}

sil::Image mosaic(sil::Image const& image)
{
    sil::Image result{image.width() * 5, image.height() * 5};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = image.pixel(
                x % image.width(),
                y % image.height()
            );
        }
    }
    return result;
}

static int flip_at_middle(int x, int middle)
{
    if (x >= middle)
        x = 2 * middle - x - 1;
    return x;
}

sil::Image mosaic_flip(sil::Image const& image)
{
    sil::Image result{image.width() * 5, image.height() * 5};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = image.pixel(
                flip_at_middle(x % (2 * image.width()), image.width()),
                flip_at_middle(y % (2 * image.height()), image.height())
            );
        }
    }
    return result;
}

void gradient(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
}

void disk(sil::Image& image, glm::vec2 center, float radius)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 position{x, y};
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
            glm::vec2   position{x, y};
            float const distance{glm::distance(position, center)};
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

static constexpr float TAU = 6.28f;

void rosace(sil::Image& image, float radius, float thickness)
{
    glm::vec2 const center{image.width() / 2.f, image.height() / 2.f};
    circle(image, center, radius, thickness);

    for (int i = 0; i < 6; ++i)
    {
        glm::vec2 const outer_center{center + from_polar_coordinates(radius, i * TAU / 6.f)};
        circle(image, outer_center, radius, thickness);
    }
}

void channels_swap(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = 1.f - color;
    }
}

void pixel_sorting(sil::Image& image)
{
    int const group_length{101};

    for (int i = 0; i < image.pixels().size() / group_length; ++i)
    {
        float const random{static_cast<float>(rand()) / static_cast<float>(RAND_MAX)};
        if (random < 0.7f)
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

void rgb_split(sil::Image& image)
{
    int const offset{30};

    sil::Image result{image.width(), image.height()};
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

void mirror(sil::Image& image)
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

sil::Image rotate_90_degrees(sil::Image const& image)
{
    sil::Image result{image.height(), image.width()};
    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            result.pixel(x, y) = image.pixel(y, image.height() - 1 - x);
        }
    }
    return result;
}

sil::Image mandelbrot()
{
    sil::Image image{500, 500};
    for (int xi{0}; xi < image.width(); xi++)
    {
        for (int yi{0}; yi < image.height(); yi++)
        {
            std::complex<float> const c{
                static_cast<float>(xi) / (image.width() - 1) * 3.f - 2.f,
                static_cast<float>(yi) / (image.height() - 1) * 3.f - 1.5f,
            };
            std::complex<float> z{0.f};

            int                  iterations{0};
            static constexpr int max_iterations{30};
            while (iterations < max_iterations && std::abs(z) < 2.f)
            {
                z = z * z + c;
                iterations++;
            }
            image.pixel(xi, yi) = glm::vec3{static_cast<float>(iterations) / static_cast<float>(max_iterations)};
        }
    }
    return image;
}

void luminosity(sil::Image& image, float luminosity)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::pow(color, glm::vec3{luminosity});
    }
}

sil::Image kuwahara(sil::Image const& image, int const square_size)
{
    sil::Image result{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            // For each pixel
            glm::vec3 const main_pixel_color{image.pixel(x, y)};
            glm::vec3       current_selected_color{};
            float           current_selected_variance{std::numeric_limits<float>::max()};
            for (int x_sign{-1}; x_sign < 2; x_sign += 2)
            {
                for (int y_sign{-1}; y_sign < 2; y_sign += 2)
                {
                    // For each of the four squares around the pixel
                    // Compute average color
                    glm::vec3 average{0.f};
                    for (int xx{0}; xx < square_size; xx++)
                    {
                        for (int yy{0}; yy < square_size; yy++)
                        {
                            // For each pixel in one of the four squares
                            int const       pixel_x{std::clamp(x + x_sign * xx, 0, image.width() - 1)};
                            int const       pixel_y{std::clamp(y + y_sign * yy, 0, image.height() - 1)};
                            glm::vec3 const pixel_color{image.pixel(pixel_x, pixel_y)};
                            average += pixel_color;
                        }
                    }
                    average /= square_size * square_size;
                    // Compute variance
                    float variance{0.f};
                    for (int xx{0}; xx < square_size; xx++)
                    {
                        for (int yy{0}; yy < square_size; yy++)
                        {
                            // For each pixel in one of the four squares
                            int const       pixel_x{std::clamp(x + x_sign * xx, 0, image.width() - 1)};
                            int const       pixel_y{std::clamp(y + y_sign * yy, 0, image.height() - 1)};
                            glm::vec3 const pixel_color{image.pixel(pixel_x, pixel_y)};
                            variance += glm::dot(pixel_color - main_pixel_color, pixel_color - main_pixel_color); // Norme au carré
                        }
                    }
                    if (variance < current_selected_variance)
                    {
                        current_selected_variance = variance;
                        current_selected_color    = average;
                    }
                }
            }
            result.pixel(x, y) = current_selected_color;
        }
    }
    return result;
}

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
        mean = image.pixels()[rand() % (image.width() * image.height())];
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
        keep_green_only(image);
        image.save("output/keep_green_only.png");
    }
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
        negative(image);
        image.save("output/negative.png");
    }
    {
        sil::Image image{"images/imac.png"};
        image = mosaic(image);
        image.save("output/mosaic.png");
    }
    {
        sil::Image image{"images/imac.png"};
        image = mosaic_flip(image);
        image.save("output/mosaic_flip.png");
    }
    {
        sil::Image image{500, 500};
        disk(image, {250.f, 250.f}, 100.f);
        image.save("output/disk.png");
    }
    {
        sil::Image image{500, 500};
        circle(image, {250.f, 250.f}, 100.f, 10.f);
        image.save("output/circle.png");
    }
    {
        sil::Image image{500, 500};
        rosace(image, 100.f, 5.f);
        image.save("output/rosace.png");
    }
    {
        sil::Image image = mandelbrot();
        image.save("output/mandelbrot.png");
    }
    {
        sil::Image image{"images/photo.jpg"};
        luminosity(image, 1.f / 1.25f);
        image.save("output/luminosity+.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        luminosity(image, 1.25f);
        image.save("output/luminosity-.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        image = kuwahara(image, 10);
        image.save("output/kuwahara.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        k_means(image, 2);
        image.save("output/k_means_2_colors.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        k_means(image, 3);
        image.save("output/k_means_3_colors.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        k_means(image, 18);
        image.save("output/k_means_18_colors.jpg");
    }
    {
        sil::Image image{"images/imac.png"};
        pixel_sorting(image);
        image.save("output/pixel_sorting.png");
    }
    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        normalize_histogram(image);
        image.save("output/normalize_histogram.jpg");
    }
    {
        sil::Image image{"images/imac.png"};
        box_blur(image, 20);
        image.save("output/box_blur.png");
    }
    {
        sil::Image image{"images/imac.png"};
        rgb_split(image);
        image.save("output/rgb_split.png");
    }
    {
        sil::Image image{"images/imac.png"};
        mirror(image);
        image.save("output/mirror.png");
    }
    {
        sil::Image image{"images/imac.png"};
        image = rotate_90_degrees(image);
        image.save("output/rotate_90_degrees.png");
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
    {
        sil::Image image{300, 200};
        gradient(image);
        image.save("output/gradient.png");
    }
}