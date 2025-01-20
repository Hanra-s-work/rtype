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

#include "GUI/ECS/Online/Orchestrator.hpp"

GUI::ECS::Online::Orchestrator::Orchestrator(const std::uint32_t entityId)
    : EntityNode(entityId)
{
};

void GUI::ECS::Online::Orchestrator::initialiseClass(std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities)
{
    PRETTY_DEBUG << "Resetting the values stored in the class" << std::endl;
    _ecsEntities = ecsEntities;
    _event.reset();
    _window.reset();
    _spriteBullet.reset();
    _spritePlayer.reset();
    _spriteEnemy.reset();
    _playerBrain.clear();
    _enemyBrain.clear();
    _enemyBullets.clear();
    _playerBullets.clear();
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
    const std::vector<std::any> sprites = _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)];

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
            applicationContext == "sprite30c" || name == "sprite30c" ||
            applicationContext == "typesheet30c" || name == "typesheet30c"
            ) {
            PRETTY_DEBUG << "Sprite bullet found" << std::endl;
            _spriteBullet = sprite.value();
            _spriteBullet->forceTick();
            PRETTY_DEBUG << "Sprite bullet content:\n" << *_spriteBullet << std::endl;
        } else if (
            applicationContext == "sprite3c" || name == "sprite3c" ||
            applicationContext == "r-typesheet3c" || name == "r-typesheet3c"
            ) {
            PRETTY_DEBUG << "Sprite bullet enemy found" << std::endl;
            _spriteBulletEnemy = sprite.value();
            _spriteBulletEnemy->forceTick();
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
    _setTheScene();
    _setTextComponents();
    PRETTY_DEBUG << "Fetching a background for the game" << std::endl;
    const std::vector<std::any> backgrounds = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];
    PRETTY_DEBUG << "Declaring the ressource required for the settings menu to have a background" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundItem;
    PRETTY_DEBUG << "Declared the ressource required for the settings menu to have a background" << std::endl;

    for (std::any backgroundCast : backgrounds) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(backgroundCast, false);
        if (!backgroundCapsule.has_value()) {
            continue;
        }
        if (
            backgroundCapsule.value()->getApplication() == "space" || backgroundCapsule.value()->getName() == "space" ||
            backgroundCapsule.value()->getApplication() == "Space" || backgroundCapsule.value()->getName() == "Space"
            ) {
            backgroundItem.emplace(backgroundCapsule.value());
        }
    }
    PRETTY_DEBUG << "Background fetched if present" << std::endl;
};

void GUI::ECS::Online::Orchestrator::setNetworkClass(const std::shared_ptr<GUI::Network::ThreadCapsule> &network)
{
    if (network == nullptr) {
        throw CustomExceptions::NoNetworkClass("<Network class not found>");
    }
    _network.emplace(network);
}

void GUI::ECS::Online::Orchestrator::start()
{
    PRETTY_DEBUG << "The start function has been called" << std::endl;
    _playing = true;
    _gameOver = false;
    _gameWon = false;
};

void GUI::ECS::Online::Orchestrator::stop()
{
    PRETTY_DEBUG << "The stop function has been called" << std::endl;
    _playing = false;
    _gameOver = false;
    _gameWon = false;
};

void GUI::ECS::Online::Orchestrator::reset()
{
    PRETTY_DEBUG << "The reset function has been called" << std::endl;
    _gameOver = false;
    _gameWon = false;
    _kill();
    _setTheScene();
    stop();
};

