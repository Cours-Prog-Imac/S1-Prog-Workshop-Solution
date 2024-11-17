#include "Degrade Lab.hpp"

float srgb_from_linear_rgb_impl(float x)
{
    if (x >= 0.0031308f)
        return 1.055f * std::pow(x, 1.f / 2.4f) - 0.055f;
    else
        return 12.92f * x;
}

float linear_rgb_from_srgb_impl(float x)
{
    if (x >= 0.04045)
        return std::pow((x + 0.055f) / (1.f + 0.055f), 2.4f);
    else
        return x / 12.92f;
}

glm::vec3 linear_rgb_from_srgb(glm::vec3 const& srgb)
{
    return {
        linear_rgb_from_srgb_impl(srgb.r),
        linear_rgb_from_srgb_impl(srgb.g),
        linear_rgb_from_srgb_impl(srgb.b),
    };
}

glm::vec3 srgb_from_linear_rgb(glm::vec3 const& rgb)
{
    return {
        srgb_from_linear_rgb_impl(rgb.r),
        srgb_from_linear_rgb_impl(rgb.g),
        srgb_from_linear_rgb_impl(rgb.b),
    };
}

glm::vec3 srgb_from_oklab(glm::vec3 const& lab)
{
    float const l_ = lab.x + 0.3963377774f * lab.y + 0.2158037573f * lab.z;
    float const m_ = lab.x - 0.1055613458f * lab.y - 0.0638541728f * lab.z;
    float const s_ = lab.x - 0.0894841775f * lab.y - 1.2914855480f * lab.z;

    float const l = l_ * l_ * l_;
    float const m = m_ * m_ * m_;
    float const s = s_ * s_ * s_;

    return srgb_from_linear_rgb({
        +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
        -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
        -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    });
}

glm::vec3 oklab_from_srgb(glm::vec3 const& srgb)
{
    glm::vec3 const lin_rgb = linear_rgb_from_srgb(srgb);

    float const l = 0.4122214708f * lin_rgb.r + 0.5363325363f * lin_rgb.g + 0.0514459929f * lin_rgb.b;
    float const m = 0.2119034982f * lin_rgb.r + 0.6806995451f * lin_rgb.g + 0.1073969566f * lin_rgb.b;
    float const s = 0.0883024619f * lin_rgb.r + 0.2817188376f * lin_rgb.g + 0.6299787005f * lin_rgb.b;

    float const l_ = cbrtf(l);
    float const m_ = cbrtf(m);
    float const s_ = cbrtf(s);

    return {
        0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_,
        1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_,
        0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_,
    };
}

void gradient_lab(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float const t     = static_cast<float>(x) / static_cast<float>(image.width() - 1);
            image.pixel(x, y) = srgb_from_oklab(
                glm::mix(
                    oklab_from_srgb({1.f, 0.f, 0.f}),
                    oklab_from_srgb({0.f, 1.f, 0.f}),
                    t
                )
            );
        }
    }
}