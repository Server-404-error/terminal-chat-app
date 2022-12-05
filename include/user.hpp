#ifndef MY_USER_H
#define MY_USER_H
#include <string>



class User
{
private:
    std::string username;
    std::string password;

public:
    User(std::string username, std::string password);
    void store_in_json();
};

#endif // MY_USER_H