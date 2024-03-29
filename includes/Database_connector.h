#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include "Database.h"

class Database_connector
{
public:
    Database_connector(const std::string &, const std::string &,
                       const std::string &, const std::string &);
   
   void log_options(int player1, int player2);
   void pull_options(int &player1, int &player2);
   void start_game(const std::string&, const std::string&);
   void clear_records();
   int current_game() const;
   void insert_move(const int, const int);

private:
    Database database;
    int current_game_;

    int get_latest_game();

    void create_data();
    void create_games();
    void create_moves();
};


#endif
