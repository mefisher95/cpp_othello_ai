#include <iostream>
#include "Database.h"

////////////////////////////////////////////////////////////////////////////////
// Database Class
//==============================================================================
// Provides a wrapper for most common mysql commands in c++.
//==============================================================================
// Methods:
//  current_database() -> std::string
//  use_database(std::string) -> void
//  create_database(std::string) -> void
//  show_databases() -> STRING_VEC
//  is_database(std::string) -> bool
//
//  create_table(std::string, STRING_VEC) -> void
//  drop_table(std::string) -> void
//  desc_table(std::string) -> RESULT_VEC
//
//  insert_row(std::string, STRING_VEC, RESULT_VEC) -> void
//  update_row(std::string, std::string, std::string) -> void
//  delete_row(std::string, std::string) -> void
//
//  select(std::string, std::string) -> RESULT_VEC
//
// Private Methods:
//
//  commit(const char*) -> MYSQL_RES*
//
//==============================================================================


Database::Database(std::string user, std::string pasw,
                   std::string database, std::string host)
:user_(user), password_(pasw), database_(database), host_(host)
{}

std::string Database::current_database() const { return database_; }
void Database::use_database(const std::string &newdatabase)
{
    if (is_database(newdatabase)) database_ = newdatabase;
    else throw MySQLException(3, ("\"" + newdatabase + "\" is not a valid Database").c_str());
}

void Database::create_database(const std::string &name)
{
    std::string sql = "CREATE DATABASE " + std::string(name) + ";";
    mysql_free_result(commit(sql.c_str()));
}

void Database::drop_database(const std::string &name)
{
    std::string sql = "DROP DATABASE " + std::string(name) + ";";
    mysql_free_result(commit(sql.c_str()));
}

STRING_VEC Database::show_databases()
{
    std::string sql = "SHOW DATABASES;";
    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;

    std::vector<std::string> results;

    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        results.push_back(result_row[0]);
    }

    return results;
}

bool Database::is_database(const std::string &name)
{
    std::vector<std::string> databases = show_databases();

    for (int i = 0; i < databases.size(); ++i)
    {
        if (databases[i] == name) return true;
    }
    return false;
}

void Database::create_table(const std::string &name, const STRING_VEC &fields)
{
    std::string sql = "CREATE TABLE ";
    sql += std::string(name) + "(";

    for (int i = 0; i < fields.size(); ++i)
    {
        sql.append(fields[i]);
        if (i < fields.size() - 1) sql.append(",");
    }

    sql += ") engine=innodb;";

    // remember to always free the result pointer!
    mysql_free_result(commit(sql.c_str()));
}

void Database::drop_table(const std::string &name)
{
    std::string sql = "DROP TABLE ";
    sql.append(name);
    sql.append(";");

    // remember to always free the result pointer!
    mysql_free_result(commit(sql.c_str()));
}

RESULT_VEC Database::desc_table(const std::string &name)
{
    std::string sql = "DESC " + std::string(name) + ";";

    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;

    MYSQL_FIELD *field;
    int field_count = 0;

    for (;(field = mysql_fetch_field(result)); ++field_count){}

    RESULT_VEC fields;
    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        std::vector<std::string> param;
        for (int i = 0; i < field_count; ++i)
        {
            param.push_back((result_row[i] ? result_row[i] : "NULL"));
        }
        fields.push_back(param);
    }

    mysql_free_result(result);
    return fields;
}

STRING_VEC Database::show_tables()
{
    std::string sql = "SHOW TABLES;";
    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;

    std::vector<std::string> results;

    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        results.push_back(result_row[0]);
    }

    return results;
}

bool Database::is_table(const std::string &name)
{
    std::vector<std::string> tables = show_tables();

    for (int i = 0; i < tables.size(); ++i)
    {
        if (tables[i] == name) return true;
    }
    return false;
}

