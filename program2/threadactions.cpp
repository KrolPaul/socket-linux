#include <iostream>
#include <stdlib.h>
#include "threadactions.h"
#include "../connection/server.h"


void thread1(int port){
    Connection::Server server;
    if (!server.connect(port)) return;
    char buf[server.getBufferSize()];
    int bytesRecv;
    char ack[3];
    int val;
    while(1){
        bytesRecv = server.recv(buf);
        while(bytesRecv <= 0){
            server.connect();
            bytesRecv = server.recv(buf);
        }
        server.send(ack, sizeof(ack));
        val = std::atoi(buf);
        if (val % 32 || val < 32)
            std::cout << "Error: " << buf << " is not a multiple of 32.\n";
        else
            std::cout << "Data received: " << buf << '\n';
    }
}