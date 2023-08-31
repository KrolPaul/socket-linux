#include <thread>
#include <string>
#include <iostream>
#include "../concurrent/buffer.h"  
#include "threadactions.h"


int main(int argc, char * argv[]){
    int port = 8243;
    if (argc > 1)
        port = std::atoi(argv[1]);
    std::cout << "Running at port " << port << ".\n";
    std::cout << "You can specify port in a first command line argument.\n";

    Buffer<std::string> buf;
    std::thread Thread1(thread1, std::ref(buf));
    std::thread Thread2(thread2, std::ref(buf), port);
    Thread1.join();
    Thread2.join();
    return 0;
}