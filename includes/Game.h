#ifndef GAME_H
#define GAME_H

#include <string>
#include "Bitboard.h"
#include "Exception.h"
#include "util.h"
#include "Brain.h"
#include "Database_connector.h"

struct move_data
{
    bool player;
    int move;
};

class Game
{
public:
    Game(int player0_brain = BrainRandom, int player1_brain = BrainRandom)
    :player_turn(1), db("root", "", "Othello", "127.0.0.1")
    {
        switch (player0_brain)
        {
            case BrainUser:
            p0brain = new User();
            break;

            case BrainRandom:
            p0brain = new Random();
            break;

            case BrainHeuristicOnly:
            p0brain = new HeuristicOnly();
            break;
        }
        switch (player1_brain)
        {
            case BrainUser:
            p1brain = new User();
            break;

            case BrainRandom:
            p1brain = new Random();
            break;

            case BrainHeuristicOnly:
            p1brain = new HeuristicOnly();
            break;
        }
    }
    ~Game()
    {
        delete p0brain;
        delete p1brain;
    }

    void play_game()
    {
        db.start_game(p0brain->type(), p1brain->type());
        print_board();
        int turn = 0;
        while(1)
        {
            int action_count0 = board.get_actions(0).size();
            int action_count1 = board.get_actions(1).size();

            if (!action_count0 && !action_count1) break;

            if (player_turn)
            {
                if (action_count1)
                {
                    std::cout << "TURN: " << turn << std::endl;
                    std::cout << "BLACK(@)" << std::endl;
                    make_move(player_turn);
                    player_turn = !player_turn;
                    ++turn;
                }
                else
                {
                    player_turn = !player_turn;
                    continue;
                }
            }
            else
            {
                if (action_count0)
                {
                    std::cout << "TURN: " << turn << std::endl;
                    std::cout << "WHITE(0)" << std::endl;
                    make_move(player_turn);
                    player_turn = !player_turn;
                    ++turn;
                }
                else
                {
                    player_turn = !player_turn;
                    continue;
                }
            }
            print_board();
            // std::cout << *p0brain << std::endl;
            // std::cout << *p1brain << std::endl;
        }

        std::cout << "White Count: " 
                  << board.player0_popcount() 
                  << " Braintype: " 
                  << *p0brain
                  << std::endl;

        std::cout << "Black Count: " 
                  << board.player1_popcount() 
                  << " Braintype: "
                  << *p1brain
                  << std::endl;
    }

    void print_board() { board.print(); }

private:
    const Brain* p0brain;
    const Brain* p1brain;
    Bitboard board;
    Database_connector db;

    int player_turn;

    void make_move(int move)
    {
        DirTuple pos(N, -1);
        move ? pos = p1brain->make_move(board.get_actions(move), board):
               pos = p0brain->make_move(board.get_actions(move), board);

        if (pos[1] == -1) return;
        board.make_move(move, pos);
    }
};

#endif
