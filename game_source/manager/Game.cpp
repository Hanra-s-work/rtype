#include "Game.hpp"
#include "Registry.hpp"
#include "EventDispatcher.hpp"
#include "Time.hpp"
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

void Game::serialize(const GameMessage& message, std::ostringstream& os)
{
    os.write(reinterpret_cast<const char*>(&message.type), sizeof(message.type));
    os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
    os.write(reinterpret_cast<const char*>(&message.msg.status), sizeof(message.msg.status));
    os.write(reinterpret_cast<const char*>(&message.msg.asset_id), sizeof(message.msg.asset_id));
    os.write(reinterpret_cast<const char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
    os.write(reinterpret_cast<const char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
}

GameMessage Game::deserialize(std::istringstream& is)
{
    GameMessage message;
    is.read(reinterpret_cast<char*>(&message.type), sizeof(message.type));
    is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
    is.read(reinterpret_cast<char*>(&message.msg.status), sizeof(message.msg.status));
    is.read(reinterpret_cast<char*>(&message.msg.asset_id), sizeof(message.msg.asset_id));
    is.read(reinterpret_cast<char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
    is.read(reinterpret_cast<char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
    return message;
}
