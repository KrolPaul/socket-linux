#pragma once
#include <memory>
namespace Connection{
    class Socket;
};

class Connection::Socket{
public:

    Socket& operator=(int val);
    operator int() const;
    static std::unique_ptr<Socket> getSocket();
    static std::unique_ptr<Socket> getSocket(int domain, int type, int protocol);

    int recv(char * buf, size_t bufferSize);
    int send(const char * const msg, int msgSize);

    Socket(int val = -1);
    ~Socket();

private:
    int socket;
};