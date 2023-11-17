#include "convolution.hpp"

struct Kernel {
    Kernel(int width, int height)
    {
        values.resize(width);
        for (std::vector<float>& vec : values)
            vec.resize(height);
    }

    Kernel(std::vector<std::vector<float>> kernel)
        : values{kernel}
    {
    }

    std::vector<std::vector<float>> values;

    int width() const
    {
        return values.size();
    }

    int height() const
    {
        if (values.empty())
            return 0;
        return values[0].size();
    }

    float at(int x, int y) const
    {
        return values[x][y];
    }
    float& at(int x, int y)
    {
        return values[x][y];
    }
};

int clamp(int x, int min, int max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

static void apply_kernel(sil::Image& image, Kernel const& kernel)
{
    sil::Image result{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 value{0.f};
            for (int xk{0}; xk < kernel.width(); xk++)
            {
                for (int yk{0}; yk < kernel.height(); yk++)
                {
                    int const xx = clamp(x + xk - kernel.width() / 2, 0, image.width() - 1);
                    int const yy = clamp(y + yk - kernel.height() / 2, 0, image.height() - 1);
                    value += image.pixel(xx, yy) * kernel.at(xk, yk);
                }
            }
            result.pixel(x, y) = value;
        }
    }
    image = result;
}

void box_blur(sil::Image& image, int const kernel_size)
{
    Kernel kernel{kernel_size, kernel_size};
    for (int x{0}; x < kernel.width(); ++x)
    {
        for (int y{0}; y < kernel.height(); ++y)
        {
            kernel.at(x, y) = 1.f / static_cast<float>(kernel.width()) / static_cast<float>(kernel.height());
        }
    }
    apply_kernel(image, kernel);
}

void box_blur_separable_filter(sil::Image& image, int const kernel_size)
{
    Kernel kernel_x{kernel_size, 1};
    Kernel kernel_y{1, kernel_size};
    for (int x{0}; x < kernel_size; ++x)
    {
        kernel_x.at(x, 0) = 1.f / static_cast<float>(kernel_size);
    }
    for (int y{0}; y < kernel_size; ++y)
    {
        kernel_y.at(0, y) = 1.f / static_cast<float>(kernel_size);
    }
    apply_kernel(image, kernel_x);
    apply_kernel(image, kernel_y);
}

void sharpen(sil::Image& image)
{
    apply_kernel(
        image,
        Kernel{{
            std::vector<float>{+0.f, -1.f, +0.f},
            std::vector<float>{-1.f, +5.f, -1.f},
            std::vector<float>{+0.f, -1.f, +0.f},
        }}
    );
}

void emboss(sil::Image& image)
{
    apply_kernel(
        image,
        Kernel{{
            std::vector<float>{-2.f, -1.f, +0.f},
            std::vector<float>{-1.f, +1.f, +1.f},
            std::vector<float>{+0.f, +1.f, +2.f},
        }}
    );
}

void outline(sil::Image& image)
{
    apply_kernel(
        image,
        Kernel{{
            std::vector<float>{-1.f, -1.f, -1.f},
            std::vector<float>{-1.f, +8.f, -1.f},
            std::vector<float>{-1.f, -1.f, -1.f},
        }}
    );
}