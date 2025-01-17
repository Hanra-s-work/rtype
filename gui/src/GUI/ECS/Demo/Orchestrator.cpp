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
        PRETTY_ERROR << "The window manager has not been found" << std::endl;
        throw CustomExceptions::NoWindow("<No window to draw on>");
    }
    _window = window_ptr.value();
    PRETTY_DEBUG << "The window manager has been fetched" << std::endl;

    PRETTY_DEBUG << "Fetching the event manager" << std::endl;
    std::any evt = _ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0];
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(evt, false);
    if (!event_ptr.has_value()) {
        PRETTY_ERROR << "The event has been found" << std::endl;
        throw CustomExceptions::NoEventManager("<No events to listen on>");
    }
    _event = event_ptr.value();
    PRETTY_DEBUG << "The event manager has been fetched" << std::endl;

    PRETTY_DEBUG << "Fetching the sprites contained in the ecs array (if present)" << std::endl;
    std::vector<std::any> sprites = _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)];

    for (std::any node : sprites) {
        const std::optional<std::shared_ptr<GUI::ECS::Components::SpriteComponent>> sprite = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::SpriteComponent>>(node, false);
        if (!sprite.has_value()) {
            PRETTY_WARNING << "Sprite uncasting failed" << std::endl;
        }
        std::string name = sprite.value()->getName();
        std::string applicationContext = sprite.value()->getApplication();

        PRETTY_DEBUG << "Current sprite info { name: '" << name << "', application context: '" << applicationContext << "' }" << std::endl;

        if (
            applicationContext == "sprite42" || name == "r-typesheet42" ||
            applicationContext == "sprite42" || name == "r-typesheet42"
            ) {
            PRETTY_DEBUG << "Sprite player has been found" << std::endl;
            _spritePlayer = sprite.value();
            PRETTY_DEBUG << "Sprite player content:\n" << *_spritePlayer << std::endl;
        } else if (
            applicationContext == "sprite43_laser" || name == "sprite43_laser" ||
            applicationContext == "sprite43_laser" || name == "sprite43_laser"
            ) {
            PRETTY_DEBUG << "Sprite bullet found" << std::endl;
            _spriteBullet = sprite.value();
            PRETTY_DEBUG << "Sprite bullet content:\n" << *_spriteBullet << std::endl;
        } else if (
            applicationContext == "sprite3" || name == "sprite3" ||
            applicationContext == "r-typesheet3" || name == "r-typesheet3"
            ) {
            PRETTY_DEBUG << "Sprite bullet enemy found" << std::endl;
            _spriteBulletEnemy = sprite.value();
            PRETTY_DEBUG << "Sprite bullet enemy content:\n" << *_spriteBulletEnemy << std::endl;
        } else if (
            applicationContext == "r-typesheet13" || name == "r-typesheet13" ||
            applicationContext == "sprite13" || name == "sprite13"
            ) {
            PRETTY_DEBUG << "Sprite enemy found" << std::endl;
            _spriteEnemy = sprite.value();
            PRETTY_DEBUG << "Sprite enemy content:\n" << *_spriteEnemy << std::endl;
        }
    }
    PRETTY_DEBUG << "The sprite player has been fetched" << std::endl;

    PRETTY_DEBUG << "Checking if the elements are loaded or not" << std::endl;
    if (_spriteBullet == nullptr || _spritePlayer == nullptr || _spriteEnemy == nullptr || _spriteBulletEnemy == nullptr) {
        PRETTY_ERROR << "The sprite player, bullet, enemy or bullet enemy has not been found" << std::endl;
        throw CustomExceptions::NoSprite("<One of the sprites that the program attempted to load was missing>");
    }
    PRETTY_DEBUG << "The elements are loaded" << std::endl;

    PRETTY_DEBUG << "Spawning the player in the screen" << std::endl;
    _spawn();
    PRETTY_DEBUG << "The player has been spawned" << std::endl;

    PRETTY_DEBUG << "Spawning the enemies" << std::endl;
    const float spriteHeight = _spriteEnemy->getCollision().getHeight();
    const float spriteWidth = _spriteEnemy->getCollision().getWidth();
    const int windowWidth = spriteWidth; //_window->getDimensions().first;
    const int windowHeight = _window->getDimensions().second;
    PRETTY_DEBUG << "window height: " << windowHeight << ", window width: " << windowWidth << std::endl;
    PRETTY_DEBUG << "Sprite height: " << spriteHeight << ", sprite width: " << spriteWidth << std::endl;
    PRETTY_DEBUG << "_screenPosXOffset: " << _screenPosXOffset << ", _screenPosYOffset: " << _screenPosYOffset << std::endl;
    float posX = windowWidth;
    PRETTY_DEBUG << "posX = windowWidth (" << windowWidth << ") = " << posX << std::endl;
    PRETTY_DEBUG << "posX (" << posX << ") -= (spriteWidth (" << spriteWidth << ") + _screenPosXOffset (" << _screenPosXOffset << ")) (" << (spriteWidth + _screenPosXOffset) << ") = " << posX - (spriteWidth + _screenPosXOffset) << std::endl;
    // posX -= (spriteWidth + _screenPosXOffset);
    float posY = spriteHeight;
    PRETTY_DEBUG << "posX: " << posX << ", posY: " << posY << std::endl;
    for (unsigned int index = 0; index < 4; index++) {
        std::pair<float, float> pos = { posX - _randInt(0, spriteWidth), posY };
        PRETTY_DEBUG << "Spawning enemy : " << index << ", pos: " << pos << std::endl;
        _spawnEnemy(pos);
        posY += _randInt(spriteHeight, spriteHeight + 10);
    }
    PRETTY_DEBUG << "The enemies have been spawned" << std::endl;
};

