#include "Game.hpp"
#include "Registry.hpp"
#include "EventDispatcher.hpp"
#include "Time.hpp"

Game::Game()
{
    _dispatcher = new EventDispatcher();
    _dispatcher->subscribe([this](const GameMessage& event) {
        this->onEventReceived(event);
    });
    _game = new Registry(_dispatcher);
}

Game::~Game()
{
    delete _game;
    delete _dispatcher;
}

void Game::update(float _deltaTime)
{
    Time::deltaTime = _deltaTime;
    _game->run_systems();
}

std::forward_list<GameMessage> &Game::getGameEvents(void)
{
    return _events;
}

void Game::onEventReceived(const GameMessage &event)
{
    _events.push_front(event);
}
