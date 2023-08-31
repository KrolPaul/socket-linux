#include <iostream>
#include "server.h"

Connection::Server::Server()
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

bool Connection::Server::bind(int port)
{
    addr.sin_port = htons(port);
    listener = Socket::getSocket();
    if (::bind(*listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return false;
    return true;
}

bool Connection::Server::listen()
{
    if (::listen(*listener, 1) >= 0)
        return true;
        
    perror("Listen error");
    return false;
}

bool Connection::Server::accept()
{
    socket = std::make_unique<Socket>(::accept(*listener, 0, 0));
    if (*socket >= 0)
        return true;
    perror("Accept error");
    return false;
}

bool Connection::Server::connect(int port)
{
    if (port > 0)
        if (!bind(port)) return false;
    if (!listen())
        return false;
    if (!accept())
        return false;
    return true;
}