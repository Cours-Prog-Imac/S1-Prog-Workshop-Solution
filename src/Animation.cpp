#include "Animation.hpp"
#include <sil/sil.hpp>
#include <string>
#include "Disque.hpp"

void animation()
{
    int const nb_frames = 60;
    for (int i{0}; i < nb_frames; ++i)
    {
        sil::Image image{200, 200};

        glm::vec2 const center = {
            image.width() * i / static_cast<float>(nb_frames),
            image.height() / 2.f
        };
        disk(image, center, 50.f);
        image.save("output/animation/" + std::to_string(i) + ".png");
    }
}