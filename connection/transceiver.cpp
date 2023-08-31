#include "transceiver.h"

const size_t DEFAULT_BUF_SIZE = 1024;

Connection::Transceiver::Transceiver() : bufferSize{DEFAULT_BUF_SIZE}
{}

bool Connection::Transceiver::setBufferSize(size_t bufferSize)
{
    return true;
}

size_t Connection::Transceiver::getBufferSize()
{
    return bufferSize;
}

int Connection::Transceiver::recv(char *buf)
{
    socket->recv(buf, bufferSize);
}

int Connection::Transceiver::send(const char *const msg, int msgSize)
{
    socket->send(msg, msgSize);
}
