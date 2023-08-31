#include <thread>
#include <iostream>
#include "threadactions.h"

int main(int argc, char * argv[]){
    int port = 8243;
    if (argc > 1)
        port = std::atoi(argv[1]);
    std::cout << "Running at port " << port << ".\n";
    std::cout << "You can specify port in a first command line argument.\n";
    
    std::thread Thread1(thread1, port);
    Thread1.join();
    return 0;
}