void GUI::ECS::Online::Orchestrator::tick(const std::vector<GUI::Network::MessageNode> &packets)
{
    // Check if the class is set to calculate it's move
    if (!_playing) {
        PRETTY_DEBUG << "Skipping tick because we are not playing" << std::endl;
        return;
    }

    PRETTY_DEBUG << "Orchestrator dump (before tick):\n" << getInfo(0) << std::endl;

    // update entities based on packets received
    PRETTY_DEBUG << "Going to process received packets" << std::endl;
    for (const GUI::Network::MessageNode &packet : packets) {
        PRETTY_DEBUG << "Packet received: " << Recoded::myToString(packet) << std::endl;
        switch (packet.type) {
            case GUI::Network::MessageType::P_MOVE:
                _setPosition(packet.id, packet.info.coords);
                break;
            case GUI::Network::MessageType::P_SHOOT:
                /* animation */
                break;
            case GUI::Network::MessageType::P_SPAWN:
                if (packet.info.assetId == static_cast<int>(GUI::ECS::GameComponents::EntityType::ENEMY)) {
                    _spawnEnemy(packet.id, packet.info.coords);
                } else if (packet.info.assetId == static_cast<int>(GUI::ECS::GameComponents::EntityType::PLAYER)) {
                    _spawn(packet.id, packet.info.coords);
                } else if (packet.info.assetId == static_cast<int>(GUI::ECS::GameComponents::EntityType::LASER_ENEMY)) {
                    _spawnEnemyBullet(packet.id, packet.info.coords);
                } else {
                    _spawnFriendBullet(packet.id, packet.info.coords);
                }
                break;
            case GUI::Network::MessageType::P_KILL:
                _killEntity(packet.id);
                break;
            case GUI::Network::MessageType::P_DAMAGE:
                /* animation */
                break;
            default:
                break;
        }
    }
    PRETTY_DEBUG << "Processed received packets" << std::endl;

    // Update player movements
    PRETTY_DEBUG << "Going to process the events" << std::endl;
    if (_event->getKeys().size() > 0) {
        PRETTY_DEBUG << "Checking if the player id: " << Recoded::myToString(_playerId) << " is present" << std::endl;
        if (_playerId < _playerBrain.size()) {
            std::pair<float, float> position = _playerBrain[_playerId]->getCollision().getPosition();

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
            PRETTY_DEBUG << "Checking if the player has shot" << std::endl;
            if (_event->isKeyPressed(GUI::ECS::Systems::Key::Space)) {
                PRETTY_DEBUG << "The player has shot" << std::endl;
                if (_playerId < _playerBrain.size()) {
                    PRETTY_DEBUG << "Player shot" << std::endl;
                    _sendMessage({ GUI::Network::MessageType::P_SHOOT, _playerBrain[_playerId]->getEntityNodeId(), {0, 0, "", {0, 0}} });
                    _shootSound();
                } else {
                    PRETTY_WARNING << "There is no player to update" << std::endl;
                    throw CustomExceptions::NoSprite("<No player>");
                }
            }
            PRETTY_DEBUG << "Checked if the player had shot" << std::endl;

            // Update player position
            PRETTY_DEBUG << "Updating the player's position" << std::endl;
            if (_playerId < _playerBrain.size()) {
                _playerBrain[_playerId]->setPosition(position);
                _sendMessage({ GUI::Network::MessageType::P_MOVE, _playerBrain[_playerId]->getEntityNodeId(), {0, 0, "", {position.first, position.second}} });
            } else {
                PRETTY_WARNING << "There is no player to update" << std::endl;
                throw CustomExceptions::NoSprite("<No player>");
            }
            PRETTY_DEBUG << "The player position has been updated" << std::endl;
        } else {
            PRETTY_WARNING << "There is no player to update" << std::endl;
            throw CustomExceptions::NoSprite("<No player>");
        }
    }
    PRETTY_DEBUG << "Updating the enemy count component (if present)" << std::endl;
    if (_remainingEnemies.has_value()) {
        PRETTY_DEBUG << "Remaining enemy counter updated" << std::endl;
        _remainingEnemies.value()->setText("Remaining ennemies: " + Recoded::myToString(_activeEnemies));
    }
    PRETTY_DEBUG << "Orchestrator dump (after tick): \n" << getInfo(0) << std::endl;
};

