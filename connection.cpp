#include <iostream>
#include <thread>
#include <unistd.h>
#include "connection.h"

//constexpr std::chrono::milliseconds Connection::reconnTimeMS = std::chrono::milliseconds(2000);

Connection::Connection() : 
    bufferSize{128}
    {};

bool Connection::init(int port){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << "Socket error";
        perror("Socket error");
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        if (errno == EADDRINUSE){
            addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) >= 0){
                std::cout << "Its a client\n";
                isServer = false;
                return true;
            }
        }
        perror("Connection error");
        return false;
    }
    std::cout << "Its a server\n";
    isServer = true;
    listener = sock;
    waitConn();
    return true;
}

void Connection::waitConn(){ 
    listen(listener, 1);
    sock = -1;
    while (sock < 0) {
        sock = accept(listener, 0, 0);
        std::cout << sock << '\n';
        if (sock < 0)
            perror("Accept error");
    }
}

int Connection::receive(char *buf)
{ 
    int bytesRecv = recv(sock, buf, bufferSize, 0);
    std::cout << "BytesRecv " << bytesRecv << ", bufSize = " << bufferSize <<'\n'; 
    printf("%s", buf);
    while (bytesRecv <= 0){
        reconnect();
        bytesRecv = recv(sock, buf, bufferSize, 0);
        printf("%s", buf);
        std::cout << "BytesRecv " << bytesRecv << '\n'; 
    }
    return bytesRecv;
}

void Connection::send(char *msg, int msgSize)
{
    int bytesSend;
    while (bytesSend = (sock, msg, msgSize, 0) < 0)
        reconnect();
}

void Connection::reconnect()
{
    if (isServer)
        waitConn();
    else {
        close(sock);
        init(ntohs(addr.sin_port));
    }
}