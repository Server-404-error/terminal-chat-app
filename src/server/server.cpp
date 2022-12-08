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
    int server_sock, client_sock1, client_sock2;
    struct sockaddr_in server_addr, client_addr1, client_addr2;
    socklen_t addr_size1, addr_size2;
    char buffer[1024];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        std::cerr << "[*] Failed to create socket :( \n"
                  << std::endl;
        exit(1);
    }
    std::cout << "[+]TCP server socket created" << std::endl;
    memset(&server_addr, '\0', sizeof(server_addr));

    server_addr.sin_family = AF_INET; // IPV4
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // bind

    n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        std::cerr << "[*] Failed to bind :( \n"
                  << std::endl;
        exit(1);
    }
    std::cout << "[+]Bind to port " << port << std::endl;

    listen(server_sock, 5);
    std::cout << "[+]Listening... " << port << std::endl;

    //--------------------client 1 --------------------------
    addr_size1 = sizeof(client_addr1);
    client_sock1 = accept(server_sock, (struct sockaddr *)&client_addr1, &addr_size1);
    std::cout << "[+]Client 1 connected" << std::endl;

    //for the server to receive data we are obliged to initialize sockets for clients
    //we need a way for the server to accept any incoming connection

    std::string m;
    bool on = true;
    while (on)
    {
        
        bzero(buffer, 1024);
        recv(client_sock2, buffer, strlen(buffer), 0);
        std::string str(buffer);
        std::cout << str << std::endl;
        // if(strcmp(buffer, "quit"))
        //     on = false;
        
    }
    close(client_sock1);
    close(client_sock2);

    std::cout << "[+]Client disconnected \n\n"
              << std::endl;
    return 0;
}
