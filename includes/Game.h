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
    Game(int player0_brain = 0, int player1_brain = 0)
    :player_turn(1)
    {
        switch (player0_brain)
        {
            case 0:
            p0brain = new User();
            break;

            case 1:
            p0brain = new Random();
            break;
        }
        switch (player1_brain)
        {
            case 0:
            p1brain = new User();
            break;

            case 1:
            p1brain = new Random();
            break;
        }
    }
    ~Game()
    {
        delete p0brain;
        delete p1brain;
    }

    int get_current_player() const { return player_turn; }

    void play_game()
    {
        print_board();

        int move = get_current_player();
        for (int i = 0; i < 10; ++i)
        {
            make_move(move);
            move = !move;
            print_board();
        }


    }

    void make_move(int move)
    {
        DirTuple pos(N, -1);
        move ? pos = p1brain->make_move(board.get_actions(move)):
               pos = p0brain->make_move(board.get_actions(move));

        board.make_move(move, pos);

        // wrap up
        black_piece_count = board.player0_popcount();
        white_piece_count = board.player1_popcount();
    }



    void print_board() { board.print(); }

private:
    const Brain* p0brain;
    const Brain* p1brain;
    Bitboard board;

    int player_turn;
    int black_piece_count, white_piece_count;

    int convert_char(std::string &input)
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

    DirTuple assign_position(const std::vector< DirTuple > &available_pos, const int &move)
    {
        for (int i = 0; i < available_pos.size(); ++i)
        {
            if (move == available_pos[i][1]) return available_pos[i];
        }
        return DirTuple(N, -1);
    }
};

#endif
