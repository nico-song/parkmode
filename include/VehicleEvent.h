#pragma once

enum class Gear { P, R, N, D };

struct VehicleEvent {
    Gear gear;
};
