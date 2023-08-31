#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "socket.h"

constexpr int DEFAULT_DOMAIN = AF_INET;
constexpr int DEFAULT_TYPE = SOCK_STREAM;

Connection::Socket::Socket(int val) :
    socket{val}
{}

Connection::Socket& Connection::Socket::operator=(int val)
{
    socket = val;
    return *this;
}

Connection::Socket::operator int() const
{
    return socket;
}

std::unique_ptr<Connection::Socket> Connection::Socket::getSocket()
{
    return getSocket(DEFAULT_DOMAIN, DEFAULT_TYPE, 0);
}

std::unique_ptr<Connection::Socket> Connection::Socket::getSocket(int domain, int type, int protocol)
{
    std::unique_ptr<Socket> ret;
    auto sock = ::socket(domain, type, protocol);
    if (sock < 0){
        perror("Socket error");
        return move(ret);
    }
    ret = std::make_unique<Socket>(sock);
    return move(ret);
}

int Connection::Socket::recv(char *buf, size_t bufferSize)
{
    return ::recv(socket, buf, bufferSize, 0);
}

int Connection::Socket::send(const char * const msg, int msgSize)
{
    return ::send(socket, msg, msgSize, 0);
}

Connection::Socket::~Socket()
{
    if (socket >= 0)
        ::close(socket);
}
