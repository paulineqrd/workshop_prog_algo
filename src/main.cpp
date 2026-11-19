#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <algorithm>

void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void channels_swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

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

void negatif(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color = glm::vec3{1 - color.r, 1 - color.g, 1 - color.b};
    }
}

void gradient(sil::Image &image)
{
    for (float x{0}; x < image.width() - 1; x++)
    {
        for (float y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = x / image.width();
            image.pixel(x, y).g = x / image.width();
            image.pixel(x, y).b = x / image.width();
        }
    }
}

void mirror(sil::Image &image)
{
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            // Essai mirror
            // image.pixel(x, y) = image.pixel(image.width() - (x + 1), y);

            image.pixel(x, y) = imageRef.pixel(imageRef.width() - (x + 1), y);
        }
    }
}

void noise(sil::Image &image)
{
    // nombre de boucle aléatoire
    // x et y aléatoire
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
            new_image.pixel(new_image.width() - (y + 1), new_image.height() - ((image.width() - (x + 1)) + 1)) = image.pixel(x, y);
        }
    }
    return new_image;
}

// A REVOIR
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

            if (x + 30 < image.width() - 1)
            {
                image.pixel(x, y).b = imageRef.pixel(x + 30, y).b;
            }
        }
    }
}

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

void disque(sil::Image &image)
{
    float rayon = image.width() * 20;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (std::pow((x - image.width() / 2), 2) + std::pow((y - image.height() / 2), 2) <= rayon)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

void circle(sil::Image &image)
{
    float rayon = image.width() * 20;
    float thickness = 1000.f;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (std::pow((x - image.width() / 2), 2) + std::pow((y - image.height() / 2), 2) >= rayon - thickness && std::pow((x - image.width() / 2), 2) + std::pow((y - image.height() / 2), 2) <= rayon + thickness)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

void animation(sil::Image &image)
{
    float rayon = image.width() * 20;
    for (int i{0}; i <= image.width(); i += 5)
    {
        sil::Image imageRef = image;
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                if (std::pow((x - i), 2) + std::pow((y - image.height() / 2), 2) <= rayon)
                {
                    imageRef.pixel(x, y).r = 1.f;
                    imageRef.pixel(x, y).g = 1.f;
                    imageRef.pixel(x, y).b = 1.f;
                }
            }
        }
        imageRef.save("output/animation/animation-" + std::to_string(i) + ".png");
    }
}

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

void mosaique(sil::Image &image)
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

void mosaique_mirror(sil::Image &image)
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

void tri_pixels(sil::Image &image)
{
    std::sort(image.pixels().begin(), image.pixels().end(), [](glm::vec3 const& color1, glm::vec3 const& color2)
    {
        float luminosite1 = color1.r + color1.g + color1.b;
        float luminosite2 = color2.r + color2.g + color2.b;

        return luminosite1 < luminosite2;
    });
}

void tri_lignes(sil::Image &image){


    for(int y {0}; y < image.height(); y++){

        auto begin = image.pixels().begin() + y * image.width();
        auto end = begin + image.width();
        std::sort(begin, end, [](glm::vec3 const& color1, glm::vec3 const& color2){
        float luminosite1 = color1.r + color1.g + color1.b;
        float luminosite2 = color2.r + color2.g + color2.b;

        return luminosite1 < luminosite2;
    });
    }
    
}

int main()
{
    // sil::Image image{300 /*width*/, 200 /*height*/};
    //  gradient(image);

    // sil::Image image{500 /*width*/, 500 /*height*/};
    // rosace(image);

    // rotate(image).save("output/test.png");
    sil::Image image{"images/logo.png"};
    tri_lignes(image);
    image.save("output/test.png");
}