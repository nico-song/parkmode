#pragma once
#include <deque>
#include <mutex>
#include <optional>

template <typename T>
class EventQueue {
public:
    void push(T item) {
        std::lock_guard<std::mutex> lock(mutex_);
        items_.push_back(std::move(item));
    }

    std::optional<T> tryPop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (items_.empty()) return std::nullopt;
        T item = std::move(items_.front());
        items_.pop_front();
        return item;
    }

private:
    std::mutex mutex_;
    std::deque<T> items_;
};
