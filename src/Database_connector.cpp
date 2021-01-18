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
        std::cout << database.current_database() << std::endl;
        create_games();
        create_moves();
    }

    if (!database.is_table("Games")) create_games();
    if (!database.is_table("Moves")) create_moves();
}


void Database_connector::start_game()
{
    STRING_VEC fields;
    RESULT_VEC arg_vect;
    fields.push_back("");
    database.insert_row("Games", fields, arg_vect);
    current_game_ = get_latest_game();
}

void Database_connector::clear_records()
{
    std::string db = database.current_database();
    // database.drop_database(db);
    // database.create_database(db);
    database.drop_table("Moves");
    database.drop_table("Games");
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

void Database_connector::create_games()
{
    STRING_VEC fields;
    fields.push_back("id INT AUTO_INCREMENT");
    fields.push_back("winner INT");
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
