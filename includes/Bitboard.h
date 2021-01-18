#ifndef BITBOARD_H
#define BITBOARD_H

#include <ostream>
#include "Bitmap.h"
#include "Exception.h"




class Bitboard
{
public:
    Bitboard(int = 0, int = 0);

    Bitmap player0() const;
    Bitmap player1() const;

    void make_move(const int, const int);

private:
    Bitmap player0_;
    Bitmap player1_;
};

std::ostream &operator<<(std::ostream &cout, const Bitboard &bitboard);

#endif
