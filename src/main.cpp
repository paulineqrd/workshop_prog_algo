#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <algorithm>
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <vector>

// Exercice 1
void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

// Exercice 2
void channels_swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

// Exercice 3
void black_and_white(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float moyenne = (color.r + color.b + color.g) / 3;
        color.r = moyenne;
        color.b = moyenne;
        color.g = moyenne;
    }
}

// Exercice 4
void negative(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color = glm::vec3{1 - color.r, 1 - color.g, 1 - color.b};
    }
}

// Exercice 5
void gradient(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float t = float(x) / image.width();
            image.pixel(x, y) = glm::vec3(t);
        }
    }
}

// Exercice 6
void mirror(sil::Image &image)
{
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = imageRef.pixel(imageRef.width() - (x + 1), y);
        }
    }
}

// Exercice 7
void noise(sil::Image &image)
{
    int loop = random_int(image.width(), image.width() * image.height());

    for (int i = 0; i < loop; i++)
    {
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());

        image.pixel(x, y).r = random_float(0.f, 1.f);
        image.pixel(x, y).g = random_float(0.f, 1.f);
        image.pixel(x, y).b = random_float(0.f, 1.f);
    }
}

// Exercice 8
sil::Image rotate(sil::Image &image)
{
    sil::Image new_image{image.height(), image.width()};

    // Avec autre fonction
    // for (int x{0}; x < image.width(); x++)
    // {
    //     for (int y{0}; y < image.height(); y++)
    //     {
    //         new_image.pixel(y, x) = image.pixel(x,y);
    //     }
    // }
    // mirror(new_image);

    // Tourné vers la droite
    //  for (int x{0}; x < image.width(); x++)
    //  {
    //      for (int y{0}; y < image.height(); y++)
    //      {
    //          new_image.pixel(y, (image.width() - (x + 1))) = image.pixel(x,y);
    //      }
    //  }

    // Tourner vers la gauche
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }
    return new_image;
}

// Exercice 9
void rgb_split(sil::Image &image)
{
    sil::Image imageRef = image;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x - 30 >= 0)
            {
                image.pixel(x, y).r = imageRef.pixel(x - 30, y).r;
            }
            else
            {
                image.pixel(x, y).r = imageRef.pixel(0, y).r;
            }

            if (x + 30 < image.width())
            {
                image.pixel(x, y).b = imageRef.pixel(x + 30, y).b;
            }
        }
    }
}

// Exercice 10
void brightness(sil::Image &image)
{

    // Eclaircissement
    // for (glm::vec3 &color : image.pixels())
    // {
    //     float a = 0.7f;
    //     color.r = std::pow(color.r, a);
    //     color.g = std::pow(color.g, a);
    //     color.b = std::pow(color.b, a);
    // }

    // Assombrissement
    for (glm::vec3 &color : image.pixels())
    {
        float a = 1.3f;
        color.r = std::pow(color.r, a);
        color.g = std::pow(color.g, a);
        color.b = std::pow(color.b, a);
    }
}

// Exercice 11
void disk(sil::Image &image)
{
    float rayon = 100.f;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float distance = std::pow(x - image.width() / 2.f, 2) + std::pow(y - image.height() / 2.f, 2);
            if (distance <= rayon * rayon)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

// Exercice 12
void circle(sil::Image &image)
{
    float rayon = 100.f;
    float thickness = 5.f;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float distance = std::pow(x - image.width() / 2.f, 2) + std::pow(y - image.height() / 2.f, 2);

            if (distance >= std::pow(rayon - thickness, 2) && distance <= std::pow(rayon + thickness, 2))
            {
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
    }
}

// Exercice 13
void animation(sil::Image &image)
{
    float rayon = 100.f;
    for (int i{0}; i <= image.width(); i += 5)
    {
        sil::Image imageRef = image;
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                if (std::pow(x - i, 2) + std::pow(y - image.height() / 2.f, 2) <= std::pow(rayon, 2))
                {
                    imageRef.pixel(x, y).r = 1.f;
                    imageRef.pixel(x, y).g = 1.f;
                    imageRef.pixel(x, y).b = 1.f;
                }
            }
        }
        imageRef.save("output/animations/animation-" + std::to_string(i) + ".png");
    }
}

// Exercice 14
void rosace(sil::Image &image)
{
    int rayon = 100;
    int thickness = 2;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float distance = std::pow(x - image.width() / 2, 2) + std::pow(y - image.height() / 2, 2);

            if (distance >= std::pow(rayon - thickness, 2) && distance <= std::pow(rayon + thickness, 2))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }

            for (int i{0}; i < 6; i++)
            {
                float angle = i * (2 * M_PI / 6);
                float x_center = image.width() / 2 + rayon * std::cos(angle);
                float y_center = image.height() / 2 + rayon * std::sin(angle);
                float distance = std::pow(x - x_center, 2) + std::pow(y - y_center, 2);

                if (distance >= std::pow(rayon - thickness, 2) && distance <= std::pow(rayon + thickness, 2))
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
    }
}

