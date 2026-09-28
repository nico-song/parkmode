#include "VehicleSim.h"
#include <chrono>

void VehicleSim::start() {
    running_ = true;
    thread_ = std::thread(&VehicleSim::run, this);
}

void VehicleSim::stop() {
    running_ = false;
    if (thread_.joinable()) thread_.join();
}

void VehicleSim::run() {
    Gear current = Gear::P;
    queue_.push({current});

    while (running_) {
        Gear want = requested_.load();
        if (want != current) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            current = want;
            queue_.push({current});
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
