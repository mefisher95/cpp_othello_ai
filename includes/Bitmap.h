#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>
#include <ostream>

class Bitmap
{
public:
    Bitmap(uint64_t n = 0);
    Bitmap(const Bitmap &bm);

    uint64_t & map();
    uint64_t map() const;

    Bitmap operator~ () const;

    Bitmap operator& (const Bitmap &bm) const;
    Bitmap operator| (const Bitmap &bm) const;
    Bitmap operator^ (const Bitmap &bm) const;
    Bitmap operator>>(const Bitmap &bm) const;
    Bitmap operator<<(const Bitmap &bm) const;
    uint64_t operator%(const Bitmap &bm) const;


    Bitmap operator& (const uint64_t n) const;
    Bitmap operator| (const uint64_t n) const;
    Bitmap operator^ (const uint64_t n) const;
    Bitmap operator>>(const uint64_t n) const;
    Bitmap operator<<(const uint64_t n) const;
    uint64_t operator%(const uint64_t n) const;

    bool operator[](const int n) const;

    int pop_count() const;
    bool is_empty() const;

private:
    uint64_t map_;
};

std::ostream &operator<<(std::ostream &cout, const Bitmap &bm);

#endif
