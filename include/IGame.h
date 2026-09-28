#pragma once
#include <string>

class IGame {
public:
    virtual ~IGame() = default;
    virtual std::string name() const = 0;
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void onPause() {}
    virtual void onResume() {}
};
