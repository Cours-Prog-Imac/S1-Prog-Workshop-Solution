#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/input.png"};
    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            image.pixel(x, y).r = 0.f;
        }
    }
    image.save("output/guess_the_effect.png");
}