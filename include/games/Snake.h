#pragma once
#include "IGame.h"
#include <deque>

class Snake : public IGame {
public:
    std::string name() const override { return "Snake"; }
    void init() override;
    void update(float dt) override;
    void render() override;

private:
    struct Cell { int x, y; };
    void spawnFood();

    std::deque<Cell> body_;
    Cell dir_{1, 0}, nextDir_{1, 0}, food_{0, 0};
    float stepTimer_ = 0.f;
    bool dead_ = false;
};
