#include "Bitmap.h"

Bitmap::Bitmap(int n)
: map_(n)
{}

uint64_t& Bitmap::map() { return map_; }
uint64_t Bitmap::map() const { return map_; }

Bitmap Bitmap::operator& (const Bitmap &bm) const { return map() &  bm.map(); }
Bitmap Bitmap::operator| (const Bitmap &bm) const { return map() | bm.map(); }
Bitmap Bitmap::operator^ (const Bitmap &bm) const { return map() ^  bm.map(); }
Bitmap Bitmap::operator>>(const Bitmap &bm) const { return map() >> bm.map(); }
Bitmap Bitmap::operator<<(const Bitmap &bm) const { return map() << bm.map(); }

Bitmap Bitmap::operator& (const int n) const { return map() & n; }
Bitmap Bitmap::operator| (const int n) const { return map() | n; }
Bitmap Bitmap::operator^ (const int n) const { return map() ^ n; }
Bitmap Bitmap::operator>>(const int n) const { return map() >> n; }
Bitmap Bitmap::operator<<(const int n) const { return map() << n; }

bool Bitmap::operator[](const int n) const { return (map() >> n) % 2; }

int Bitmap::pop_count() const
{
    int count = 0;
    uint64_t n = map_;
    n = (n & 0x5555555555555555) + ((n & 0xAAAAAAAAAAAAAAAA) >> 1);
    n = (n & 0x3333333333333333) + ((n & 0xCCCCCCCCCCCCCCCC) >> 2);
    n = (n & 0x0F0F0F0F0F0F0F0F) + ((n & 0xF0F0F0F0F0F0F0F0) >> 4);
    n = (n & 0x00FF00FF00FF00FF) + ((n & 0xFF00FF00FF00FF00) >> 8);
    n = (n & 0x0000FFFF0000FFFF) + ((n & 0xFFFF0000FFFF0000) >> 16);
    n = (n & 0x00000000FFFFFFFF) + ((n & 0xFFFFFFFF00000000) >> 32);
    count += n;
    return count;
}

std::ostream &operator<<(std::ostream &cout, const Bitmap &bm)
{
    uint64_t map = bm.map();

    for (int i = 0; i < 8; ++i)
    {
        cout << '[';
        for (int k = 0; k < 8; ++k)
        {
            cout << map % 2;
            map = map >> 1;

        }
        cout << ']';
    }
    return cout;
}
