#pragma once

#include <forward_list>
#include "GameMessage.hpp"

class Registry;
class EventDispatcher;

class Game {
public:
    Game();
    ~Game();

    void update(float _deltaTime);
    std::forward_list<GameMessage> &getGameStates(void);

    void onEventReceived(const GameMessage& event);
private:
    Registry *_game;
    EventDispatcher *_dispatcher;
    std::forward_list<GameMessage> _events;
};
