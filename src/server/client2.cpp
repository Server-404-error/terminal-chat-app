#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
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
        recv(sock, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "quit"))
            on = false;
        message = buffer;
        std::cout << "[+]freind : " << message << std::endl;



        bzero(buffer, 1024);
        std::cin >> message;
        strcpy(buffer, message.c_str());
        std::cout << "[+]Me: " << message << std::endl;
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    std::cout << "[+]Server disconnected \n\n"
              << std::endl;
    return 0;
}
