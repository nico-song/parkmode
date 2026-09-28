#include "raylib.h"
#include "Launcher.h"
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

    while (!WindowShouldClose() && !launcher.wantsQuit()) {
        launcher.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        launcher.render();
        EndDrawing();
    }
    CloseWindow();
}
