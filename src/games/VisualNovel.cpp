#include "games/VisualNovel.h"
#include <set>

namespace {
constexpr float kCharsPerSec = 30.f;
constexpr int kFontBase = 10;
constexpr float kTextSize = kFontBase * 3;
constexpr float kHintSize = kFontBase * 2;
const char* kFontPath = ASSETS_DIR "/fonts/fusion-pixel-10px-monospaced-zh_hans.ttf";
const char* kHintZh = "空格：继续    L：English";
const char* kHintEn = "Space: next    L: 中文";

int codepointCount(const std::string& s) {
    int count = 0, i = 0;
    while (i < (int)s.size()) {
        int bytes = 0;
        GetCodepointNext(s.c_str() + i, &bytes);
        i += bytes;
        count++;
    }
    return count;
}

std::string utf8Prefix(const std::string& s, int n) {
    int i = 0;
    for (int c = 0; c < n && i < (int)s.size(); c++) {
        int bytes = 0;
        GetCodepointNext(s.c_str() + i, &bytes);
        i += bytes;
    }
    return s.substr(0, i);
}
}

void VisualNovel::init() {
    script_ = {
        {"雨", "Rain", "……这里是哪里？", "...Where am I?"},
        {"雨", "Rain", "车停着。屏幕亮着。", "The car is parked. The screen is on."},
        {"???", "???", "欢迎来到停车模式。", "Welcome to park mode."},
        {"???", "???", "只要车不动，\n故事就不会停。", "As long as the car stays still,\nthe story keeps going."},
        {"雨", "Rain", "那如果我挂到D挡呢？", "And if I shift into Drive?"},
        {"???", "???", "那我们就下次再见。", "Then we'll meet again next time."},
    };
    index_ = 0;
    shown_ = 0.f;
    if (!fontLoaded_) loadFont();
}

void VisualNovel::loadFont() {
    std::string all;
    for (char c = 32; c < 127; c++) all += c;
    for (auto& l : script_) all += l.speakerZh + l.speakerEn + l.zh + l.en;
    all += kHintZh;
    all += kHintEn;

    std::set<int> unique;
    int i = 0;
    while (i < (int)all.size()) {
        int bytes = 0;
        unique.insert(GetCodepointNext(all.c_str() + i, &bytes));
        i += bytes;
    }
    std::vector<int> cps(unique.begin(), unique.end());

    font_ = LoadFontEx(kFontPath, kFontBase, cps.data(), (int)cps.size());
    SetTextureFilter(font_.texture, TEXTURE_FILTER_POINT);
    fontLoaded_ = true;
}

const std::string& VisualNovel::text() const {
    return chinese_ ? script_[index_].zh : script_[index_].en;
}

const std::string& VisualNovel::speaker() const {
    return chinese_ ? script_[index_].speakerZh : script_[index_].speakerEn;
}

void VisualNovel::update(float dt) {
    if (IsKeyPressed(KEY_L)) chinese_ = !chinese_;

    int total = codepointCount(text());
    shown_ += kCharsPerSec * dt;

    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (shown_ < total) shown_ = (float)total;
        else if (index_ + 1 < script_.size()) { index_++; shown_ = 0.f; }
        else init();
    }
}

void VisualNovel::render() {
    ClearBackground(Color{20, 24, 40, 255});
    DrawRectangle(60, 460, 1160, 220, Fade(BLACK, 0.8f));
    DrawRectangleLines(60, 460, 1160, 220, RAYWHITE);

    DrawTextEx(font_, speaker().c_str(), {90, 475}, kTextSize, 0, GOLD);
    std::string shown = utf8Prefix(text(), (int)shown_);
    DrawTextEx(font_, shown.c_str(), {90, 535}, kTextSize, 0, RAYWHITE);
    DrawTextEx(font_, chinese_ ? kHintZh : kHintEn, {90, 640}, kHintSize, 0, GRAY);
}
