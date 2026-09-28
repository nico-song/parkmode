#include "raylib.h"

int main() {
    InitWindow(1280, 720, "parkmode");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("parkmode", 40, 40, 40, RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
