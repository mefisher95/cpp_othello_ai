#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <vector>
#include "Bitmap.h"
#include "Exception.h"

enum direction {N, S, E, W, NW, NE, SW, SE};

class DirTuple
{
public:
    DirTuple(const direction dir, const Bitmap &pos)
    :dir_(dir), pos_(pos.map())//, E(Bitmap(somenumber))
    {

    }

    uint64_t operator[](const bool n) const { return (n ? pos_ : dir_); }
    direction dir() const { return dir_; }
    uint64_t pos() const { return pos_; }

private:
    direction dir_;
    uint64_t pos_;

};

class Bitboard
{
public:
    Bitboard(uint64_t = 0, uint64_t = 0);

    Bitmap player0() const;
    Bitmap player1() const;

    int board_popcount() const;
    int player0_popcount() const;
    int player1_popcount() const;

    void print(std::vector< DirTuple > = std::vector< DirTuple > ()) const;
    void make_move(const bool, const int);
    void make_move(const bool, const DirTuple &);

    std::vector< DirTuple > get_actions(const bool);

private:
    Bitmap player0_;
    Bitmap player1_;
    const Bitmap E_(uint64_t(0x8080808080808080));
    const Bitmap W_(uint64_t(0x101010101010101));
    const Bitmap NE_(uint64_t(0x80808080808080FF));
    const Bitmap NW_(uint64_t(0x1010101010101FF));
    const Bitmap SE_(uint64_t(0xFF80808080808080));
    const Bitmap SW_(uint64_t(0xFF01010101010101));
    const int n = 8;

    std::vector< int > extract_moves(Bitmap);

    bool should_add_index(std::vector< DirTuple > &, int);
};

std::ostream &operator<<(std::ostream &cout, const Bitboard &bitboard);
std::ostream &operator<<(std::ostream &cout, const DirTuple &tuple);
std::ostream &operator<<(std::ostream &cout, const std::vector< DirTuple > dt);

#endif
