#include "Bitmap.h"

Bitmap::Bitmap(int n)
: map_(n)
{}

uint64_t& Bitmap::map() { return map_; }
uint64_t Bitmap::map() const { return map_; }

Bitmap Bitmap::operator& (const Bitmap &bm) { return map() &  bm.map(); }
Bitmap Bitmap::operator| (const Bitmap &bm) { return map() | bm.map(); }
Bitmap Bitmap::operator^ (const Bitmap &bm) { return map() ^  bm.map(); }
Bitmap Bitmap::operator>>(const Bitmap &bm) { return map() >> bm.map(); }
Bitmap Bitmap::operator<<(const Bitmap &bm) { return map() << bm.map(); }

Bitmap Bitmap::operator& (const int n) { return map() & n; }
Bitmap Bitmap::operator| (const int n) { return map() | n; }
Bitmap Bitmap::operator^ (const int n) { return map() ^ n; }
Bitmap Bitmap::operator>>(const int n) { return map() >> n; }
Bitmap Bitmap::operator<<(const int n) { return map() << n; }

bool Bitmap::operator[](const int n) const { return (map() >> n) % 2; }

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
