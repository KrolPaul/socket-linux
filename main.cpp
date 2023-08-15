#include <iostream>
#include <string>
#include <thread>
//#include "buffer.h"
#include "connection.h"

int main(int argc, char * argv[]){
    int n;
    /*Buffer<std::string> buf;
    std::thread t1(thread1, std::ref(buf));
    std::thread t2(thread2, std::ref(buf));
    t1.join();
    t2.join();*/
    Connection conn;
    std::cout << "START\n";
    std::cout << conn.init(8243) << '\n';
            char * msg = "Hello Paul!\n";
    if (argc == 2){
        conn.send(msg, sizeof(msg));
    }
    else{
        char buf[sizeof(msg)];
        conn.receive(buf);
        printf("%s", buf);
        std::cout << "Good!";
    }
    return 0;
}