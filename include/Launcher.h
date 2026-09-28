#pragma once
#include "IGame.h"
#include <memory>
#include <vector>

class Launcher {
public:
    void addGame(std::unique_ptr<IGame> game);
    void update(float dt);
    void render();
    bool wantsQuit() const { return quit_; }

private:
    enum class State { Home, Running };

    void updateHome();
    void renderHome();
    void launch(size_t i);

    std::vector<std::unique_ptr<IGame>> games_;
    State state_ = State::Home;
    size_t selected_ = 0;
    size_t running_ = 0;
    bool quit_ = false;
};
