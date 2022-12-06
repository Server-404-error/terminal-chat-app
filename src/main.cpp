#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp> //ignore the squigly lines if you have them

using json = nlohmann::json;
using namespace std;

void store_in_json(std::string username, std::size_t hashedPassword)
{
    json user;
    std::ifstream i("users.json");
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
    user[std::to_string(userCount)]["password"] = hashedPassword;

    std::ofstream file("users.json");
    file << user;
}

bool not_verified(std::string password)
{
    int uppercase = 0;
    int lowercase = 0;
    int specialChar = 0;
    int len = password.length();
    if (len >= 10 && len <= 30)
    {
        for (auto a : password)
        {
            if (islower(a))
            {
                lowercase += 1;
            }
            else if (isupper(a))
            {
                uppercase += 1;
            }
            else if (a == '%' || a == '!' || a == '?' || a == '#' || a == '@')
            {
                specialChar += 1;
            }
        }
    }

    else
    {
        return false;
    }
    return uppercase >= 1 && lowercase >= 1 && specialChar >= 1;
}

// TODO: add newFeild for signup date (ex: joined: 05/12/2022)
void sign_up()
{
    std::string userName = "";
    std::string password = "";

    system("clear");
    std::cout << "you want to sign up" << '\n';
    while (userName == "")
    {
        std::cout << "Please choose a userName" << '\n';
        std::cin >> userName;
    }

    while (!not_verified(password))
    {
        std::cout << "Please choose a password (length between 15 and 30, must include 1 Uppercase, 1 lowercase and 1 special character" << '\n';
        std::cin >> password;
    }

    // Instantiation of Object
    std::hash<std::string> hash_fn;
    std::size_t hashedPassword = hash_fn(password); // TODO: Change the hash function later

    // Using operator() to get hash value

    store_in_json(userName, hashedPassword); // this function will store the data in json file
}

void log_in()
{
    system("clear");
    std::cout << "you want to log in" << '\n';
}

int choices()
{
    std::cout << "Welcome to the terminal chat app" << '\n';
    std::cout << "Please choose between: " << '\n';
    std::cout << "1. Sign up" << '\n';
    std::cout << "2. log in" << '\n';
    int choice;
    std::cin >> choice;
    return choice;
}

int main(int argc, char const *argv[])
{
    int choice = choices();
    while (choice != 1 && choice != 2)
    {
        choice = choices();
    }

    if (choice == 1)
    {
        sign_up();
    }
    else if (choice == 2)
    {
        log_in();
    }


    return 0;
}
