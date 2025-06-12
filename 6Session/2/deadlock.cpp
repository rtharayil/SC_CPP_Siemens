#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex sensorMutex;
std::mutex motorMutex;

void readSensorAndControlMotor() {
    std::lock_guard<std::mutex> lockSensor(sensorMutex); // Lock sensor
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate reading

    std::cout << "[SensorManager] Acquired sensor, now accessing motor...\n";

    std::lock_guard<std::mutex> lockMotor(motorMutex); // Tries to lock motor
    std::cout << "[SensorManager] Sensor and motor access granted.\n";
}

void controlMotorAndReadSensor() {
    std::lock_guard<std::mutex> lockMotor(motorMutex); // Lock motor
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate actuation

    std::cout << "[MotorController] Acquired motor, now accessing sensor...\n";

    std::lock_guard<std::mutex> lockSensor(sensorMutex); // Tries to lock sensor
    std::cout << "[MotorController] Motor and sensor access granted.\n";
}

int main() {
    std::thread task1(readSensorAndControlMotor);
    std::thread task2(controlMotorAndReadSensor);

    task1.join();
    task2.join();

    std::cout << "[System] Tasks complete (maybe stuck if deadlock).\n";
    return 0;
}
// g++ -std=c++17 -Wall -Wextra -pthread deadlock.cpp