#include <iostream>
#include "Database_connector.h"

Database_connector::Database_connector(const std::string &user,
                                       const std::string &password,
                                       const std::string &db,
                                       const std::string &host)
: database(Database(user, password, "", host))
{
    if (database.is_database(db))
    {
        database.use_database(db);
    }
    else
    {
        database.create_database(db);
        database.use_database(db);
        create_data();
        create_games();
        create_moves();
    }

    if (!database.is_table("Games")) create_games();
    if (!database.is_table("Moves")) create_moves();
    if (!database.is_table("Options_data")) create_data();
}


    void Database_connector::log_options(int player1, int player2)
    {
        database.drop_table("Options_data");
        create_data();
        STRING_VEC fields;
        RESULT_VEC arg_vect;
        std::vector < std::string > arg;
        arg.push_back(std::to_string(player1));
        arg.push_back(std::to_string(player2));
        arg_vect.push_back(arg);

        fields.push_back("player1");
        fields.push_back("player2");
        database.insert_row("Options_data", fields, arg_vect);
    }
   void Database_connector::pull_options(int &player1, int &player2)
   {
       RESULT_VEC results = database.select("*", "Options_data");
       
       player1 = std::stoi(results[0][0]);
       player2 = std::stoi(results[0][1]);
   }

void Database_connector::start_game(const std::string &p0brain,
                                    const std::string &p1brain)
{
    STRING_VEC fields;
    RESULT_VEC arg_vect;
    std::vector < std::string > arg;
    arg.push_back("NULL");
    arg.push_back("\"" + p0brain + "\"");
    arg.push_back("\"" + p1brain + "\"");
    arg_vect.push_back(arg);

    fields.push_back("winner");
    fields.push_back("p0brain");
    fields.push_back("p1brain");


    database.insert_row("Games", fields, arg_vect);
    current_game_ = get_latest_game();
}

void Database_connector::clear_records()
{
    std::string db = database.current_database();

    database.drop_table("Moves");
    database.drop_table("Games");
    database.drop_table("Options_data");
    
    create_games();
    create_moves();
}

int Database_connector::current_game() const { return current_game_; }


void Database_connector::insert_move(const int move, const int player)
{
     STRING_VEC fields;
     fields.push_back("game_id");
     fields.push_back("move");
     fields.push_back("player");
     RESULT_VEC arg_vect;
     STRING_VEC argument;
     argument.push_back(std::to_string(current_game()));
     argument.push_back(std::to_string(move));
     argument.push_back(std::to_string(player));
     arg_vect.push_back(argument);

     database.insert_row("Moves", fields, arg_vect);
}

int Database_connector::get_latest_game()
{
    return std::stoi(database.select("MAX(id)", "Games")[0][0]);
}

void Database_connector::create_data()
{
    STRING_VEC fields;
    fields.push_back("player1 INT");
    fields.push_back("player2 INT");
    database.create_table("Options_data", fields);
}
void Database_connector::create_games()
{
    STRING_VEC fields;
    fields.push_back("id INT AUTO_INCREMENT");
    fields.push_back("winner INT");
    fields.push_back("p0brain VARCHAR(100)");
    fields.push_back("p1brain VARCHAR(100)");
    fields.push_back("primary key (id)");
    database.create_table("Games", fields);
}

void Database_connector::create_moves()
{
    STRING_VEC fields;
    fields.push_back("id INT AUTO_INCREMENT");
    fields.push_back("game_id INT not null");
    fields.push_back("move TINYINT not null");
    fields.push_back("player TINYINT not null");
    fields.push_back("primary key (id)");
    fields.push_back("foreign key (game_id) references Games(id)");
    database.create_table("Moves", fields);
}
