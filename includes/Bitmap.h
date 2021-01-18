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

    Bitmap operator& (const Bitmap &bm) const;
    Bitmap operator| (const Bitmap &bm) const;
    Bitmap operator^ (const Bitmap &bm) const;
    Bitmap operator>>(const Bitmap &bm) const;
    Bitmap operator<<(const Bitmap &bm) const;

    Bitmap operator& (const int n) const;
    Bitmap operator| (const int n) const;
    Bitmap operator^ (const int n) const;
    Bitmap operator>>(const int n) const;
    Bitmap operator<<(const int n) const;

    bool operator[](const int n) const;

    int pop_count() const;

private:
    uint64_t map_;
};

std::ostream &operator<<(std::ostream &cout, const Bitmap &bm);

#endif
