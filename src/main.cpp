#include <iostream>
#include "Convolutions.hpp"
#include "Degrade.hpp"
#include "Diamond Square.hpp"
#include "Disque.hpp"
#include "Echanger les canaux.hpp"
#include "Filtre de Kuwahara.hpp"
#include "Fractale de Mandelbrot.hpp"
#include "Glitch.hpp"
#include "Image bruitee.hpp"
#include "K-means.hpp"
#include "Luminosite.hpp"
#include "Miroir.hpp"
#include "Mosaique.hpp"
#include "Ne garder que le vert.hpp"
#include "Negatif.hpp"
#include "Noir et Blanc.hpp"
#include "Normalisation de l'histogramme.hpp"
#include "RGB split.hpp"
#include "Rotation de 90.hpp"
#include "Tramage.hpp"
#include "Tri de pixels.hpp"
#include "Vortex.hpp"
#include "random.hpp"

int main()
{
    set_random_seed(1234); // Arbitrary number, guarantees that the artworks that depend on random will be the same every run (helps me check that my algorithm produces the same result when I tweak it).
    {
        sil::Image image{"images/logo.png"};
        keep_green_only(image);
        image.save("output/keep_green_only.png");
    }
    {
        sil::Image image{"images/logo.png"};
        black_and_white(image);
        image.save("output/black_and_white.png");
    }
    {
        sil::Image image{"images/logo.png"};
        channels_swap(image);
        image.save("output/channels_swap.png");
    }
    {
        sil::Image image{"images/logo.png"};
        negative(image);
        image.save("output/negative.png");
    }
    {
        sil::Image image{"images/logo.png"};
        image = mosaic(image);
        image.save("output/mosaic.png");
    }
    {
        sil::Image image{"images/logo.png"};
        image = mosaic_flip(image);
        image.save("output/mosaic_flip.png");
    }
    {
        sil::Image image{300, 200};
        gradient(image);
        image.save("output/gradient.png");
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
        k_means(image, 16);
        image.save("output/k_means_16_colors.jpg");
    }
    {
        sil::Image image{"images/logo.png"};
        pixel_sorting(image);
        image.save("output/pixel_sorting.png");
    }
    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        normalize_histogram(image);
        image.save("output/normalize_histogram.jpg");
    }
    {
        sil::Image image{"images/logo.png"};
        box_blur(image, 20);
        image.save("output/box_blur.png");
    }
    {
        sil::Image image{"images/logo.png"};
        auto const begin = std::chrono::steady_clock::now();
        box_blur(image, 100);
        std::cout << "Naive box blur took " << (std::chrono::steady_clock::now() - begin).count() / 1000000000.f << " seconds.\n";
        image.save("output/big_box_blur.png");
    }
    {
        sil::Image image{"images/logo.png"};
        auto const begin = std::chrono::steady_clock::now();
        box_blur_separable_filter(image, 100);
        std::cout << "Separated box blur took " << (std::chrono::steady_clock::now() - begin).count() / 1000000000.f << " seconds.\n";
        image.save("output/big_box_blur_separable_filter.png");
    }
    {
        sil::Image image{"images/logo.png"};
        sharpen(image);
        image.save("output/sharpen.png");
    }
    {
        sil::Image image{"images/logo.png"};
        emboss(image);
        image.save("output/emboss.png");
    }
    {
        sil::Image image{"images/logo.png"};
        outline(image);
        image.save("output/outline.png");
    }
    {
        sil::Image image{"images/logo.png"};
        rgb_split(image);
        image.save("output/rgb_split.png");
    }
    {
        sil::Image image{"images/logo.png"};
        mirror(image);
        image.save("output/mirror.png");
    }
    {
        sil::Image image{"images/logo.png"};
        image = rotate_90_degrees(image);
        image.save("output/rotate_90_degrees.png");
    }
    {
        sil::Image image{"images/logo.png"};
        noisy_image(image);
        image.save("output/noisy_image.png");
    }
    {
        sil::Image image{"images/logo.png"};
        glitch(image);
        image.save("output/glitch.png");
    }
    {
        sil::Image image{"images/logo.png"};
        vortex(image);
        image.save("output/vortex.png");
    }
    {
        sil::Image image{"images/photo.jpg"};
        ordered_dithering(image);
        image.save("output/ordered_dithering.png");
    }
    {
        set_random_seed(2000); // A seed that looks good for our map
        sil::Image image{513, 513};
        diamond_square(image);
        image.save("output/diamond_square_greyscale.png");
        colorize_heightmap(image);
        image.save("output/diamond_square_colored.png");
    }
    {
        sil::Image image{"images/photo.jpg"};
        difference_of_gaussians(image);
        image.save("output/difference_of_gaussians.png");
    }
}