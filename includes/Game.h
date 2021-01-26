#ifndef GAME_H
#define GAME_H

#include <string>
#include "Bitboard.h"
#include "Exception.h"
#include "util.h"
#include "Brain.h"

class Game
{
public:
    Game(int player0_brain = BrainRandom, int player1_brain = BrainRandom)
    :player_turn(1)
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
        print_board();
        int turn = 0;
        while(!stalemate())
        {
            std::cout << "TURN: " << turn << std::endl;
            player_turn ? std::cout << "BLACK(@)" << std::endl
                        : std::cout << "WHITE(0)" << std::endl;
            make_move(player_turn);
            player_turn = !player_turn;
            print_board();
            ++turn;
        }
        std::cout << "Black Count: " << board.player0_popcount() << std::endl;
        std::cout << "White Count: " << board.player1_popcount() << std::endl;
    }



    void print_board() { board.print(); }

private:
    const Brain* p0brain;
    const Brain* p1brain;
    Bitboard board;

    int player_turn;
    int black_piece_count, white_piece_count;

    void make_move(int move)
    {
        DirTuple pos(N, -1);
        move ? pos = p1brain->make_move(board.get_actions(move), board):
               pos = p0brain->make_move(board.get_actions(move), board);

        if (pos[1] == -1) return;
        board.make_move(move, pos);

        // wrap up
        black_piece_count = board.player0_popcount();
        white_piece_count = board.player1_popcount();
    }

    bool stalemate()
    {
        return !(board.get_actions(0).size() || board.get_actions(1).size());
    }
};

#endif
