#include <iostream>
#include <thread>
#include <netinet/in.h>
#include "client.h"

Connection::Client::Client()
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

bool Connection::Client::connect(int port)
{
    addr.sin_port = htons(port);
    while(1){
        socket = Socket::getSocket();
        if (!socket) return false;

        if (::connect(*socket, (struct sockaddr *)&addr, sizeof(addr)) >= 0)
            return true;
        std::this_thread::sleep_for(reconnTime);
    }
}