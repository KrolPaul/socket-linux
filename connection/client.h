#pragma once
#include <chrono>
#include "transceiver.h"

namespace Connection {
    class Client;
};

class Connection::Client : virtual public Connection::Transceiver {
public:
    Client();
    bool connect(int port) override;

    const std::chrono::milliseconds reconnTime = std::chrono::milliseconds(1000);
}; 