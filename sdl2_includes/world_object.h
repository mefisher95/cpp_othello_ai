#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H

#include <iostream>
#include "Game_Object.h"
#include "Surface.h"

// class World_Object: public Game_Object
// {
// public:
//     World_Object(int x, int y, Surface *surface)
//     : x_(x), y_(y), w_(32), h_(32), surface_(surface)
//     {
//         rect_ = Rect(x, y, 32, 48);
//     }
//
//     void set_rect(const Rect &rect)
//     {
//         x_ = rect.x;
//         y_ = rect.y;
//         w_ = rect.w;
//         h_ = rect.h;
//     }
//
//     void set_rect(int x, int y, int w, int h)
//     {
//         x_ = x;
//         y_ = y;
//         w_ = w;
//         h_ = h;
//     }
//
//     void draw()
//     {
//         surface_.put_image(image_, x_, y_, w_, h_);
//     }
// private:
//     int x_;
//     int y_;
//     int w_;
//     int h_;
//     Surface *surface_;
//     Image *image_;
//     Rect rect_;
//
// };

#endif
