#include <iostream>
#include "Game.h"

int main()
{


    // Bitboard board();
    // board.print();
    Game game(BrainHeuristicOnly, BrainRandom);
    game.play_game();
    // Heuristic* h = new RegionBaseWeights();
    // h->print();
    return 0;
}
