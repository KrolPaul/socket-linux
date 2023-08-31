#pragma once
#include "transceiver.h"

namespace Connection {
    class Server;
};

class Connection::Server : virtual public Connection::Transceiver {
public:
    Server();
    bool connect(int port = 0) override;

protected:
    bool bind(int port);
    bool listen();
    bool accept();

private:
    std::unique_ptr<Socket> listener;
};