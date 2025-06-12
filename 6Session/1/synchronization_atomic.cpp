#include <iostream>
#include <thread>
#include <atomic>  // Required for std::atomic

std::atomic<int> counter(0);  // Now thread-safe

void increment() {
    for (int i = 0; i < 100000; ++i)
        ++counter;  // Atomic increment, no race condition
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Counter: " << counter << std::endl;
    return 0;
}

//g++ -pthread synchronization_atomic.cpp 

//g++ -S  synchronization_atomic.cpp