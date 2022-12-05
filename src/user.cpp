#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class User
{
private:
    std::string username;
    std::string password;

public:
    User(std::string userName, std::string hashedPassword)
    {
        this->username = userName;
        this->password = hashedPassword;
    }
    void store_in_json()
    {
        json user;
        std::ifstream i("users.json");  //TODO: a bug: if the users.json file deosn't exist the program throw an error
        if (i.is_open())
        {
            i >> user;
        }
        // system("cls");
        int userCount = 0;
        for (auto it = user.begin(); it != user.end(); ++it) // we iterate through the json file to add the new user in the end,
        {
            userCount += 1;
            std::cout << *it << std::endl;
        }
        userCount += 1;
        user[std::to_string(userCount)]["username"] = username;
        user[std::to_string(userCount)]["password"] = password;

        std::ofstream file("users.json");
        file << user;
    }
};
