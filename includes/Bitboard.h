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

    void print(std::vector< DirTuple > possible_moves = std::vector< DirTuple > ()) const;

    void make_move(const bool, const int);
    void make_move(const bool, const uint64_t);

    std::vector< DirTuple > get_actions(const bool player_piece)
    {
        std::vector< DirTuple > all_moves;
        Bitmap empty_map(0), moves(0), empty_positions(~(player0_ | player1_));

        //set players
        Bitmap player, opponent;
        if (player_piece)
        {
            player = player1();
            opponent = player0();
        }
        else
        {
            player = player0();
            opponent = player1();
        }


        // North
        moves = empty_map;
        Bitmap candidates(opponent & (player << 8));
        while (!candidates.is_empty())
        {
            moves = moves | empty_positions & (candidates << 8);
            candidates = opponent & (candidates << 8);
        }
        if (!moves.is_empty()) all_moves.push_back(DirTuple(N, moves));

        // South
        moves = empty_map;
        candidates = opponent & (player >> 8);
        while(!candidates.is_empty())
        {
            moves = moves | empty_positions & (candidates >> 8);
            candidates = opponent & (candidates >> 8);
        }
        if (!moves.is_empty()) all_moves.push_back(DirTuple(S, moves));

        // East
        moves = empty_map;
        candidates = opponent & (player >> 1);
        Bitmap x(E_);

        for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
        {
            x = x | (x >> uint64_t(1));
            moves = moves | empty_positions & (candidates >> uint64_t(1)) & ~(x);
            candidates = opponent & (candidates >> uint64_t(1));
        }
        if(!moves.is_empty()) all_moves.push_back(DirTuple(E, moves));
        std::cout << "moves at E "<< moves << std::endl;

        // West
        moves = empty_map;
        candidates = opponent & (player << 1);
        x = W_;
        for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
        {
            x = x | (x << uint64_t(1));
            moves = moves | empty_positions & (candidates << uint64_t(1)) & ~(x);
            candidates = opponent & (candidates << uint64_t(1));
        }

        if(!moves.is_empty()) all_moves.push_back(DirTuple(W, moves));

        // North West
        moves = empty_map;
        candidates = opponent & (player << 9);
        x = NW_;

        for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
        {
            x = x | (x << uint64_t(9));
            moves = moves | empty_positions & (candidates << uint64_t(9)) & ~(x);
            candidates = opponent & (candidates << uint64_t(9));
        }

        if(!moves.is_empty()) all_moves.push_back(DirTuple(NW, moves));

        // South West
        moves = empty_map;
        candidates = opponent & (player >> 7);
        x = SW_;

        for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
        {
            x = x | (x >> uint64_t(7));
            moves = moves | empty_positions & (candidates >> uint64_t(7)) & ~(x);
            candidates = opponent & (candidates >> uint64_t(7));
        }

        if(!moves.is_empty()) all_moves.push_back(DirTuple(SW, moves));


        // North East
        moves = empty_map;
        candidates = opponent & (player << 7);
        x = NE_;

        for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
        {
            x = x | (x << uint64_t(7));
            moves = moves | empty_positions & (candidates << uint64_t(7)) & ~(x);
            candidates = opponent & (candidates << uint64_t(7));
        }
        if(!moves.is_empty()) all_moves.push_back(DirTuple(NE, moves));



        // South East
        moves = empty_map;
        candidates = opponent & (player >> 9);
        x = SE_;
        for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
        {
            x = x | (x >> uint64_t(9));
            moves = moves | empty_positions & (candidates >> uint64_t(9)) & ~(x);
            candidates = opponent & (candidates >> uint64_t(9));
        }
        if(!moves.is_empty()) all_moves.push_back(DirTuple(SE, moves));

        std::vector< DirTuple > seperate_moves;

        for (int i = 0; i < all_moves.size(); ++i)
        {
            std::vector< int > moves_as_indicies = extract_moves(all_moves[i][1]);

            for (int k = 0; k < moves_as_indicies.size(); ++k)
            {
                if (should_add_index(seperate_moves, moves_as_indicies[k]))
                seperate_moves.push_back(DirTuple(direction(all_moves[i][0]), moves_as_indicies[k]));
            }
        }

        return seperate_moves;
    }



private:
    Bitmap player0_;
    Bitmap player1_;
    Bitmap E_, W_, NE_, NW_, SE_, SW_;


    std::vector< int > extract_moves(Bitmap move_as_map);

    bool should_add_index(std::vector< DirTuple > &seperate_moves, int index)
    {
        for (int i = 0; i < seperate_moves.size(); ++i)
        {
            if (seperate_moves[i][1] == index) return false;
        }
        return true;
    }
};

std::ostream &operator<<(std::ostream &cout, const Bitboard &bitboard);
std::ostream &operator<<(std::ostream &cout, const DirTuple &tuple);
std::ostream &operator<<(std::ostream &cout, const std::vector< DirTuple > dt);

#endif
