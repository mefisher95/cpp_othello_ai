#ifndef BRAIN_H
#define BRAIN_H

#include <ctime>
#include <cstdlib>
#include "Heuristic.h"

class Brain
{
public:
    Brain()
    {}

    virtual void print() { std::cout << "this is a brain" << std::endl; }
    virtual DirTuple make_move(const std::vector< DirTuple >&,
                               const Bitboard &board) const = 0;

protected:
    Heuristic* heuristic_;
    int convert_char(std::string &input) const
    {
        int character = int(input[0]);
        if (character > 96 && character < 105) return character - 97;
        else if (character > 64 && character < 73) return character - 65;
        return -1;
    }

    int convert_pos(int x, int y) const
    {
        return 8 * y + x;
    }

    DirTuple assign_position(const std::vector< DirTuple > &available_pos, const int &move) const
    {
        for (int i = 0; i < available_pos.size(); ++i)
        {
            if (move == available_pos[i][1]) return available_pos[i];
        }
        return DirTuple(N, -1);
    }

};

class User: public Brain
{
public:
    User()
    {}

    void print() { std::cout << "this is a random brain" << std::endl; }

    DirTuple make_move(const std::vector< DirTuple >& actions,
                       const Bitboard &board) const
    {
        if (!actions.size()) return DirTuple(N, -1);
        DirTuple pos(N, -1);
        while(1)
        {
            std::string input0;
            int input1;
            std::cout << "Enter input: ";
            std::cin >> input0 >> input1;
            int input0_int = convert_char(input0);

            if (input0.size() > 1 || input0_int == -1 || input1 > 7)
            {
                std::cout << "invalid input" << std::endl;
                continue;
            }

            pos = assign_position(actions, convert_pos(input0_int, input1));

            if (pos[1] == -1)
            {
                std::cout << "invalid move" << std::endl;
                continue;
            }

            return pos;
        }
    }
};

class Random: public Brain
{
public:
    Random()
    {
        srand((unsigned int) time(NULL));
    }

    void print() { std::cout << "this is a random brain" << std::endl; }

    DirTuple make_move(const std::vector< DirTuple >& actions,
                       const Bitboard &board) const
    {
        if (!actions.size()) return DirTuple(N, -1);
        return actions[rand() % actions.size()];
    }
};

class HeuristicOnly: public Brain
{
public:
    HeuristicOnly()
    {
        heuristic_ = new RegionBaseWeights();
    }
    ~HeuristicOnly() { delete heuristic_; }

    void print() { std::cout << "this is a random only brain" << std::endl; }

    DirTuple make_move(const std::vector< DirTuple >& actions,
                       const Bitboard &board) const
   {
       DirTuple action = actions[0];
       int weight =  heuristic_->score_move(action[1]);
       for (int i = 1; i < actions.size(); ++i)
       {
            DirTuple newaction = actions[i];
            int newweight = heuristic_->score_move(newaction[1]);
            if ( newweight > weight)
            {
                action = newaction;
                weight = newweight;
            }
       }
       return action;
   }
};



#endif
