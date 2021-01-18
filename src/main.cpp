#include <iostream>
#include "Database_connector.h"
#include "Bitboard.h"

int main()
{
    Bitboard board;
    std::cout << board << std::endl;
    std::cout << std::endl;
    board.make_move(1, 1);
    std::cout << board << std::endl;
    std::cout << std::endl;
    board.make_move(0, 2);
    std::cout << board << std::endl;
    std::cout << std::endl;
    board.make_move(1, 3);
    std::cout << board << std::endl;
    std::cout << std::endl;
    board.make_move(0, 4);
    std::cout << board << std::endl;
    std::cout << std::endl;


    return 0;

}
