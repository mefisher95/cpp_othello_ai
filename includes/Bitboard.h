#ifndef BITBOARD_H
#define BITBOARD_H


class Bitboard
{
public:
    Bitboard()
    : player0(0), player1(0)
    {}

private:
    uint64_t player0;
    uint64_t player1;
};

#endif
