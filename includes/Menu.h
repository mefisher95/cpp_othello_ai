#ifndef MENU_H
#define MENU_H

#include "util.h"
#include "Database_connector.h"

void print_screen()
{
    std::ostringstream stringStream;
    stringStream << " \u001b[1J \033[" << 0 << ";0H";
    std::string output = stringStream.str();
    int len = output.size();
    std::string erase = std::string(len, '\b');
    std::cout << erase << output << std::endl;
}

int main_menu_input()
{
    while(1)
    {
        int input;
        std::cout << "INPUT >> ";
        std::cin >> input;

        if (input ==  0) return play;
        else if (input == 1) return rules;
        else if (input == 2) return options;
        else if (input == 3) return previous;
        else if (input == 4) return quit;

        print_screen();
        std::cout << "+-+-+-+-+-+-+-+-+\n"
                << "| | | | | | | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "| | | | | | | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "| | | | | | | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "|M|I|K|E|S| | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "| |O|T|H|E|L|L|O|\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "| | | | | | | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "| | | | | | | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "| | | | | | | | |\n"
                << "+-+-+-+-+-+-+-+-+\n"
                << "\n"
                << "\n"
                << "PLAY    [0] RULES          [1]\n" 
                << "OPTIONS [2] PREVIOUS GAMES [3]\n"
                << "QUIT    [4]\n"
                << std::endl;
    }
}


int main_menu()
{
    print_screen();
    std::cout << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "|M|I|K|E|S| | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| |O|T|H|E|L|L|O|\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "| | | | | | | | |\n"
              << "+-+-+-+-+-+-+-+-+\n"
              << "\n"
              << "\n"
              << "PLAY    [0] RULES          [1]\n" 
              << "OPTIONS [2] PREVIOUS GAMES [3]\n"
              << "QUIT    [4]\n"
              << std::endl;
    return main_menu_input();
}

int options_menu(int &player1, int &player2)
{
    bool alter_one = false;
    bool alter_two = false;
    int option;

    while(1)
    {
        print_screen();

        std::cout << "OPTIONS:\n"
                << "\n"
                << "Use this screen to change the AI"
                << "brain.\n"
                << "\n";
        std::cout << "PLAYER 1 BRAIN: ";
        switch (player1)
        {
        case BrainRandom:
            std::cout << "Random Brain" << std::endl;
            break;

        case BrainHeuristicOnly:
            std::cout << "Heuristic Only Brain" << std::endl;
            break;

        case BrainMinimax:
            std::cout << "Minimax Brain" << std::endl;
            break;

        case BrainUser:
            std::cout << "User Brain" << std::endl;
            break;
        
        default:
            break;
        }

        std::cout << "PLAYER 2 BRAIN: ";
        switch (player2)
        {
        case BrainRandom:
            std::cout << "Random Brain" << std::endl;
            break;

        case BrainHeuristicOnly:
            std::cout << "Heuristic Only Brain" << std::endl;
            break;

        case BrainMinimax:
            std::cout << "Minimax Brain" << std::endl;
            break;

        case BrainUser:
            std::cout << "User Brain" << std::endl;
            break;
        
        default:
            break;
        }
        if (!(alter_one || alter_two))
        {
            std::cout << "\nChange Player Brain:\n"
                    << "Player 1 [0]  player 2 [1]\n"
                    << "Return   [2]\n"
                    << std::endl;
            std::cout << "ENTER: ";
            std::cin >> option;
            if (option == 0 ) alter_one = true;
            if (option == 1 ) alter_two = true;
            if (option == 2 ) 
            {
                Database_connector db("root", "root", "Othello", "127.0.0.1");
                db.log_options(player1, player2);
                return 0;
            }
            else continue;
        }
        else if (alter_one)
        {
            std::cout << "\nChoose Brain: Player1\n"
                      << "Random Brain         [0]\n"
                      << "Heuristic Only Brain [1]\n"
                      << "Minimax Brain        [2]\n"
                      << "User Brain           [3]\n"
                      << "Cancel               [4]\n"
                      << std::endl;
            alter_one = false;
            std::cout << "ENTER: ";
            std::cin >> option;
            if (option == 0 ) player1 = BrainRandom;
            if (option == 1 ) player1 = BrainHeuristicOnly;
            if (option == 2 ) player1 = BrainMinimax;
            if (option == 3 ) player1 = BrainUser;
            if (option == 4 ) alter_one = false;
            
            continue;
        }
        else if (alter_two)
        {
            std::cout << "\nChoose Brain: Player2\n"
                      << "Random Brain         [0]\n"
                      << "Heuristic Only Brain [1]\n"
                      << "Minimax Brain        [2]\n"
                      << "User Brain           [3]\n"
                      << "Cancel               [4]\n"
                      << std::endl;
            alter_one = false;
            std::cout << "ENTER: ";
            std::cin >> option;
            if (option == 0 ) player2 = BrainRandom;
            if (option == 1 ) player2 = BrainHeuristicOnly;
            if (option == 2 ) player2 = BrainMinimax;
            if (option == 3 ) player2 = BrainUser;
            if (option == 4 ) alter_two = false;
            
            continue;
        }
        
    }
    return 0;
}

int previous_games(int &player1, int &player2)
{
    Database_connector db("root", "root", "Othello", "127.0.0.1");
    db.log_options(player1, player2);
    db.pull_options(player1, player2);
    return 0;
}
#endif