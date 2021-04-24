#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <unordered_map>
#include <string>

#include "Bitmap.h"


class Heuristic
{
public:
    Heuristic()
    :one(1)
    {}

    virtual int score_move(const int action) = 0;
    virtual int score_board(const Bitboard &board, const bool player) = 0;

    virtual void print() const = 0;
    virtual std::ostream& print(std::ostream &stm) const = 0;


protected:
    const Bitmap one;

};

std::ostream& operator<<(std::ostream& stm, const Heuristic& h)
{ return h.print(stm); } 

class RegionBaseWeights: public Heuristic
{
public:
    RegionBaseWeights()
    :Heuristic(), region_corner(0x8100000000000081),
    region_guard(0x42C300000000C342), region_backedge(0x3C0081818181003C),
    region_frontedge(0x3C424242423C00), region_center(0x3C3C3C3C0000)
    {
        region_weights["corner"] = 5;
        region_weights["backedge"] = 2;
        region_weights["center"] = 1;
        region_weights["frongedge"] = -2;
        region_weights["guard"] = -5;
    }

    int score_move(const int action)
    {
        if (!(region_corner & one << action).is_empty()) return region_weights["corner"];
        if (!(region_guard & one << action).is_empty()) return region_weights["guard"];
        if (!(region_backedge & one << action).is_empty()) return region_weights["backedge"];
        if (!(region_frontedge & one << action).is_empty()) return region_weights["frongedge"];
        if (!(region_center & one << action).is_empty()) return region_weights["center"];
        throw HeuristicException(0, ("Invalid Heuristic region with move \""
                                    + std::to_string(action) + "\"").c_str());
        return 0;
    }

    int score_board(const Bitboard &board, const bool player)
    {
        int score = 0;
        if (player)
        {
            score += (board.player1() & region_corner).pop_count() * region_weights["corner"];
            score += (board.player1() & region_guard).pop_count() * region_weights["guard"];
            score += (board.player1() & region_center).pop_count() * region_weights["center"];
            score += (board.player1() & region_backedge).pop_count() * region_weights["backedge"];
            score += (board.player1() & region_frontedge).pop_count() * region_weights["frontedge"];
        }
        else
        {
            score += (board.player0() & region_corner).pop_count() * region_weights["corner"];
            score += (board.player0() & region_guard).pop_count() * region_weights["guard"];
            score += (board.player0() & region_center).pop_count() * region_weights["center"];
            score += (board.player0() & region_backedge).pop_count() * region_weights["backedge"];
            score += (board.player0() & region_frontedge).pop_count() * region_weights["frontedge"];
        }
        return score;
    }

    void print() const
    {
        for (int i = 0; i < 64; ++i)
        {
            if (i > 0 && !(i % 8)) std::cout << std::endl;
            if (region_corner[i]) std::cout << 'x';
            if (region_guard[i]) std::cout << '*';
            if (region_backedge[i]) std::cout << '^';
            if (region_frontedge[i]) std::cout << '+';
            if (region_center[i]) std::cout << '%';
        }
        std::cout << std::endl;
    }

    std::ostream& print(std::ostream& stm) const
    { return stm << "Heuristic : RegionBasedWeights"; }
private:
    const Bitmap region_corner;
    const Bitmap region_backedge;
    const Bitmap region_frontedge;
    const Bitmap region_guard;
    const Bitmap region_center;
    std::unordered_map< std::string, int > region_weights;
};



#endif
