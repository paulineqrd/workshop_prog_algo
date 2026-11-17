#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>

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

void disque(sil::Image &image){
    float rayon = image.width()*10;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++){
            if (std::pow((x - image.width()/2), 2) + std::pow((y - image.height()/2), 2) <= rayon)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

int main()
{
    //sil::Image image{300 /*width*/, 200 /*height*/};
    // gradient(image);

    sil::Image image{500 /*width*/, 500 /*height*/};
    disque(image);

    // rotate(image).save("output/test.png");
    // sil::Image image{"images/photo.jpg"};
    // brightness(image);
    image.save("output/test.png");
}