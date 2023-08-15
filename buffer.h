#pragma once
#include <mutex>
#include <semaphore>
#include <queue>
#include <condition_variable>

#define Container std::queue

template <typename T>
class Buffer{
public:
    void push(T value);
    T pop();
    Buffer(){};
private:
    Container<T> buffer;
    std::condition_variable checkBuf;
    std::mutex changingBuf;
};

template <typename T>
void Buffer<T>::push(T value){
    std::unique_lock<std::mutex> lck(changingBuf);
    buffer.push(value);
    checkBuf.notify_one();
}

// Blocking operation
template <typename T>
T Buffer<T>::pop(){
    std::unique_lock<std::mutex> lck(changingBuf);
    while (buffer.size() <= 0)
        checkBuf.wait(lck);
    auto value = buffer.front();
    buffer.pop();
    return value;
}