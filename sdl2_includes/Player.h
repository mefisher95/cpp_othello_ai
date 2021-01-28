#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Game_Object.h"

class Player: public Game_Object
{
public:
    Player(int x, int y, Surface *surface, std::string filename)
    : surface_(surface)
    {
        image_ = new Image(filename);
        rect_ = image_->get_rect();
        rect_.x = x;
        rect_.y = y;
    }

    ~Player()
    {
        delete image_;
    }

    // void set_rect(const Rect &rect)
    // {
    //     x_ = rect.x;
    //     y_ = rect.y;
    //     w_ = rect.w;
    //     h_ = rect.h;
    // }
    //
    // void set_rect(int x, int y, int w, int h)
    // {
    //     x_ = x;
    //     y_ = y;
    //     w_ = w;
    //     h_ = h;
    // }

    void draw()
    {
        surface_->put_image(image_, rect_);
    }
private:
    Surface *surface_;
    Image *image_;
    Rect rect_;

};

#endif