// Exercice 15
void mosaic(sil::Image &image)
{
    int nbDivision = 5;
    sil::Image newImage{image.width() * nbDivision, image.height() * nbDivision};

    for (int x{0}; x < newImage.width(); x++)
    {
        for (int y{0}; y < newImage.height(); y++)
        {
            newImage.pixel(x, y) = image.pixel(x % image.width(), y % image.height());
        }
    }

    image = newImage;
}

// Exercice 16
void mosaic_mirror(sil::Image &image)
{
    int nbDivision = 5;
    sil::Image newImage{image.width() * nbDivision, image.height() * nbDivision};

    for (int x{0}; x < newImage.width(); x++)
    {
        for (int y{0}; y < newImage.height(); y++)
        {

            int xOriginal = x % image.width();
            int yOriginal = y % image.height();

            int caseX = x / image.width();

            if (caseX % 2 == 1)
            {
                xOriginal = image.width() - 1 - xOriginal;
            }

            newImage.pixel(x, y) = image.pixel(xOriginal, yOriginal);
        }
    }

    image = newImage;
}

// Exercice 17
void glitch(sil::Image &image)
{
    sil::Image imageRef = image;

    for (int i{0}; i < 20; i++)
    {
        int largeur = random_int(20, 40);
        int hauteur = random_int(5, 15);

        int x1 = random_int(0, image.width() - largeur);
        int y1 = random_int(0, image.height() - hauteur);

        int x2 = random_int(0, image.width() - largeur);
        int y2 = random_int(0, image.height() - hauteur);

        for (int x{0}; x < largeur; x++)
        {
            for (int y{0}; y < hauteur; y++)
            {
                image.pixel(x1 + x, y1 + y) = imageRef.pixel(x2 + x, y2 + y);
                image.pixel(x2 + x, y2 + y) = imageRef.pixel(x1 + x, y1 + y);
            }
        }

        imageRef = image;
    }
}

float brightness(glm::vec3 color)
{
    float brightness = color.r + color.g + color.b;
    return brightness;
}

// Exercice 18
void pixel_sorting(sil::Image &image)
{
    std::sort(image.pixels().begin(), image.pixels().end(), [](glm::vec3 const &color1, glm::vec3 const &color2)
              { return brightness(color1) < brightness(color2); });
}

// Exercice 19
void rows_sorting(sil::Image &image)
{
    for (int y{0}; y < image.height(); y++)
    {
        auto begin = image.pixels().begin() + y * image.width();
        auto end = begin + image.width();
        std::sort(begin, end, [](glm::vec3 const &color1, glm::vec3 const &color2)
                  { return brightness(color1) < brightness(color2); });
    }
}

// Exercice 20
void random_sorting(sil::Image &image)
{
    for (int i{0}; i < image.width(); i++)
    {
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());

        int randomWidth = random_int(10, 30);

        randomWidth = std::min(randomWidth, image.width() - x);

        auto begin = image.pixels().begin() + y * image.width() + x;
        auto end = begin + randomWidth;

        std::sort(begin, end, [](glm::vec3 const &color1, glm::vec3 const &color2)
                  { return brightness(color1) < brightness(color2); });
    }
}

// Exercice 21
void mandelbrot_fractal(sil::Image &image)
{
    for (float x{0}; x < image.width(); x++)
    {
        for (float y{0}; y < image.height(); y++)
        {
            float re = x / image.width() * 3.f - 2.f;
            float im = y / image.height() * 3.f - 1.5f;

            std::complex<float> c{re, im};
            std::complex<float> z{0};
            int compteur{0};

            while (std::abs(z) <= 2 && compteur < 100)
            {
                z = z * z + c;
                compteur++;
            }

            int gris = compteur * 255 / 100;
            image.pixel(x, y) = glm::vec3(gris / 255.f);
        }
    }
}

// Exercice 22
void color_gradient(sil::Image &image)
{
    // Version sans glm::mix
    // for (float x{0}; x < image.width(); x++)
    // {
    //     for (float y{0}; y < image.height(); y++)
    //     {
    //         float t = x / image.width();

    //         image.pixel(x, y).r = 1.f - t;
    //         image.pixel(x, y).g = t;
    //     }
    // }

    glm::vec3 color1{1.f, 0.f, 0.f};
    glm::vec3 color2{0.f, 1.f, 0.f};

    for (float x{0}; x < image.width(); x++)
    {
        for (float y{0}; y < image.height(); y++)
        {
            float t = x / image.width();
            image.pixel(x, y) = glm::mix(color1, color2, t);
        }
    }
}

