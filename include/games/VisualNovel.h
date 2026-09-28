#pragma once
#include "IGame.h"
#include "raylib.h"
#include <string>
#include <vector>

class VisualNovel : public IGame {
public:
    std::string name() const override { return "Visual Novel"; }
    void init() override;
    void update(float dt) override;
    void render() override;

private:
    struct Line {
        std::string speakerZh, speakerEn;
        std::string zh, en;
    };
    void loadFont();
    const std::string& text() const;
    const std::string& speaker() const;

    std::vector<Line> script_;
    size_t index_ = 0;
    float shown_ = 0.f;
    bool chinese_ = true;
    bool fontLoaded_ = false;
    Font font_{};
};
