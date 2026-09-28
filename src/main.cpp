#include "raylib.h"
#include "games/Snake.h"
#include <memory>

int main() {
    InitWindow(1280, 720, "parkmode");
    SetTargetFPS(60);

    std::unique_ptr<IGame> game = std::make_unique<Snake>();
    game->init();

    while (!WindowShouldClose()) {
        game->update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        game->render();
        EndDrawing();
    }
    CloseWindow();
}
