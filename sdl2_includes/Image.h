#ifndef IMAGE_H
#define IMAGE_H
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Rect.h"

class ImageError
{
public:
    ImageError()
    {
        std::cout << "InvalidImage: There was a problem initializing this "
                  << "Image object with the provided filename."
                  << std::endl;
    }
};

class Image
{
public:
    Image() : image_(NULL)
    {}

    Image(const std::string & filename)
    : image_(SDL_LoadBMP(filename.c_str()))
    {
        if (image_ == NULL)
        {
            throw ImageError();
        }
        rect_ = image_->clip_rect;
    }

    Image(SDL_Surface * surface_image)
    : image_(surface_image)
{}
    ~Image() { SDL_FreeSurface(image_); }

    void load(const std::string & filename)
    {
        image_ = SDL_LoadBMP(filename.c_str());
        if (image_ == NULL)
        {
            throw ImageError();
        }
        rect_ = image_->clip_rect;
    }

    Rect get_rect() const { return rect_; }

    SDL_Surface * get_image() const { return image_ ;}

private:
    SDL_Surface * image_;
    SDL_Rect rect_;
};

#endif
