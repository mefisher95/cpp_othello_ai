#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include "Database.h"

class Database_connector
{
public:
    Database_connector(const std::string &user, const std::string &password,
                       const std::string &db, const std::string &host)
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
           // database.drop_database(db);
       }

       if (!database.is_table("Games")) create_games();
       if (!database.is_table("Moves")) create_moves();

       // std::cout << "games exists: " << database.is_table("Games") << std::endl;
       // std::cout << "moves exists: " << database.is_table("Moves") << std::endl;
   }

   void start_game()
   {
       STRING_VEC fields;
       RESULT_VEC arg_vect;
       fields.push_back("");
       database.insert_row("Games", fields, arg_vect);
       current_game_ = get_latest_game();
   }

   int current_game() const { return current_game_; }

   void clear_records()
   {
       std::string db = database.current_database();
       // database.drop_database(db);
       // database.create_database(db);
       database.drop_table("Moves");
       database.drop_table("Games");
       create_games();
       create_moves();
   }


private:
    Database database;
    int current_game_;

    int get_latest_game()
    {
        // RESULT_VEC  << std::endl;
        return std::stoi(database.select("MAX(id)", "Games")[0][0]);
    }

    void create_games()
    {
        STRING_VEC fields;
        fields.push_back("id INT AUTO_INCREMENT");
        fields.push_back("winner INT");
        fields.push_back("primary key (id)");
        database.create_table("Games", fields);
    }

    void create_moves()
    {
        STRING_VEC fields;
        fields.push_back("id INT AUTO_INCREMENT");
        fields.push_back("game_id INT not null");
        fields.push_back("primary key (id)");
        fields.push_back("foreign key (game_id) references Games(id)");
        database.create_table("Moves", fields);
    }
};


#endif
