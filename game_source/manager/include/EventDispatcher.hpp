#pragma once

#include <functional>
#include "GameMessage.hpp"

class EventDispatcher {
public:
    using Callback = std::function<void(const GameMessage&)>;

    void subscribe(Callback callback) {
        listener = callback;
    }

    void notify(const GameMessage& event) {
        if (listener)
            listener(event);
    }

private:
    Callback listener;
};