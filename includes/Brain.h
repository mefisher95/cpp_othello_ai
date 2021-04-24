#ifndef BRAIN_H
#define BRAIN_H

#include <ctime>
#include <cstdlib>
#include <string>
#include "Heuristic.h"
#include "BH_Queue.h"

class Brain
{
public:
    Brain()
    {}

    // virtual void print() { std::cout << "this is a brain" << std::endl; }
    virtual std::ostream& print(std::ostream &stm) const = 0;
    virtual std::string type() const = 0;
    virtual DirTuple make_move(const int player,
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

std::ostream& operator<<(std::ostream& stm, const Brain& b)
{ return b.print(stm); } 

class User: public Brain
{
public:
    User()
    {}

    // void print() { std::cout << "this is a random brain" << std::endl; }
    std::ostream& print(std::ostream& stm) const
    { return stm << "< Brain: User >"; }
    std::string type() const { return "User"; }

    DirTuple make_move(const int player,
                       const Bitboard &board) const
    {
        Bitboard temp(board);
        const std::vector< DirTuple > actions = temp.get_actions(player);
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
    Random() { srand((unsigned int) time(NULL)); }

    // void print() { std::cout << "this is a random brain" << std::endl; }
    std::string type() const { return "Random"; }
    std::ostream& print(std::ostream& stm) const
    { return stm << "< Brain: Random >"; }

    DirTuple make_move(const int player,
                       const Bitboard &board) const
    {
        Bitboard temp(board);
        const std::vector< DirTuple > actions = temp.get_actions(player);
        if (!actions.size()) return DirTuple(N, -1);
        return actions[rand() % actions.size()];
    }
};

class HeuristicOnly: public Brain
{
public:
    HeuristicOnly() { heuristic_ = new RegionBaseWeights(); }
    ~HeuristicOnly() { delete heuristic_; }

    // void print() { std::cout << "this is a random only brain" << std::endl; }
    std::string type() const { return "HeuristicOnly"; }
    std::ostream& print(std::ostream& stm) const
    { return stm << "< Brain: HeuristicOnly; " << *heuristic_ << " >"; }

    DirTuple make_move(const int player,
                       const Bitboard &board) const
    {
        Bitboard temp(board);
        const std::vector< DirTuple > actions = temp.get_actions(player);
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

class Minimax: public Brain
{
public:
    Minimax() { heuristic_ = new RegionBaseWeights(); }
    ~Minimax() { delete heuristic_; }

    std::string type() const { return "Minimax"; }
    std::ostream& print(std::ostream& stm) const
    { return stm << "< Brain: Minimax; " << *heuristic_ << " >"; }

    BH_Queue generate_queue(const std::vector< DirTuple >& actions, bool player) const
    {
        BH_Queue queue = BH_Queue();
    
        for (int i = 0; i < actions.size(); ++i)
        {
            int weight =  heuristic_->score_move(actions[i][1]);
            player ? weight : -weight;
            queue.insert(actions[i], weight);
        }

        return queue;
    }

    DirTuple make_move(const int player,
                       const Bitboard &board) const
    {
        Bitboard temp(board);
        const std::vector< DirTuple > actions = temp.get_actions(player);

        const int depth = 11;

        // std::cout << actions << std::endl;
        DirNode action = minimax(player, board, 0, depth, -999999999, 999999999);
        // std::cout << action << std::endl;

        for (int i = 0; i < actions.size(); ++i)
        {
            if (action.tuple == actions[i]) return action.tuple;
        }
        // return queue.pop().tuple;
        throw HeuristicException(1, "invalid move");
    }

    DirNode minimax(int player, const Bitboard &bitboard, 
                    int temp_recursive_depth=0, int max_depth = 0, 
                    int a = -999999999, int b = 999999999) const
    {
        ++temp_recursive_depth;

        if (temp_recursive_depth == max_depth) 
        {
            
            return DirNode(DirTuple(N, Bitmap()), 
                           heuristic_->score_board(bitboard, player),
                           true);
        }

        DirNode best_action(DirTuple(N, Bitmap()), -9999, true);
        if (player == 1)
        {
            int max = -999999999;

            // generates move queue
            Bitboard board(bitboard);
            std::vector< DirTuple > actions = board.get_actions(player);
            BH_Queue queue = generate_queue(actions, player);
            // std::cout << "max queue: " << queue << std::endl;


            for (int i = 0; i < queue.len(); ++i)
            {
                Bitboard resulting_state(bitboard);
                DirNode action = queue.pop();

                resulting_state.make_move(player, action.tuple);
                DirNode v = minimax(0, resulting_state, temp_recursive_depth, max_depth,
                                    a, b);
                
                if (v.none)
                {
                    best_action.weight = action.weight;
                    best_action.tuple = action.tuple;
                }
                else if (v.weight > best_action.weight)
                {
                    best_action.weight = v.weight;
                    best_action.tuple = action.tuple;
                }

                a >= best_action.weight ? a = a : a = best_action.weight;

                if (a >= b) break;
            }
            // std::cout << best_action << " recursive depth " << temp_recursive_depth << std::endl;
            // std::cout << actions << std::endl;
            return best_action;
        }
        else if (player == 0)
        {
            int min = 999999999;
            Bitboard board(bitboard);

            std::vector< DirTuple > actions = board.get_actions(player);
            BH_Queue queue = generate_queue(actions, player);

            for (int i = 0; i < queue.len(); ++i)
            {
                Bitboard resulting_state(bitboard);
                DirNode action = queue.pop();

                resulting_state.make_move(player, action.tuple);
                DirNode v = minimax(1, resulting_state, temp_recursive_depth, max_depth,
                                    a, b);
                
                if (v.none)
                {
                    best_action.weight = action.weight;
                    best_action.tuple = action.tuple;
                }
                else if (v.weight < best_action.weight)
                {
                    best_action.weight = v.weight;
                    best_action.tuple = action.tuple;
                }

                b <= best_action.weight ? b = b : b = best_action.weight;

                if (b <= a) break;
            }

            return best_action;
        }
        return DirNode(DirTuple(N, 0), 99999, true);

    }

private:

    const int MAX = 1;
    const int MIN = 0;
};

// std::ostream &operator<<(std::ostream &cout, const User &u)
// {
//     cout << "< User Brain >";
//     return cout;
// }
// std::ostream &operator<<(std::ostream &cout, const Random &r)
// {
//     cout << "< Random Brain >";
//     return cout;
// }
// std::ostream &operator<<(std::ostream &cout, const HeuristicOnly& ho)
// {
//     cout << "< HeuristicOnly Brain >";
//     return cout;
// }
// std::ostream &operator<<(std::ostream &cout, const Minimax &m)
// {
//     cout << "< Minimax >";
//     return cout;
// }




#endif
