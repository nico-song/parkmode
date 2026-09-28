#include "games/Snake.h"
#include "raylib.h"

namespace {
constexpr int kCols = 32, kRows = 18, kCell = 40;
constexpr float kStep = 0.1f;
}

void Snake::init() {
    body_.clear();
    body_.push_back({kCols / 2, kRows / 2});
    dir_ = nextDir_ = {1, 0};
    stepTimer_ = 0.f;
    dead_ = false;
    spawnFood();
}

void Snake::spawnFood() {
    while (true) {
        Cell c{GetRandomValue(0, kCols - 1), GetRandomValue(0, kRows - 1)};
        bool onBody = false;
        for (auto& b : body_) if (b.x == c.x && b.y == c.y) onBody = true;
        if (!onBody) { food_ = c; return; }
    }
}

void Snake::update(float dt) {
    if (dead_) { if (IsKeyPressed(KEY_R)) init(); return; }

    if (IsKeyPressed(KEY_UP)    && dir_.y == 0) nextDir_ = {0, -1};
    if (IsKeyPressed(KEY_DOWN)  && dir_.y == 0) nextDir_ = {0, 1};
    if (IsKeyPressed(KEY_LEFT)  && dir_.x == 0) nextDir_ = {-1, 0};
    if (IsKeyPressed(KEY_RIGHT) && dir_.x == 0) nextDir_ = {1, 0};

    stepTimer_ += dt;
    if (stepTimer_ < kStep) return;
    stepTimer_ -= kStep;
    dir_ = nextDir_;

    Cell head{body_.front().x + dir_.x, body_.front().y + dir_.y};
    if (head.x < 0 || head.y < 0 || head.x >= kCols || head.y >= kRows) { dead_ = true; return; }
    for (auto& b : body_) if (b.x == head.x && b.y == head.y) { dead_ = true; return; }

    body_.push_front(head);
    if (head.x == food_.x && head.y == food_.y) spawnFood();
    else body_.pop_back();
}

void Snake::render() {
    DrawRectangle(food_.x * kCell, food_.y * kCell, kCell, kCell, RED);
    for (auto& b : body_)
        DrawRectangle(b.x * kCell + 2, b.y * kCell + 2, kCell - 4, kCell - 4, GREEN);
    DrawText(TextFormat("score %d", (int)body_.size() - 1), 20, 20, 30, RAYWHITE);
    if (dead_) DrawText("dead. press R", 480, 340, 40, RAYWHITE);
}
