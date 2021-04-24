#include <iostream>
#include <iomanip>
#include <string>
#include "Game.h"
#include "Menu.h"

int main()
{
    int option = 0;
    int player1 = BrainRandom;
    int player2 = BrainRandom;

    Database_connector db("root", "root", "Othello", "127.0.0.1");
    db.pull_options(player1, player2);

    while(1)
    {
        if (option == menu) 
        {
            option = main_menu();
        }
        else if (option == play)
        {
            Game game(player1, player2);
            game.play_game();
            char x;
            std::cout << "continue?: ";
            std::cin >> x;
            option = 0;
        }
        else if (option == quit)
        {
            std::cout << "GOODBYE!" << std::endl;
            break;
        }
        else if (option == rules)
        {
            option = 0;
        }
        else if (option == options)
        {
            options_menu(player1, player2);
            option = 0;
        }
        else if (option == previous)
        {
            previous_games(player1, player2);
            // option = 0;
            return 0;
        }
        else
        {
            option = 0;
        }
    }

    return 0;
}
