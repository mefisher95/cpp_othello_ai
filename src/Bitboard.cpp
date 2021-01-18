#include "Bitboard.h"
#include <iostream>

Bitboard::Bitboard(int player0, int player1)
: player0_(player0), player1_(player1)
{}

Bitmap Bitboard::player0() const { return player0_; }
Bitmap Bitboard::player1() const { return player1_; }

int Bitboard::board_popcount() const { return (player0_ | player1_).pop_count(); }
int Bitboard::player0_popcount() const { return player0_.pop_count(); }
int Bitboard::player1_popcount() const { return player1_.pop_count(); }

void Bitboard::make_move(const int player, const int pos)
{
    if ((player0_ | player1_)[pos]) throw BitException(0, ("Invalid Position; position '" + std::to_string(pos) + "' already occupied").c_str());
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