void Database::insert_row(const std::string & name, const STRING_VEC &fields,
                          const RESULT_VEC &arg_vect)
{
    std::string sql = "INSERT " + name + " (";
    for (int i = 0; i < fields.size(); ++i)
    {
        sql += fields[i];
        if (i < fields.size() - 1) sql += ", ";
    }
    sql += ") VALUES (";

    if (!arg_vect.size()) sql += ")";

    for (int i = 0; i < arg_vect.size(); ++i)
    {
        for (int k = 0; k < arg_vect[i].size(); ++k)
        {
            sql += arg_vect[i][k];
            if (k < arg_vect[i].size() - 1) sql += ", ";
        }
        if (i < arg_vect.size() - 1) sql += "), (";
        else sql += ")";
    }

    sql += ";";


    mysql_free_result(commit(sql.c_str()));
}

void Database::update_row(const std::string & name,
                          const std::string & set,
                          const std::string & where)
{
    std::string sql = "UPDATE " + name + " SET " + set + " WHERE " + where + ";";
    mysql_free_result(commit(sql.c_str()));

}

void Database::delete_row(const std::string &name,
                          const std::string &where)
{
    std::string sql = "DELETE FROM " + name + " WHERE " + where + ";";
    mysql_free_result(commit(sql.c_str()));
}

RESULT_VEC Database::select(const std::string &paramaters,
                            const std::string &target)
{
    std::string sql = "SELECT ";
    sql.append(paramaters);
    sql += " FROM ";
    sql.append(target);
    sql += ";";


    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;
    MYSQL_FIELD *field;
    int field_count = 0;

    for (;(field = mysql_fetch_field(result)); ++field_count){}

    RESULT_VEC select_vector;
    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        std::vector< std::string > row_vector;
        for (int i =0; i < field_count; ++i)
        {
            if (result_row[i] == NULL) row_vector.push_back("NULL");
            else row_vector.push_back(result_row[i]);
        }

        select_vector.push_back(row_vector);
    }

    mysql_free_result(result);
    return select_vector;
}

RESULT_VEC Database::select(const std::string &paramaters)
{
    std::string sql = "SELECT ";
    sql.append(paramaters);
    sql += ";";

    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;
    MYSQL_FIELD *field;
    int field_count = 0;

    for (;(field = mysql_fetch_field(result)); ++field_count){}

    RESULT_VEC select_vector;

    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        std::vector< std::string > row_vector;
        for (int i =0; i < field_count; ++i)
        {
            row_vector.push_back(result_row[i]);
        }

        select_vector.push_back(row_vector);
    }
    mysql_free_result(result);
    return select_vector;
}

MYSQL_RES* Database::commit(const char* sql_request)
{
    MYSQL mysql;
    mysql_init(&mysql);
  
    MYSQL* conn = mysql_real_connect(&mysql, host_.c_str(),
                                     user_.c_str(), password_.c_str(),
                                     database_.c_str(), 0, 0, 0);

    if (conn == NULL)
    {
        const char* error = mysql_error(&mysql);
        throw MySQLException(0, error);
    }




    int state = mysql_query(conn, sql_request);

    if (state)
    {
        const char* error = mysql_error(&mysql);
        throw MySQLException(1, error);
    }
    MYSQL_RES* result = mysql_store_result(conn);

    mysql_close(conn);
    log_error(sql_request, "sql_request.log");
    return result;
}

std::ostream &operator<<(std::ostream &cout, const Database &db)
{
    cout << "<Database object " << &db << " conn=" << db.current_database() << ">";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const RESULT_VEC &result_vector)
{
    cout << "[";
    for (int i = 0; i < result_vector.size(); ++i)
    {
        cout << "{";
        for (int k = 0; k < result_vector[i].size(); ++k)
        {
            cout << result_vector[i][k] << ' ';
            if (i < result_vector[i].size() - 1) cout << ", ";

        }
        cout << "}";
        if (i < result_vector.size() - 1) cout << ", ";
    }
    cout << "]";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const STRING_VEC &string_vector)
{
    cout << "[ ";
    for (int i = 0; i < string_vector.size(); ++i)
    {
        cout << string_vector[i];
        if (i < string_vector.size() - 1) cout << ", ";
    }
    cout << "]";
    return cout;
}