void GUI::ECS::Online::Orchestrator::render()
{
    PRETTY_DEBUG << "In the render function" << std::endl;
    PRETTY_DEBUG << "Displaying the background image (if present)" << std::endl;
    if (_backgroundItem.has_value()) {
        PRETTY_DEBUG << "The background is present, displaying" << std::endl;
        _window->draw(*(_backgroundItem.value()));
    } else {
        PRETTY_WARNING << "There is no background to display" << std::endl;
    }
    PRETTY_DEBUG << "Displayed the background image (if present)" << std::endl;
    PRETTY_DEBUG << "Going to render the players" << std::endl;
    unsigned int index = 0;
    for (std::shared_ptr<GUI::ECS::Online::PlayerBrain> item : _playerBrain) {
        std::string name = item->getSprite().getName();
        std::pair<float, float> pos = item->getCollision().getPosition();
        std::pair<float, float> dim = item->getCollision().getDimension();
        bool visible = item->isVisible();
        PRETTY_DEBUG << "_playerBrain[" << name << index << "]<" << pos << ">%" << dim << "%:" << Recoded::myToString(visible) << std::endl;
        _window->draw(item->render());
        index++;
    }
    PRETTY_DEBUG << "Players rendered" << std::endl;
    PRETTY_DEBUG << "Going to render the ennemies" << std::endl;
    index = 0;
    for (std::shared_ptr<GUI::ECS::Online::EnemyBrain> item : _enemyBrain) {
        std::string name = item->getSprite().getName();
        std::pair<float, float> pos = item->getCollision().getPosition();
        std::pair<float, float> dim = item->getCollision().getDimension();
        bool visible = item->isVisible();
        PRETTY_DEBUG << "_enemyBrain[" << name << index << "]<" << pos << ">%" << dim << "%:" << Recoded::myToString(visible) << std::endl;
        _window->draw(item->render());
        index++;
    }
    PRETTY_DEBUG << "Ennemies rendered" << std::endl;
    PRETTY_DEBUG << "Going to render the player bullets" << std::endl;
    index = 0;
    for (GUI::ECS::Online::Bullet item : _playerBullets) {
        std::string name = item.getSprite().getName();
        std::pair<float, float> pos = item.getCollision().getPosition();
        std::pair<float, float> dim = item.getCollision().getDimension();
        bool enemy = item.isEnemy();
        bool visible = item.isVisible();
        PRETTY_DEBUG << "_playerBullets[" << name << index << "]<" << pos << ">%" << dim << "%(" << Recoded::myToString(enemy) << "):" << Recoded::myToString(visible) << std::endl;
        _window->draw(item.render());
        index++;
    }
    PRETTY_DEBUG << "Player bullets rendred" << std::endl;
    PRETTY_DEBUG << "Going to render the enemy bullets" << std::endl;
    index = 0;
    for (GUI::ECS::Online::Bullet item : _enemyBullets) {
        std::string name = item.getSprite().getName();
        std::pair<float, float> pos = item.getCollision().getPosition();
        std::pair<float, float> dim = item.getCollision().getDimension();
        bool enemy = item.isEnemy();
        bool visible = item.isVisible();
        PRETTY_DEBUG << "_enemyBullets[" << name << index << "]<" << pos << ">%" << dim << "%(" << Recoded::myToString(enemy) << "):" << Recoded::myToString(visible) << std::endl;
        _window->draw(item.render());
        index++;
    }
    PRETTY_DEBUG << "Enemy bullets rendred" << std::endl;
    PRETTY_DEBUG << "Rendering the overlay text (if present)" << std::endl;
    if (_remainingEnemies.has_value()) {
        PRETTY_DEBUG << "Remaining ennemies has a value, displaying" << std::endl;
        _window->draw(*(_remainingEnemies.value()));
    }
    PRETTY_DEBUG << "Displayed the overlay text (if present)" << std::endl;
    PRETTY_DEBUG << "Out of render()" << std::endl;
};

const bool GUI::ECS::Online::Orchestrator::isGameOver() const
{
    return _gameOver;
}

const bool GUI::ECS::Online::Orchestrator::isGameWon() const
{
    return _gameWon;
}


