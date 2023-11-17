#include "Filtre de Kuwahara.hpp"
#include <algorithm>

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