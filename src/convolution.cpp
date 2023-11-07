#include "convolution.hpp"

struct Kernel {
    Kernel(int width, int height)
    {
        values.resize(width);
        for (std::vector<float>& vec : values)
            vec.resize(height);
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
    for (int x = 0; x < kernel.width(); ++x)
    {
        for (int y = 0; y < kernel.height(); ++y)
        {
            kernel.at(x, y) = 1.f / static_cast<float>(kernel.width()) / static_cast<float>(kernel.height());
        }
    }
    apply_kernel(image, kernel);
}