// Exercice 23
void halftone(sil::Image &image)
{
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {-0.5, 0, -0.375, 0.125},
        {0.25, -0.25, 0.375, -0.125},
        {-0.3125, 0.1875, -0.4375, 0.0625},
        {0.4375, -0.0625, 0.3125, -0.1875},
    };

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float luminosity = (image.pixel(x, y).r + image.pixel(x, y).g + image.pixel(x, y).b) / 3.f;
            float seuil = bayer_matrix_4x4[y % bayer_n][x % bayer_n];

            if (luminosity > 0.5f + seuil)
            {
                image.pixel(x, y) = glm::vec3(1.f);
            }
            else
            {
                image.pixel(x, y) = glm::vec3(0.f);
            }
        }
    }
}

// Exercice 24
glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

sil::Image vortex(sil::Image &image)
{
    sil::Image newImage{image.width(), image.height()};
    for (int x{0}; x < newImage.width(); x++)
    {
        for (int y{0}; y < newImage.height(); y++)
        {

            glm::vec2 point{x, y};
            glm::vec2 center{image.width() / 2.f, image.height() / 2.f};

            float distance = glm::distance(point, center);
            float angle = distance * 0.1f;
            glm::vec2 newPoint = rotated(point, center, angle);

            int newX = newPoint.x;
            int newY = newPoint.y;

            if (newX >= 0 && newX < newImage.width() && newY >= 0 && newY < newImage.height())
            {
                newImage.pixel(x, y) = image.pixel(newX, newY);
            }
        }
    }

    return newImage;
}

// Exercice 25
void convolution(sil::Image &image, std::vector<std::vector<float>> kernel)
{
    sil::Image newImage{image.width(), image.height()};

    int kernelSize = kernel.size();
    int offset = kernelSize / 2;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            glm::vec3 color{0.f};
            float divisor = 0.f;

            for (int i = 0; i < kernelSize; i++)
            {
                for (int j = 0; j < kernelSize; j++)
                {
                    int newX = x + i - offset;
                    int newY = y + j - offset;

                    if (newX >= 0 && newX < image.width() && newY >= 0 && newY < image.height())
                    {
                        color += image.pixel(newX, newY) * kernel[i][j];
                    }
                    divisor += kernel[i][j];
                }
            }

            if (divisor != 0.f)
            {
                color = color / divisor;
            }

            newImage.pixel(x, y) = glm::clamp(color, glm::vec3(0.f), glm::vec3(1.f));
        }
    }

    image = newImage;
}

void box_blur(sil::Image &image)
{
    convolution(image, {{1, 1, 1},
                        {1, 1, 1},
                        {1, 1, 1}});
}

void sharpen(sil::Image &image)
{
    convolution(image, {{0, -1, 0},
                        {-1, 5, -1},
                        {0, -1, 0}});
}

void outline(sil::Image &image)
{
    convolution(image, {{-1, -1, -1},
                        {-1, 8, -1},
                        {-1, -1, -1}});
}

void emboss(sil::Image &image)
{
    convolution(image, {{-2, -1, 0},
                        {-1, 1, 1},
                        {0, 1, 2}});
}

int main()
{
    // EXERCICES NOUVELLE IMAGE RECTANGULAIRE
    // sil::Image image{300 /*width*/, 200 /*height*/};
    // gradient(image);
    // color_gradient(image);

    // EXERCICE NOUVELLE IMAGE CARRE
    // sil::Image image{500 /*width*/, 500 /*height*/};
    // disk(image);
    // circle(image);
    // animation(image);
    // rosace(image);
    // mandelbrot_fractal(image);

    // EXERCICES AVEC PHOTO :
    // sil::Image image{"images/photo.jpg"};
    // brightness(image);
    // halftone(image);

    // EXERCICES AVEC LOGO :
    sil::Image image{"images/logo.png"};
    // keep_green_only(image);
    // channels_swap(image);
    // black_and_white(image);
    // negative(image);
    // mirror(image);
    // noise(image);
    // rotate(image);
    // rgb_split(image);
    // mosaic(image);
    // mosaic_mirror(image);
    // glitch(image);
    // pixel_sorting(image);
    // rows_sorting(image);
    // random_sorting(image);
    // vortex(image).save("output/test.png");
    // box_blur(image);
    // sharpen(image);
    // outline(image);
    emboss(image);

    image.save("output/test.png");
}