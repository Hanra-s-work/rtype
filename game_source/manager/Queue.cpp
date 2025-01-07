#include "Queue.hpp"

void Queue::push(const GameMessage& item) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(item);
    _condition.notify_one();
}

std::optional<GameMessage> Queue::pop() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty()) return std::nullopt;
    GameMessage item = _queue.front();
    _queue.pop();
    return item;
}

GameMessage Queue::waitAndPop() {
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this] { return !_queue.empty(); });
    GameMessage item = _queue.front();
    _queue.pop();
    return item;
}

bool Queue::isEmpty() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.empty();
}