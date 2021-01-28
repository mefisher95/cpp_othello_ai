#include <iostream>
#include "Game.h"
#include "Database_connector.h"

int main()
{


    // Bitboard board();
    // board.print();
    
    // Database db0("root", "", "", "127.0.0.1");
    // std::cout << db0.show_databases() << std::endl;
    Game game(BrainHeuristicOnly, BrainRandom);
    game.play_game();
    // Heuristic* h = new RegionBaseWeights();
    // h->print();
    return 0;
}
