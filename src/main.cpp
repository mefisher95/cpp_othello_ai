#include <iostream>
#include "Game.h"
#include "Bitboard.h"


int main()
{
    Game game(0, 1);
    game.make_move();
    // std::cout << game.get_current_player() << std::endl;
    game.print_board();

    return 0;

}