void GUI::ECS::Demo::Orchestrator::start()
{
    PRETTY_DEBUG << "The start function has been called" << std::endl;
    _playing = true;
};

void GUI::ECS::Demo::Orchestrator::stop()
{
    PRETTY_DEBUG << "The stop function has been called" << std::endl;
    _playing = false;
};

void GUI::ECS::Demo::Orchestrator::reset()
{
    PRETTY_DEBUG << "The reset function has been called" << std::endl;
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
        PRETTY_DEBUG << "Skipping tick because we are not playing" << std::endl;
        return;
    }

    // Declaring a list to contain the bullets to remove
    std::vector<unsigned int> bulletsToRemove;

    // Tick the player logic 
    _playerBrain->tick();

    // Tick the enemy logic
    PRETTY_DEBUG << "Ennemies on screen: " << _enemyBrain.size() << std::endl;
    for (unsigned int index = 0; index < _enemyBrain.size(); index++) {
        PRETTY_DEBUG << "Ticking the enemy, index: " << index << ", name: " << _enemyBrain[index]->getSprite().getName() << std::endl;
        std::optional<GUI::ECS::Demo::Bullet> shot = _enemyBrain[index]->tick();
        if (shot.has_value()) {
            PRETTY_DEBUG << "Enemy shot a bullet, index: " << index << ", name: " << shot.value().getSprite().getName() << std::endl;
            _bullets.push_back(shot.value());
        }
    }

    // Update player movements
    if (_event->getKeys().size() > 0) {
        std::pair<float, float> position = _playerBrain->getCollision().getPosition();

        // Handle movement
        if (_event->isKeyPressed(GUI::ECS::Systems::Key::Up) && position.second > 0) {
            position.second += _stepUp;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Down) && position.second < _window->getDimensions().second - _screenPosYOffset) {
            position.second += _stepDown;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Left) && position.first > 0) {
            position.first += _stepLeft;
        } else if (_event->isKeyPressed(GUI::ECS::Systems::Key::Right) && position.first < _window->getDimensions().first - _screenPosXOffset) {
            position.first += _stepRight;
        }

        // Handle shooting
        if (_event->isKeyPressed(GUI::ECS::Systems::Key::Space)) {
            _bullets.push_back(_playerBrain->shoot());
        }

        // Update player position
        _playerBrain->setPosition(position);
    }


    // Bullets collisions
    PRETTY_DEBUG << "Bullet count : " << _bullets.size() << std::endl;
    for (unsigned int index = 0; index < _bullets.size(); index++) {
        _bullets[index].tick();
        PRETTY_DEBUG << "bullet: index: " << index << ", visible: " << Recoded::myToString(_bullets[index].isVisible()) << ", enemy: " << Recoded::myToString(_bullets[index].isEnemy()) << std::endl;
        // Skipping because the bullet is not visible
        if (!_bullets[index].isVisible()) {
            bulletsToRemove.push_back(index);
            continue;
        }
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

    // Removing bullets that are not rendered anymore
    PRETTY_DEBUG << "Bullets to be removed: list size: " << bulletsToRemove.size() << std::endl;
    for (unsigned int index = 0; index < bulletsToRemove.size(); index++) {
        PRETTY_DEBUG << "Bullet " << index << " removed" << std::endl;
        _bullets.erase(_bullets.begin() + bulletsToRemove[index]);
    }

    // Check if all the enemies are dead
    unsigned int index = 0;
    for (; index < _enemyBrain.size() && !_enemyBrain[index]->isVisible(); index++);
    if (index == _enemyBrain.size()) {
        PRETTY_DEBUG << "All the enemies are dead, the game is won" << std::endl;
        _gameWon = true;
    }
};

