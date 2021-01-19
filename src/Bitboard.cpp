#include "Bitboard.h"
#include <iostream>
#include <cmath>

Bitboard::Bitboard(uint64_t player0, uint64_t player1)
: player0_(player0), player1_(player1),
  W_(uint64_t(72340172838076673)), E_(uint64_t(9259542123273814144)),
  SW_(uint64_t(18374969058471772417)), SE_(uint64_t(18410856566090662016)),
  NW_(uint64_t(72340172838076927)), NE_(uint64_t(9259542123273814271))
{
    make_move(1, 27);
    make_move(0, 28);
    make_move(0, 35);
    make_move(1, 36);
}

Bitmap Bitboard::player0() const { return player0_; }
Bitmap Bitboard::player1() const { return player1_; }

int Bitboard::board_popcount() const { return (player0_ | player1_).pop_count(); }
int Bitboard::player0_popcount() const { return player0_.pop_count(); }
int Bitboard::player1_popcount() const { return player1_.pop_count(); }

void Bitboard::print(std::vector< DirTuple > possible_moves) const
{
    std::cout << possible_moves.size() << std::endl;

    Bitmap candidates;

    for (int i = 0; i < possible_moves.size(); ++i)
    {
        std::cout << possible_moves[i][1] << std::endl;
        candidates = candidates |  (Bitmap(1)<< possible_moves[i][1]);
    }
    Bitmap North;
    Bitmap South;
    Bitmap East;


    std::cout << "+-+-+-+-+-+-+-+-+" << std::endl;
    for (int i = 0; i < 64; ++i)
    {
        std::cout << "|";
        if (i > 0 && !(i % 8)) std::cout << "\n+-+-+-+-+-+-+-+-+\n|";
        if (player0()[i]) std::cout << "O";
        else if (player1()[i]) std::cout << "@";
        else if (candidates[i]) std::cout << "*";
        else std::cout << " ";
    }
    std::cout << "|\n+-+-+-+-+-+-+-+-+" << std::endl;
}

void Bitboard::make_move(const bool player, const int pos)
{
    if (pos < 0 || pos > 63) throw BitException(0, ("Invalid Position; position '" + std::to_string(pos) + "' outside valid range (0-63) (int pos)").c_str());
    if ((player0_ | player1_)[pos]) throw BitException(1, ("Invalid Position; position '" + std::to_string(pos) + "' already occupied (int pos)").c_str());
    switch (player)
    {
        case 0:
        player0_ = (player0_) | (Bitmap(1) << pos);
        return;

        case 1:
        player1_ = (player1_) | (Bitmap(1) << pos);
        return;
    }
}

void Bitboard::make_move(const bool player, const uint64_t pos)
{
    if (pos < 0 || uint64_t(log2(pos)) > 63) throw BitException(2, ("Invalid Position; position '" + std::to_string(log2(pos)) + "' outside valid range (0-63) (Bitmap pos)").c_str());
    if ((player0_ | player1_)[uint64_t(log2(pos))]) throw BitException(3, ("Invalid Position; position '" + std::to_string(log2(pos)) + "' already occupied (int pos)").c_str());

    switch (player)
    {
        case 0:
        player0_ = (player0_ | pos);
        return;

        case 1:
        player1_ = (player1_ | pos);
        return;
    }
}

std::vector< int > Bitboard::extract_moves(Bitmap move_as_map)
{
    std::vector< int > moves_as_indicies;
    int pos = 0;

    while(!move_as_map.is_empty())
    {
        if (move_as_map % 2) moves_as_indicies.push_back(pos);
        ++pos;
        move_as_map = move_as_map >> 1;
    }

    return moves_as_indicies;
}

std::ostream &operator<<(std::ostream &cout, const Bitboard &bitboard)
{
    cout << bitboard.player0();
    cout << '\n';
    cout << bitboard.player1();
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const DirTuple &tuple)
{
    cout << "< "
         << tuple[0]
         << ", "
         << tuple[1]
         << " >";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const std::vector< DirTuple > dt)
{
    cout << "[";
    for (int i = 0; i < dt.size(); ++i)
    {
        cout << dt[i];
        if (i < dt.size() - 1) cout << ", ";
    }
    cout << "]";
    return cout;
}
