/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Orchestrator.cpp
*/

/**
 * @file Orchestrator.cpp
 *
 * @brief File that will contain the code for functions of the orchestrator class
 */

#include "GUI/ECS/Demo/Orchestrator.hpp"


void GUI::ECS::Demo::Orchestrator::initialiseClass(std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities)
{
    PRETTY_DEBUG << "Resetting the values stored in the class" << std::endl;
    _ecsEntities = ecsEntities;
    _event.reset();
    _window.reset();
    _spriteBullet.reset();
    _spritePlayer.reset();
    _spriteEnemy.reset();
    _playerBrain.reset();
    PRETTY_DEBUG << "The values stored in the class have been reset" << std::endl;

    PRETTY_DEBUG << "Fetching the window manager" << std::endl;
    std::any win = _ecsEntities[typeid(GUI::ECS::Systems::Window)][0];
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> window_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>>(win, false);
    if (!window_ptr.has_value()) {
        throw CustomExceptions::NoWindow("<No window to draw on>");
    }
    _window = window_ptr.value();
    PRETTY_DEBUG << "The window manager has been fetched" << std::endl;

    PRETTY_DEBUG << "Fetching the event manager" << std::endl;
    std::any evt = _ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0];
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(evt, false);
    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<No events to listen on>");
    }
    _event = event_ptr.value();
    PRETTY_DEBUG << "The event manager has been fetched" << std::endl;

    PRETTY_DEBUG << "Fetching the sprites of contained in the ecs array (if present)" << std::endl;
    std::vector<std::any> sprites = _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)];

    for (std::any node : sprites) {
        const std::optional<std::shared_ptr<GUI::ECS::Components::SpriteComponent>> sprite = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::SpriteComponent>>(node, false);
        if (!sprite.has_value()) {
            PRETTY_WARNING << "Sprite uncasting failed" << std::endl;
        }
        std::string name = sprite.value()->getName();
        std::string applicationContext = sprite.value()->getApplication();
        if (
            applicationContext == "sprite42" || applicationContext == "r-typesheet42" ||
            name == "sprite42" || name == "r-typesheet42"
            ) {
            _spritePlayer = sprite.value();
        } else if (
            applicationContext == "sprite43_laser" || applicationContext == "sprite43_laser" ||
            name == "sprite43_laser" || name == "sprite43_laser"
            ) {
            _spriteBullet = sprite.value();
        } else if (
            applicationContext == "sprite3" || applicationContext == "sprite3" ||
            name == "r-typesheet3" || name == "r-typesheet3"
            ) {
            _spriteBulletEnemy = sprite.value();
        } else if (
            name == "sprite13" || name == "sprite13" ||
            applicationContext == "r-typesheet13" || applicationContext == "r-typesheet13"
            ) {
            _spriteEnemy = sprite.value();
        }
    }
    PRETTY_DEBUG << "The sprite player has been fetched" << std::endl;

    PRETTY_DEBUG << "Spawning the player in the screen" << std::endl;
    _spawn();
    PRETTY_DEBUG << "The player has been spawned" << std::endl;

    PRETTY_DEBUG << "Spawning the enemies" << std::endl;
    const float spriteHeight = _spriteEnemy->getCollision().getHeight();
    const float spriteWidth = _spriteEnemy->getCollision().getWidth();
    float posX = _window->getDimensions().first - spriteWidth;
    float posY = spriteHeight;
    for (unsigned int index = 0; index < 4; index++) {
        _spawnEnemy({ posX - _randInt(0, spriteWidth), posY });
        posY += _randInt(spriteHeight, spriteHeight + 10);
    }
    PRETTY_DEBUG << "The enemies have been spawned" << std::endl;
};

void GUI::ECS::Demo::Orchestrator::start()
{
    _playing = true;
};

void GUI::ECS::Demo::Orchestrator::stop()
{
    _playing = false;
};

void GUI::ECS::Demo::Orchestrator::reset()
{
    _kill();
    _spawn();
    stop();
    _gameOver = false;
    _gameWon = false;
};

