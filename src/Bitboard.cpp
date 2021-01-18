#include "Bitboard.h"

Bitboard::Bitboard(int player0, int player1)
: player0_(player0), player1_(player1)
{}

Bitmap Bitboard::player0() const { return player0_; }
Bitmap Bitboard::player1() const { return player1_; }

void Bitboard::make_move(const int player, const int pos)
{
    switch (player)
    {
        case 0:
        player0_ = (player0_) | (1 << pos);
        return;

        case 1:
        player1_ = (player1_) | (1 << pos);
        return;
    }
}

std::ostream &operator<<(std::ostream &cout, const Bitboard &bitboard)
{
    cout << bitboard.player0();
    cout << '\n';
    cout << bitboard.player1();
    return cout;
}
