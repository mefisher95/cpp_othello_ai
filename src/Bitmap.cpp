#include "Bitmap.h"

Bitmap::Bitmap(uint64_t n)
: map_(n)
{}

Bitmap::Bitmap(const Bitmap &bm)
: map_(bm.map())
{}


uint64_t& Bitmap::map() { return map_; }
uint64_t Bitmap::map() const { return map_; }

Bitmap Bitmap::operator~ () const { return ~map(); }

Bitmap Bitmap::operator& (const Bitmap &bm) const { return map() &  bm.map(); }
Bitmap Bitmap::operator| (const Bitmap &bm) const { return map() | bm.map(); }
Bitmap Bitmap::operator^ (const Bitmap &bm) const { return map() ^  bm.map(); }
Bitmap Bitmap::operator>>(const Bitmap &bm) const { return map() >> bm.map(); }
Bitmap Bitmap::operator<<(const Bitmap &bm) const { return map() << bm.map(); }
uint64_t Bitmap::operator%(const Bitmap &bm) const { return map() % bm.map(); }

Bitmap Bitmap::operator& (const uint64_t n) const { return map() & n; }
Bitmap Bitmap::operator| (const uint64_t n) const { return map() | n; }
Bitmap Bitmap::operator^ (const uint64_t n) const { return map() ^ n; }
Bitmap Bitmap::operator>>(const uint64_t n) const { return map() >> n; }
Bitmap Bitmap::operator<<(const uint64_t n) const { return map() << n; }
uint64_t Bitmap::operator%(const uint64_t n) const { return map() % n; }

bool Bitmap::operator[](const int n) const { return (map() >> n) % 2; }

int Bitmap::pop_count() const
{
    int count = 0;
    uint64_t n = map_;
    n = (n & 0X5555555555555555) + ((n & 0XAAAAAAAAAAAAAAAA) >> 1);
    n = (n & 0X3333333333333333) + ((n & 0XCCCCCCCCCCCCCCCC) >> 2);
    n = (n & 0X0F0F0F0F0F0F0F0F) + ((n & 0XF0F0F0F0F0F0F0F0) >> 4);
    n = (n & 0X00FF00FF00FF00FF) + ((n & 0XFF00FF00FF00FF00) >> 8);
    n = (n & 0X0000FFFF0000FFFF) + ((n & 0XFFFF0000FFFF0000) >> 16);
    n = (n & 0X00000000FFFFFFFF) + ((n & 0XFFFFFFFF00000000) >> 32);
    count += n;
    return count;
}

bool Bitmap::is_empty() const { return !pop_count(); }

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
