#include <iostream>
#include "Database_connector.h"
#include "Bitboard.h"

int main()
{
    Bitboard board;
    std::cout << board << std::endl;
    board.make_move(0, 0);

    board.make_move(1, 1);
    board.make_move(1, 2);
    board.make_move(1, 3);

    std::cout << board << std::endl;

    board.make_move(0, 63);
    board.make_move(0, 62);
    board.print();



    // uint64_t n = 0x5555555555555555;
    // std::cout << n << std::endl;
    return 0;

}