void GUI::ECS::Demo::Orchestrator::tick()
{
    // Check if the class is set to calculate it's move
    if (!_playing) {
        return;
    }

    // Tick the player logic 
    _playerBrain->tick();
    for (unsigned int index = 0; index < _enemyBrain.size(); index++) {
        std::optional<GUI::ECS::Demo::Bullet> shot = _enemyBrain[index]->tick();
        if (shot.has_value()) {
            _bullets.push_back(shot.value());
        }
    }

    // Update player movements
    if (_event->getKeys().size() > 0) {
        std::pair<float, float> position = _playerBrain->getCollision().getPosition();
        if (_event->isKeyPressed(GUI::ECS::Systems::Key::Up) && position.second > 0) {
            position.second += _stepUp;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Down) && position.second < _window->getDimensions().second) {
            position.second += _stepDown;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Left) && position.second > 0) {
            position.second += _stepLeft;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Right) && position.first < _window->getDimensions().first) {
            position.first += _stepRight;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Space)) {
            _bullets.push_back(_playerBrain->shoot());
        }
        _playerBrain->setPosition(position);
    }

    // Bullets collisions
    for (unsigned int index = 0; index < _bullets.size(); index++) {
        _bullets[index].tick();
        // Skipping because the bullet is not visible
        if (!_bullets[index].isVisible())
            continue;
        // The bullet is comming from a player, if so check the enemies
        if (!_bullets[index].isEnemy()) {
            for (unsigned int eIndex = 0; eIndex < _enemyBrain.size(); eIndex++) {
                // Check if the bullet has hit it's target and that the enemy is still alive
                if (_bullets[index].isColliding(_enemyBrain[eIndex]->getCollision())) {
                    // hide the bullet an check the health
                    _bullets[index].setVisible(false);
                    if (_enemyBrain[eIndex]->getHealth() <= 0) {
                        _enemyBrain[eIndex]->setVisible(false);
                    } else {
                        _enemyBrain[eIndex]->setHealth(_enemyBrain[eIndex]->getHealth() - _bullets[index].getDamage());
                    }
                }
            }
        } else {
            if (_playerBrain->isColliding(_bullets[index].getCollision())) {
                _playerBrain->setHealth(_playerBrain->getHealth() - _bullets[index].getDamage());
                // Check if the player is dead.
                if (_playerBrain->getHealth() < 0) {
                    _gameOver = true;
                    return;
                }
                _bullets[index].setVisible(false);
            }
        }
    }

    // Check if all the enemies are dead
    unsigned int index = 0;
    for (; index < _enemyBrain.size() && !_enemyBrain[index]->isVisible(); index++);
    if (index == _enemyBrain.size()) {
        _gameWon = true;
    }
};

void GUI::ECS::Demo::Orchestrator::render()
{
    _window->draw(_playerBrain->render());
    for (std::shared_ptr<GUI::ECS::Demo::EnemyBrain> item : _enemyBrain) {
        _window->draw(item->render());
    }
    for (GUI::ECS::Demo::Bullet item : _bullets) {
        _window->draw(item.render());
    }
};

const bool GUI::ECS::Demo::Orchestrator::isGameOver() const
{
    return _gameOver;
}

const bool GUI::ECS::Demo::Orchestrator::isGameWon() const
{
    return _gameOver;
}

void GUI::ECS::Demo::Orchestrator::_spawn()
{
    if (_spritePlayer == nullptr) {
        throw CustomExceptions::NoSprite("<Sprite player not found>");
    }
    if (_spriteBullet == nullptr) {
        throw CustomExceptions::NoSprite("<Sprite bullet not found>");
    }
    _playerBrain = std::make_shared<GUI::ECS::Demo::PlayerBrain>();
    _playerBrain->setSprite(*_spritePlayer, *_spriteBullet);
}

void GUI::ECS::Demo::Orchestrator::_kill()
{
    _playerBrain.reset();
    _enemyBrain.clear();
};

void GUI::ECS::Demo::Orchestrator::_spawnEnemy(const std::pair<float, float> pos)
{
    if (_spriteEnemy == nullptr) {
        throw CustomExceptions::NoSprite("<Sprite enemy not found>");
    }
    if (_spriteBulletEnemy == nullptr) {
        throw CustomExceptions::NoSprite("<Sprite bullet enemy not found>");
    }
    std::shared_ptr<GUI::ECS::Demo::EnemyBrain> enemy = std::make_shared<GUI::ECS::Demo::EnemyBrain>();
    enemy->setSprite(*_spriteEnemy, *_spriteBulletEnemy);
    enemy->setPosition(pos);
    enemy->setVisible(true);
    _enemyBrain.push_back(enemy);
}

const int GUI::ECS::Demo::Orchestrator::_randInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}



