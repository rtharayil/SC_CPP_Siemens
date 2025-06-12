#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex sensorMutex;
std::mutex motorMutex;

void taskSensorThenMotor() {
    std::scoped_lock lock(sensorMutex, motorMutex); // Safe, ordered lock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[SensorManager] Acquired both sensor and motor safely.\n";
}

void taskMotorThenSensor() {
    std::scoped_lock lock(motorMutex, sensorMutex); // Still safe!
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[MotorController] Acquired both motor and sensor safely.\n";
}

int main() {
    std::thread t1(taskSensorThenMotor);
    std::thread t2(taskMotorThenSensor);

    t1.join();
    t2.join();

    std::cout << "[System] All tasks completed without deadlock.\n";
    return 0;
}

//g++ -std=c++17 -Wall -Wextra -pthread deadlock_fix.cpp