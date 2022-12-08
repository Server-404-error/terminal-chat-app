#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <ctime>

using json = nlohmann::json;
using namespace std;

class User
{
private:
    std::string username;
    std::string password;
    std::string id;

public:
    User(std::string userName, std::string hashedPassword)
    {
        this->username = userName;
        this->password = hashedPassword;
    }
    std::string id_generator()
    {
        const char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int string_length = sizeof(alphanum) - 1;
        srand(time(0));
        for (int i = 0; i < 10; i++)
            id += alphanum[rand() % string_length];
    }
    void store_in_json()
    {
        json user;
        std::ifstream i("users.json"); // TODO: a bug: if the users.json file deosn't exist the program throw an error
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

    void connect_to_server()
    {
        std::string user_id = id_generator();
        std::string ip_addr = "127.0.0.1";
        char *ip;
        strcpy(ip, ip_addr.c_str());
        int port = 5566;
        int sock;
        struct sockaddr_in addr;
        socklen_t addr_size;
        char buffer[1024];
        int n;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            std::cerr << "[*] Failed to create socket :( \n"
                      << std::endl;
            exit(1);
        }
        std::cout << "[+]TCP server socket created" << std::endl;
        memset(&addr, '\0', sizeof(addr));

        addr.sin_family = AF_INET; // IPV4
        addr.sin_port = port;
        addr.sin_addr.s_addr = inet_addr(ip);

        connect(sock, (struct sockaddr *)&addr, sizeof(addr));
        std::cout << "[+]Connected to the server" << std::endl;
        std::string message;
        char *msg;
        bool on = true;
        while (on)
        {
            bzero(buffer, 1024);
            std::cin >> message;
            strcpy(buffer, message.c_str());
            sendto(sock, buffer, strlen(buffer), 0, NULL, 0);
            // if(strcmp(buffer, "quit"))
            //     on = false;
        }

        close(sock);
        std::cout << "[+]Server disconnected \n\n"
                  << std::endl;
    }
};
