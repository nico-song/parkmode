#pragma once
#include "IGame.h"
#include "VehicleEvent.h"
#include <memory>
#include <vector>

class Launcher {
public:
    void addGame(std::unique_ptr<IGame> game);
    void onVehicleEvent(const VehicleEvent& e);
    void update(float dt);
    void render();
    bool wantsQuit() const { return quit_; }

private:
    enum class State { Home, Running, Locked };

    void updateHome();
    void renderHome();
    void renderLock();
    void renderGear();
    void launch(size_t i);

    std::vector<std::unique_ptr<IGame>> games_;
    State state_ = State::Home;
    State resumeTo_ = State::Home;
    Gear gear_ = Gear::P;
    size_t selected_ = 0;
    size_t running_ = 0;
    bool quit_ = false;
};
