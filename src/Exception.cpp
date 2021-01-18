#include "Exception.h"

Exception::Exception(int error_code, const char* message)
:error_code_(error_code), message_(message)
{}

int Exception::error_code() const { return error_code_; }
std::string Exception::error_message() const { return message_; }

MySQLException::MySQLException(int error_code, const char* message)
:Exception(error_code, message)
{
    std::string printmessage = "MySQLException error " +
                          std::to_string(Exception::error_code()) +
                          ": " + Exception::error_message();
    log_error(printmessage.c_str(), "error.log");
}

BitException::BitException(int error_code, const char* message)
:Exception(error_code, message)
{
    std::string printmessage = "BitException error " +
                          std::to_string(Exception::error_code()) +
                          ": " + Exception::error_message();
    log_error(printmessage.c_str(), "error.log");
}

std::ostream &operator<<(std::ostream &cout, const MySQLException & e)
{
    cout << "< MySQLException error# " << e.error_code()
         << " : " << e.error_message() << " >";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const BitException & e)
{
    cout << "< BitException error# " << e.error_code()
         << " : " << e.error_message() << " >";
    return cout;
}
