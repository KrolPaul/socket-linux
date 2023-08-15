#pragma once
#include <chrono>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

class Connection{
public:
    Connection();
    //Blocking operations
    bool init(int port);
    int receive(char * buf);
    void send(char * msg, int msgSize);

private:
    int bufferSize;
    struct sockaddr_in addr;
    int sock, listener;
    bool isServer;
    static constexpr std::chrono::milliseconds reconnTimeMS =std::chrono::milliseconds(2000);

    void waitConn();
    void reconnect();
};