#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>
#include <ostream>

class Bitmap
{
public:
    Bitmap(int n);

    uint64_t & map();
    uint64_t map() const;

    Bitmap operator& (const Bitmap &bm);
    Bitmap operator| (const Bitmap &bm);
    Bitmap operator^ (const Bitmap &bm);
    Bitmap operator>>(const Bitmap &bm);
    Bitmap operator<<(const Bitmap &bm);

    Bitmap operator& (const int n);
    Bitmap operator| (const int n);
    Bitmap operator^ (const int n);
    Bitmap operator>>(const int n);
    Bitmap operator<<(const int n);

    bool operator[](const int n) const;


private:
    uint64_t map_;
};

std::ostream &operator<<(std::ostream &cout, const Bitmap &bm);

#endif
