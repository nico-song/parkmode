#include "raylib.h"
#include "Launcher.h"
#include "EventQueue.h"
#include "VehicleSim.h"
#include "games/Snake.h"
#include "games/VisualNovel.h"
#include <memory>

int main() {
    InitWindow(1280, 720, "parkmode");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    Launcher launcher;
    launcher.addGame(std::make_unique<Snake>());
    launcher.addGame(std::make_unique<VisualNovel>());

    EventQueue<VehicleEvent> events;
    VehicleSim car(events);
    car.start();

    while (!WindowShouldClose() && !launcher.wantsQuit()) {
        if (IsKeyPressed(KEY_ONE))   car.requestGear(Gear::P);
        if (IsKeyPressed(KEY_TWO))   car.requestGear(Gear::R);
        if (IsKeyPressed(KEY_THREE)) car.requestGear(Gear::N);
        if (IsKeyPressed(KEY_FOUR))  car.requestGear(Gear::D);

        while (auto e = events.tryPop()) launcher.onVehicleEvent(*e);

        launcher.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        launcher.render();
        EndDrawing();
    }

    car.stop();
    CloseWindow();
}