const std::string GUI::ECS::Online::Orchestrator::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Player brain:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Playing: '" + Recoded::myToString(_playing) + "'\n";
    result += indentation + "- Game Won: '" + Recoded::myToString(_gameWon) + "'\n";
    result += indentation + "- Game Over: '" + Recoded::myToString(_gameOver) + "'\n";
    result += indentation + "- Step Up: '" + Recoded::myToString(_stepUp) + "'\n";
    result += indentation + "- Step Down: '" + Recoded::myToString(_stepDown) + "'\n";
    result += indentation + "- Step Left: '" + Recoded::myToString(_stepLeft) + "'\n";
    result += indentation + "- Step Right: '" + Recoded::myToString(_stepRight) + "'\n";
    result += indentation + "- Screen Position X Offset: '" + Recoded::myToString(_screenPosXOffset) + "'\n";
    result += indentation + "- Screen Position Y Offset: '" + Recoded::myToString(_screenPosYOffset) + "'\n";
    result += indentation + "- Active Enemies: '" + Recoded::myToString(_activeEnemies) + "'\n";
    result += indentation + "- Player Id: '" + Recoded::myToString(_playerId) + "'\n";
    result += indentation + "- Remaining enemies (has value): '" + Recoded::myToString(_remainingEnemies.has_value()) + "'\n";
    if (_remainingEnemies.has_value()) {
        result += indentation + "- Remaining enemies: {\n" + _remainingEnemies.value()->getInfo(indent + 1) + indentation + "}\n";
    }
    result += indentation + "- background item (has value): '" + Recoded::myToString(_backgroundItem.has_value()) + "'\n";
    if (_backgroundItem.has_value()) {
        result += indentation + "- background item: {\n" + _backgroundItem.value()->getInfo(indent + 1) + indentation + "}\n";
    }
    result += indentation + "- Sprite Bullet: {\n" + _spriteBullet->getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Sprite Bullet Enemy: {\n" + _spriteBulletEnemy->getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Sprite Player: {\n" + _spritePlayer->getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Sprite Enemy: {\n" + _spriteEnemy->getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Enemy Bullets: {\n";
    for (unsigned int index = 0; index < _enemyBullets.size(); index++) {
        result += indentation + "\t" + Recoded::myToString(index) + ": {\n";
        result += _enemyBullets[index].getInfo(indent + 2);
        result += indentation + "\t}\n";
    }
    result += indentation + "}\n";
    result += indentation + "- Window: {\n" + _window->getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Event: {\n" + _event->getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Player Bullets: {\n";
    for (unsigned int index = 0; index < _playerBullets.size(); index++) {
        result += indentation + "\t" + Recoded::myToString(index) + ": {\n";
        result += _playerBullets[index].getInfo(indent + 2);
        result += indentation + "\t}\n";
    }
    result += indentation + "}\n";
    result += indentation + "- Player Brains: {\n";
    for (unsigned int index = 0; index < _playerBrain.size(); index++) {
        result += indentation + "\t" + Recoded::myToString(index) + ": {\n";
        result += _playerBrain[index]->getInfo(indent + 2);
        result += indentation + "\t}\n";
    }
    result += indentation + "}\n";
    result += indentation + "- Enemy Brains: {\n";
    for (unsigned int index = 0; index < _enemyBrain.size(); index++) {
        result += indentation + "\t" + Recoded::myToString(index) + ": {\n";
        result += _enemyBrain[index]->getInfo(indent + 2);
        result += indentation + "\t}\n";
    }
    result += indentation + "}\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    return result;
}


void GUI::ECS::Online::Orchestrator::_spawn(const std::uint32_t id, const std::pair<float, float> &pos)
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
    std::shared_ptr<GUI::ECS::Online::PlayerBrain> playerEntity = std::make_shared<GUI::ECS::Online::PlayerBrain>(id);
    PRETTY_DEBUG << "The playerEntity shared pointer has been created" << std::endl;
    playerEntity->setSprite(_spritePlayer, _spriteBullet);
    PRETTY_DEBUG << "The playerEntity has been set with the sprites of bullet and player" << std::endl;
    playerEntity->setDimension({ 2,2 });
    playerEntity->setPosition(pos);
    playerEntity->setBulletSize({ 0.5,0.5 });
    _playerBrain.push_back(playerEntity);
    PRETTY_DEBUG << "Friend spawned" << std::endl;
};

void GUI::ECS::Online::Orchestrator::_spawnFriendBullet(const std::uint32_t id, const std::pair<float, float> &pos)
{
    PRETTY_DEBUG << "In _spawnFriendBullet function in charge of creating the user" << std::endl;
    if (_spriteBullet == nullptr) {
        PRETTY_ERROR << "The _spriteBullet is set to nullptr" << std::endl;
        throw CustomExceptions::NoSprite("<Sprite bullet not found>");
    }
    PRETTY_DEBUG << "The _spawnFriendBullet shared pointer is going to be created" << std::endl;
    const bool fromEnemy = false;
    GUI::ECS::Online::Bullet bullet(id);
    bullet.setSprite(*_spriteBullet);
    bullet.setEnemy(fromEnemy);
    bullet.setPosition(pos);
    bullet.setDamage(5);
    bullet.setDirection({ 1,0 });
    bullet.setSpeed(1);
    _playerBullets.push_back(bullet);
    PRETTY_DEBUG << "Friend bullet created" << std::endl;
};

void GUI::ECS::Online::Orchestrator::_spawnEnemyBullet(const std::uint32_t id, const std::pair<float, float> &pos)
{
    PRETTY_DEBUG << "In _spawnEnemyBullet function in charge of creating the user" << std::endl;
    if (_spriteBullet == nullptr) {
        PRETTY_ERROR << "The _spriteBullet is set to nullptr" << std::endl;
        throw CustomExceptions::NoSprite("<Sprite bullet not found>");
    }
    PRETTY_DEBUG << "The _spawnEnemyBullet shared pointer is going to be created" << std::endl;
    const bool fromEnemy = true;
    GUI::ECS::Online::Bullet bullet(id);
    bullet.setSprite(*_spriteBullet);
    bullet.setEnemy(fromEnemy);
    bullet.setPosition(pos);
    bullet.setDamage(5);
    bullet.setDirection({ 1,0 });
    bullet.setSpeed(1);
    _enemyBullets.push_back(bullet);
    PRETTY_DEBUG << "Enemy bullet created" << std::endl;
};


void GUI::ECS::Online::Orchestrator::_setPosition(const std::uint32_t id, const std::pair<float, float> &pos)
{
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    std::size_t entityIndex = -1;
    for (std::size_t i = 0; i < _playerBrain.size(); i++) {
        if (_playerBrain[i]->getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _playerBrain[entityIndex]->setPosition(pos);
        return;
    }
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    entityIndex = -1;
    for (std::size_t i = 0; i < _enemyBrain.size(); i++) {
        if (_enemyBrain[i]->getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _enemyBrain[entityIndex]->setPosition(pos);
        return;
    }
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    entityIndex = -1;
    for (std::size_t i = 0; i < _playerBullets.size(); i++) {
        if (_playerBullets[i].getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _playerBullets[entityIndex].setPosition(pos);
        return;
    }
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    entityIndex = -1;
    for (std::size_t i = 0; i < _enemyBullets.size(); i++) {
        if (_enemyBullets[i].getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _enemyBullets[entityIndex].setPosition(pos);
        return;
    }
    PRECISE_DEBUG << Recoded::myToString(id) << " was not found, thus not moved" << std::endl;
}

void GUI::ECS::Online::Orchestrator::_killEntity(const std::uint32_t id)
{
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    std::size_t entityIndex = -1;
    for (std::size_t i = 0; i < _playerBrain.size(); i++) {
        if (_playerBrain[i]->getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _playerBrain.erase(_playerBrain.begin() + entityIndex);
        return;
    }
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    entityIndex = -1;
    for (std::size_t i = 0; i < _enemyBrain.size(); i++) {
        if (_enemyBrain[i]->getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _enemyBrain.erase(_enemyBrain.begin() + entityIndex);
        _activeEnemies -= 1;
        return;
    }
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    entityIndex = -1;
    for (std::size_t i = 0; i < _playerBullets.size(); i++) {
        if (_playerBullets[i].getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _playerBullets.erase(_playerBullets.begin() + entityIndex);
        return;
    }
    PRETTY_DEBUG << "Checking if " << Recoded::myToString(id) << " is present in the vector" << std::endl;
    entityIndex = -1;
    for (std::size_t i = 0; i < _enemyBullets.size(); i++) {
        if (_enemyBullets[i].getEntityNodeId() == id) {
            PRETTY_DEBUG << Recoded::myToString(id) << " is present in the vector, marking for removal" << std::endl;
            entityIndex = i;
            break;
        }
    }
    if (entityIndex != -1) {
        PRETTY_DEBUG << "Removing " << Recoded::myToString(entityIndex) << std::endl;
        _enemyBullets.erase(_enemyBullets.begin() + entityIndex);
        return;
    }
    PRECISE_DEBUG << Recoded::myToString(id) << " was not present, thus not removed." << std::endl;
}

void GUI::ECS::Online::Orchestrator::_sendMessage(const GUI::Network::MessageNode &node)
{
    if (!_network.has_value()) {
        PRETTY_CRITICAL << "There is no network manager to use to send packets" << std::endl;
        throw CustomExceptions::NoNetworkClass("<No network manager for the online brain>");
    }
    PRETTY_DEBUG << "Sending message" << std::endl;
    _network.value()->sendMessage(node);
}

void GUI::ECS::Online::Orchestrator::_kill()
{
    PRETTY_DEBUG << "The _kill function has been called" << std::endl;
    for (unsigned int index = 0; index < _playerBrain.size(); index++) {
        PRETTY_DEBUG << "Resetting players: " << index << std::endl;
        _playerBrain[index].reset();
    }
    _playerBrain.clear();
    for (unsigned int index = 0; index < _enemyBrain.size(); index++) {
        PRETTY_DEBUG << "Resetting enemy: " << index << std::endl;
        _enemyBrain[index].reset();
    }
    PRETTY_DEBUG << "Clearing enemy vector" << std::endl;
    _enemyBrain.clear();
    _activeEnemies = 0;
    PRETTY_DEBUG << "Enemies cleared, size: " << _enemyBrain.size() << std::endl;
    PRETTY_DEBUG << "Clearing remaining bullets" << std::endl;
    unsigned int bIndex = 0;
    while (_playerBullets.size() > 0) {
        PRETTY_DEBUG << "Removing bullet: " << bIndex << ", bullet enemy: " << Recoded::myToString(_playerBullets[_playerBullets.size() - 1].isEnemy()) << std::endl;
        _playerBullets.pop_back();
        bIndex++;
    }
    PRETTY_DEBUG << "Removed the player bullets" << std::endl;
    bIndex = 0;
    while (_enemyBullets.size() > 0) {
        PRETTY_DEBUG << "Removing bullet: " << bIndex << ", bullet enemy: " << Recoded::myToString(_enemyBullets[_enemyBullets.size() - 1].isEnemy()) << std::endl;
        _enemyBullets.pop_back();
        bIndex++;
    }
    PRETTY_DEBUG << "Removed the enemy bullets" << std::endl;
    PRETTY_DEBUG << "A the end of the kill function" << std::endl;
};

void GUI::ECS::Online::Orchestrator::_spawnEnemy(const std::uint32_t id, std::pair<float, float> pos)
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
    std::shared_ptr<GUI::ECS::Online::EnemyBrain> enemy = std::make_shared<GUI::ECS::Online::EnemyBrain>(id);
    PRETTY_DEBUG << "The _enemyBrain shared pointer has been created" << std::endl;
    enemy->setSprite(_spriteEnemy, _spriteBulletEnemy);
    PRETTY_DEBUG << "The sprite enemy and sprite bullet enemy has been set" << std::endl;
    enemy->setPosition(pos);
    PRETTY_DEBUG << "The enemy has been set with the position: " << pos << std::endl;
    enemy->setVisible(true);
    enemy->setDimension({ 4,4 });
    enemy->setBulletSize({ 0.5, 0.5 });
    PRETTY_DEBUG << "The enemy is visible" << std::endl;
    _enemyBrain.push_back(enemy);
    _activeEnemies += 1;
    PRETTY_DEBUG << "The enemy has been added to the _enemyBrain" << std::endl;
}

const int GUI::ECS::Online::Orchestrator::_randInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void GUI::ECS::Online::Orchestrator::_setTheScene()
{
    PRETTY_DEBUG << "Resetting the victory and loss variables" << std::endl;
    _gameOver = false;
    _gameWon = false;
    PRETTY_DEBUG << "Reset the victory and loss variables" << std::endl;
    PRETTY_DEBUG << "Resetting the position of the items on screen" << std::endl;
    std::pair<float, float> pos = { 1,1 };
    _spriteBullet->setPosition(pos);
    _spriteBulletEnemy->setPosition(pos);
    _spriteEnemy->setPosition(pos);
    _spritePlayer->setPosition(pos);
    PRETTY_DEBUG << "Reset the position of the items on screen" << std::endl;
    _activeEnemies = 0;
    PRETTY_DEBUG << "The enemies have been spawned" << std::endl;
}

void GUI::ECS::Online::Orchestrator::_setTextComponents()
{

    PRETTY_DEBUG << "Setting the health value of the player" << std::endl;
    const std::vector<std::any> fonts = _ecsEntities[typeid(GUI::ECS::Systems::Font)];

    PRETTY_DEBUG << "Declaring font holder instances" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> defaultFont;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFont;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> buttonFont;
    PRETTY_DEBUG << "Declared font holder instances" << std::endl;
    PRETTY_DEBUG << "Fetching the fonts that will be used in the window" << std::endl;
    unsigned int index = 0;
    unsigned int titleFontIndex = 0;
    unsigned int bodyFontIndex = 0;
    unsigned int defaultFontIndex = 0;
    unsigned int buttonFontIndex = 0;
    for (std::any fontCast : fonts) {
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> fontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fontCast, false);
        if (!fontCapsule.has_value()) {
            continue;
        }
        std::string applicationContext = fontCapsule.value()->getApplication();
        if (applicationContext == "title") {
            titleFontIndex = index;
        } else if (applicationContext == "body") {
            bodyFontIndex = index;
        } else if (applicationContext == "default") {
            defaultFontIndex = index;
        } else if (applicationContext == "button") {
            buttonFontIndex = index;
        } else {
            index++;
            continue;
        }
        index++;
    }
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[titleFontIndex], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[bodyFontIndex], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> defaultFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[defaultFontIndex], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> buttonFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[buttonFontIndex], false);
    if (!defaultFontCapsule.has_value()) {
        PRETTY_DEBUG << "No default font found, aborting program" << std::endl;
        throw CustomExceptions::NoFont("<Default font not found>");
    }
    defaultFont.emplace(defaultFontCapsule.value());
    titleFont.emplace(defaultFontCapsule.value());
    bodyFont.emplace(defaultFontCapsule.value());
    buttonFont.emplace(defaultFontCapsule.value());
    if (titleFontCapsule.has_value()) {
        PRETTY_SUCCESS << "Title font found, not defaulting to the default font." << std::endl;
        titleFont.emplace(titleFontCapsule.value());
    }
    if (bodyFontCapsule.has_value()) {
        PRETTY_SUCCESS << "Body font found, not defaulting to the default font." << std::endl;
        bodyFont.emplace(bodyFontCapsule.value());
    }
    if (buttonFontCapsule.has_value()) {
        PRETTY_SUCCESS << "Button font found, not defaulting to the default font." << std::endl;
        buttonFont.emplace(buttonFontCapsule.value());
    }
    PRETTY_DEBUG << "Fetched the fonts that will be used in the window" << std::endl;
    PRETTY_DEBUG << "Creating the text to display the user's health" << std::endl;
    const unsigned int size = 20;
    const std::pair<float, float> posEnnemies = { 10, 40 };
    std::shared_ptr<GUI::ECS::Components::TextComponent> textEnnemies = std::make_shared<GUI::ECS::Components::TextComponent>(
        0,
        *(bodyFont.value()),
        "Remaining ennemies: ",
        size,
        GUI::ECS::Systems::Colour::Red,
        GUI::ECS::Systems::Colour::Red,
        GUI::ECS::Systems::Colour::Red,
        posEnnemies
    );
    _remainingEnemies.emplace(textEnnemies);
    PRETTY_DEBUG << "Fonts gathered" << std::endl;

}


/**
 * @brief Plays the shooting sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with shooting, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void GUI::ECS::Online::Orchestrator::_shootSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->shootSound();
}

/**
 * @brief Plays the damage sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with damage, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void GUI::ECS::Online::Orchestrator::_damageSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->damageSound();
}

/**
 * @brief Plays the death sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with the player or entity death, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void GUI::ECS::Online::Orchestrator::_deadSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->deadSound();
}

/**
 * @brief Plays the button click sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with button interactions, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void GUI::ECS::Online::Orchestrator::_buttonSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->buttonSound();
}

/**
 * @brief Plays the game over sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with the game over event, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void GUI::ECS::Online::Orchestrator::_gameOverSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->gameOverSound();
}

/**
 * @brief Plays the win sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with success or game completion, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void GUI::ECS::Online::Orchestrator::_winSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->winSound();
}

std::ostream &GUI::ECS::Online::operator<<(std::ostream &os, const GUI::ECS::Online::Orchestrator &item)
{
    os << item.getInfo();
    return os;
}