void GUI::ECS::Demo::Orchestrator::render()
{
    PRETTY_DEBUG << "In the render function" << std::endl;
    PRETTY_DEBUG << "_playerBrain: " << Recoded::myToString(_playerBrain->isVisible()) << ", _enemy size: " << _enemyBrain.size() << ", _bullets size: " << _bullets.size() << std::endl;
    PRETTY_DEBUG << "_playerBrain[" << _playerBrain->getSprite().getName() << "]<" << _playerBrain->getCollision().getPosition() << ">%" << _playerBrain->getCollision().getDimension() << "%:" << Recoded::myToString(_playerBrain->isVisible()) << std::endl;
    _window->draw(_playerBrain->render());
    PRETTY_DEBUG << "Going to render the ennemies" << std::endl;
    unsigned int index = 0;
    for (std::shared_ptr<GUI::ECS::Demo::EnemyBrain> item : _enemyBrain) {
        PRETTY_DEBUG << "_enemyBrain[" << item->getSprite().getName() << index << "]<" << item->getCollision().getPosition() << ">%" << item->getCollision().getDimension() << "%:" << Recoded::myToString(item->isVisible()) << std::endl;
        _window->draw(item->render());
        index++;
    }
    PRETTY_DEBUG << "Ennemies rendered" << std::endl;
    PRETTY_DEBUG << "Going to render the bullets" << std::endl;
    index = 0;
    for (GUI::ECS::Demo::Bullet item : _bullets) {
        PRETTY_DEBUG << "_bullets[" << item.getSprite().getName() << index << "]<" << item.getCollision().getPosition() << ">%" << item.getCollision().getDimension() << "%(" << Recoded::myToString(item.isEnemy()) << "):" << Recoded::myToString(item.isVisible()) << std::endl;
        _window->draw(item.render());
        index++;
    }
    PRETTY_DEBUG << "Bullets rendred" << std::endl;
    PRETTY_DEBUG << "Out of render()" << std::endl;
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
    PRETTY_DEBUG << "In _spawn function in charge of creating the user" << std::endl;
    if (_spritePlayer == nullptr) {
        PRETTY_ERROR << "The _spritePlayer is set to nullptr" << std::endl;
        throw CustomExceptions::NoSprite("<Sprite player not found>");
    }
    if (_spriteBullet == nullptr) {
        PRETTY_ERROR << "The _spriteBullet is set to nullptr" << std::endl;
        throw CustomExceptions::NoSprite("<Sprite bullet not found>");
    }
    PRETTY_DEBUG << "The _playerBrain shared pointer is going to be created" << std::endl;
    _playerBrain = std::make_shared<GUI::ECS::Demo::PlayerBrain>();
    PRETTY_DEBUG << "The _playerBrain shared pointer has been created" << std::endl;
    _playerBrain->setSprite(_spritePlayer, _spriteBullet);
    PRETTY_DEBUG << "The _playerBrain has been set with the sprites of bullet and player" << std::endl;
    _playerBrain->setDimension({ 2,2 });
}

void GUI::ECS::Demo::Orchestrator::_kill()
{
    PRETTY_DEBUG << "The _kill function has been called" << std::endl;
    _playerBrain.reset();
    _enemyBrain.clear();
};

void GUI::ECS::Demo::Orchestrator::_spawnEnemy(const std::pair<float, float> pos)
{
    PRETTY_DEBUG << "In spawn enemy" << std::endl;
    if (_spriteEnemy == nullptr) {
        PRETTY_ERROR << "The _spriteEnemy is set to nullptr" << std::endl;
        throw CustomExceptions::NoSprite("<Sprite enemy not found>");
    }
    if (_spriteBulletEnemy == nullptr) {
        PRETTY_ERROR << "The _spriteBulletEnemy is set to nullptr" << std::endl;
        throw CustomExceptions::NoSprite("<Sprite bullet enemy not found>");
    }
    PRETTY_DEBUG << "The _enemyBrain shared pointer is going to be created" << std::endl;
    std::shared_ptr<GUI::ECS::Demo::EnemyBrain> enemy = std::make_shared<GUI::ECS::Demo::EnemyBrain>();
    PRETTY_DEBUG << "The _enemyBrain shared pointer has been created" << std::endl;
    enemy->setSprite(_spriteEnemy, _spriteBulletEnemy);
    PRETTY_DEBUG << "The sprite enemy and sprite bullet enemy has been set" << std::endl;
    enemy->setPosition(pos);
    PRETTY_DEBUG << "The enemy has been set with the position: " << pos << std::endl;
    enemy->setVisible(true);
    // enemy->setDimension({ 10,10 });
    PRETTY_DEBUG << "The enemy is visible" << std::endl;
    _enemyBrain.push_back(enemy);
    PRETTY_DEBUG << "The enemy has been added to the _enemyBrain" << std::endl;
}

const int GUI::ECS::Demo::Orchestrator::_randInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}



