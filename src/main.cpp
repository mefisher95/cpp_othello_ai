#include <iostream>
#include "Database_connector.h"

int main()
{
    Database_connector dbc("root", "root", "Othello", "127.0.0.1");
    // dbc.clear_records();
    dbc.start_game();
    std::cout << dbc.current_game() << std::endl;
    dbc.insert_move(62, 0);
    dbc.insert_move(63, 1);
    dbc.insert_move(1, 0);
    dbc.insert_move(34, 1);
    dbc.clear_records();
    return 0;
}
