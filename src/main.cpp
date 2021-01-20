#include <iostream>
#include "Database_connector.h"
#include "Bitboard.h"



int main()
{

    
    Bitboard board;
    // std::cout << board << std::endl;
    // std::cout << Bitmap(input) << std::endl;
    // Bitboard board;
    // board.print();
    std::vector< DirTuple > moves = board.get_actions(0);
    std::cout << moves << std::endl;
    board.print(moves);
    board.make_move(0, moves[0]);
    board.print(moves);
    //
    // for (int i = 0; i < moves.size(); ++i)
    // {
    //     std::cout << moves[i] << std::endl;
    //     board.make_move(0, moves[i][1]);
    // }
    // board.print();


    return 0;

}
