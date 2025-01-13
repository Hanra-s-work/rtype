#include "Game.hpp"
#include "Registry.hpp"
#include "EventDispatcher.hpp"
#include "../ECS/include/Time.hpp"
#include "Queue.hpp"

Game::Game()
{
    _dispatcher = new EventDispatcher();
    _queue = new Queue();
    _dispatcher->subscribe([this](const GameMessage& event) {
        this->onGameEventReceived(event);
    });
    _game = new Registry(_dispatcher, _queue);
}

Game::~Game()
{
    delete _game;
    delete _dispatcher;
    delete _queue;
}

void Game::update(float _deltaTime)
{
    Time::deltaTime = _deltaTime;
    _game->run_systems();
}

std::forward_list<std::string> Game::getGameEvents(void)
{
    std::forward_list<std::string> serializedMessages;
    for (const auto& event : _eventsFromGame) {
        std::ostringstream oss;
        serialize(event, oss);
        serializedMessages.push_front(oss.str());
    }
    _eventsFromGame.clear();
    return serializedMessages;
}

void Game::onGameEventReceived(const GameMessage &event)
{
    _eventsFromGame.push_front(event);
}

void Game::onServerEventReceived(std::string &event)
{
    std::istringstream iss(event);
    GameMessage loadedMessage = deserialize(iss);
    _eventsFromServer.push_front(loadedMessage);
    _queue->push(loadedMessage);
}
