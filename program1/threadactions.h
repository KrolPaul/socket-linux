#pragma once
#include <string>
#include "../concurrent/buffer.h"

void thread1(Buffer<std::string> & buf);
void thread2(Buffer<std::string> & buf, int port);