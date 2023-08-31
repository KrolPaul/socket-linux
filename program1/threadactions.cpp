#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include "threadactions.h"
#include "../connection/client.h"

int toDigit (unsigned char c) 
{
    if (std::isdigit(c))
        return c - '0';
    return -1;
}

bool isOdd (char c) 
{
    return !(toDigit(c) % 2); 
}

void countChars(std::string & s, std::map<char,int> & counter)
{
    std::for_each(s.begin(), s.end(),
        [&counter] (auto el){
            if (counter.find(el) == counter.end())
                counter[el] = 1;
            else
                ++counter[el];
    }); 
}

void addToStr(std::string & res, std::string what, int quant = 1){
    while (quant--)
        res += what;
}

std::string makeString(std::map<char,int> & digits){
    std::string s;
    std::for_each(digits.rbegin(), digits.rend(),
        [&s](auto el){
            if (isOdd(el.first))
                addToStr(s, "KB", el.second);
            else
                addToStr(s, std::string(1, el.first), el.second);
        }
    );
    return s;
}

int sum(std::string & s){
    int res = 0;
    std::for_each(s.begin(), s.end(),
        [&res](unsigned char c){
            auto val = toDigit(c);
            if (val != -1) res += val;
        }
    );
    return res;
}

void thread1(Buffer<std::string> & buf)
{
    std::string s;
    std::map<char,int> counter;
    while(1){
        std::cin >> s;
        counter.clear();

        if (s.size() > 64) continue;
        if (!std::all_of(s.begin(), s.end(), 
            [](unsigned char c){ return std::isdigit(c); })) continue;

        countChars(s, counter);
        buf.push(makeString(counter));
    }
}

void thread2(Buffer<std::string> & buf, int port){
    Connection::Client client;
    while (!client.connect(port));
    std::string s;
    char ack[3];
    while(1){
        s = buf.pop();
        std::cout << s << '\n';
        while(1){
            client.send(std::to_string(sum(s)).c_str(), s.size());
            if (client.recv(ack) == sizeof(ack)) break;
            else client.connect(port);
        }
    }
} 

