#include "Launcher.h"
#include "raylib.h"
#include <string>

namespace {
constexpr int kTileW = 360, kTileH = 220, kGap = 40, kTileY = 250;

Rectangle tileRect(size_t i, size_t count) {
    int n = (int)count;
    float totalW = (float)(n * kTileW + (n - 1) * kGap);
    float x = (GetScreenWidth() - totalW) / 2 + (float)i * (kTileW + kGap);
    return {x, (float)kTileY, (float)kTileW, (float)kTileH};
}
}

void Launcher::addGame(std::unique_ptr<IGame> game) {
    games_.push_back(std::move(game));
}

void Launcher::launch(size_t i) {
    running_ = i;
    games_[i]->init();
    state_ = State::Running;
}

void Launcher::onVehicleEvent(const VehicleEvent& e) {
    gear_ = e.gear;
    bool parked = (gear_ == Gear::P);

    if (!parked && state_ != State::Locked) {
        resumeTo_ = state_;
        if (state_ == State::Running) games_[running_]->onPause();
        state_ = State::Locked;
    } else if (parked && state_ == State::Locked) {
        state_ = resumeTo_;
        if (state_ == State::Running) games_[running_]->onResume();
    }
}

void Launcher::update(float dt) {
    if (state_ == State::Locked) return;
    if (state_ == State::Home) {
        updateHome();
        return;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        games_[running_]->onPause();
        state_ = State::Home;
        return;
    }
    games_[running_]->update(dt);
}

void Launcher::updateHome() {
    if (IsKeyPressed(KEY_Q)) quit_ = true;
    if (IsKeyPressed(KEY_RIGHT) && selected_ + 1 < games_.size()) selected_++;
    if (IsKeyPressed(KEY_LEFT) && selected_ > 0) selected_--;
    if (IsKeyPressed(KEY_ENTER)) { launch(selected_); return; }

    Vector2 mouse = GetMousePosition();
    for (size_t i = 0; i < games_.size(); i++) {
        if (CheckCollisionPointRec(mouse, tileRect(i, games_.size()))) {
            selected_ = i;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { launch(i); return; }
        }
    }
}

void Launcher::render() {
    if (state_ == State::Locked) {
        if (resumeTo_ == State::Running) games_[running_]->render();
        else renderHome();
        renderLock();
    } else if (state_ == State::Running) {
        games_[running_]->render();
        DrawText("Esc: home", GetScreenWidth() - 150, 20, 20, GRAY);
    } else {
        renderHome();
    }
    renderGear();
}

void Launcher::renderHome() {
    ClearBackground(Color{12, 12, 16, 255});
    DrawText("parkmode", 60, 60, 60, RAYWHITE);
    DrawText("choose a game", 60, 130, 30, GRAY);

    for (size_t i = 0; i < games_.size(); i++) {
        Rectangle r = tileRect(i, games_.size());
        bool sel = (i == selected_);
        DrawRectangleRec(r, sel ? Color{40, 90, 200, 255} : Color{35, 35, 45, 255});
        if (sel) DrawRectangleLinesEx(r, 4, RAYWHITE);

        std::string name = games_[i]->name();
        int w = MeasureText(name.c_str(), 40);
        DrawText(name.c_str(), (int)(r.x + (r.width - w) / 2), (int)(r.y + r.height / 2 - 20), 40, RAYWHITE);
    }
    DrawText("arrows + enter, or click    q: quit    1-4: gear", 60, 640, 20, GRAY);
}

void Launcher::renderLock() {
    int W = GetScreenWidth(), H = GetScreenHeight();
    DrawRectangle(0, 0, W, H, Fade(BLACK, 0.75f));
    const char* msg = "Shift to Park to play";
    int w = MeasureText(msg, 40);
    DrawText(msg, (W - w) / 2, H / 2 - 20, 40, RAYWHITE);
}

void Launcher::renderGear() {
    const char* labels[] = {"P", "R", "N", "D"};
    int x0 = GetScreenWidth() - 180;
    for (int i = 0; i < 4; i++) {
        bool on = ((int)gear_ == i);
        DrawText(labels[i], x0 + i * 40, 685, 30, on ? RAYWHITE : DARKGRAY);
    }
}
