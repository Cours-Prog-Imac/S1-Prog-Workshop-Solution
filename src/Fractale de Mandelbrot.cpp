#include "Fractale de Mandelbrot.hpp"
#include <complex>

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