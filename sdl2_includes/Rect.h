#ifndef RECT_H
#define RECT_H

#include <iostream>

typedef SDL_Rect Rect;
// class Rect
// {
// public:
//     Rect(int x, int y, int h, int w)
//     :x_(x), y_(y), h_(h), w_(w)
//     {}
//
//     Rect( const SDL_Rect &r)
//     :x_(r.x), y_(r.y), h_(r.h), w_(r.w)
//
//
//     int x() const { return x_; }
//
// private:
//     int x_, y_, h_, w_;
// };

inline std::ostream & operator<<(std::ostream & cout, const Rect & r)
{
	cout << "(" << r.x << "," << r.y << "," << r.w << "," << r.h << ")";
	return cout;
}

#endif
