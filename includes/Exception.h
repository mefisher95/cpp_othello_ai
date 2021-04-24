#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <ostream>
#include "util.h"

class Exception
{
public:
    Exception(int error_code, const char* message);

    int error_code() const;
    std::string error_message() const;

private:
    const int error_code_;
    const std::string message_;
};


class MySQLException: public Exception
{
public:
    MySQLException(int error_code, const char* error);
};

class BitException: public Exception
{
public:
    BitException(int error_code, const char* error);
};

class HeuristicException: public Exception
{
public:
    HeuristicException(int error_code, const char* error);
};


std::ostream &operator<<(std::ostream &cout, const MySQLException &);
std::ostream &operator<<(std::ostream &cout, const BitException &);
std::ostream &operator<<(std::ostream &cout, const HeuristicException &);


#endif
