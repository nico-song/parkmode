#pragma once
#include "EventQueue.h"
#include "VehicleEvent.h"
#include <atomic>
#include <thread>

class VehicleSim {
public:
    explicit VehicleSim(EventQueue<VehicleEvent>& queue) : queue_(queue) {}
    ~VehicleSim() { stop(); }

    void start();
    void stop();
    void requestGear(Gear g) { requested_ = g; }

private:
    void run();

    EventQueue<VehicleEvent>& queue_;
    std::atomic<Gear> requested_{Gear::P};
    std::atomic<bool> running_{false};
    std::thread thread_;
};
