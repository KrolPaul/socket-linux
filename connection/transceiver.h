#pragma once
#include <netinet/in.h>
#include "socket.h"

namespace Connection {
    class Transceiver;
};

class Connection::Transceiver {
public:
    bool setBufferSize(size_t bufferSize);
    size_t getBufferSize();
    virtual bool connect(int port = 0) = 0;

    int recv(char * buf);
    int send(const char * const msg, int msgSize);

protected:
    Transceiver();
    struct sockaddr_in addr;
    std::unique_ptr<Socket> socket;

private:
    size_t bufferSize;
};