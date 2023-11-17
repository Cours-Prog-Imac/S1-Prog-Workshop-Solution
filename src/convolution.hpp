#pragma once
#include "sil/sil.hpp"

void box_blur(sil::Image& image, int const kernel_size);
void box_blur_separable_filter(sil::Image& image, int const kernel_size);
void sharpen(sil::Image& image);
void emboss(sil::Image& image);
void outline(sil::Image& image);