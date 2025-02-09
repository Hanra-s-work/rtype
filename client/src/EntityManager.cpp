#include "EntityManager.hpp"
#include "SpriteEntity.hpp"
#include "TextureManager.hpp"
#include <cstring>

void EntityManager::update(float dt)
{
    for (auto &e : _entities)
        e.second->update(dt);
}

void EntityManager::render(sf::RenderWindow &window)
{
    for (auto &e : _entities)
        e.second->render(window);
}

void EntityManager::updateEntity(uint32_t id, EntityType type, float posX, float posY)
{
    if (_destroyed.find(id) != _destroyed.end())
        return;
    auto it = _entities.find(id);
    if (it == _entities.end())
        _entities[id] = createEntity(type, posX, posY);
    else {
        if (auto se = dynamic_cast<SpriteEntity*>(it->second.get()))
            se->setTargetPosition(posX, posY);
        else
            it->second->setPosition(posX, posY);
    }
}

void EntityManager::removeEntity(uint32_t id)
{
    _entities.erase(id);
    _destroyed.insert(id);
}

void EntityManager::updateLife(uint32_t id, EntityType type, uint32_t life)
{
    if (_destroyed.find(id) != _destroyed.end())
        return;
    auto it = _entities.find(id);
    if (it != _entities.end()) {
        if (auto se = dynamic_cast<SpriteEntity*>(it->second.get()))
            se->setLife(life);
    }
}

SpriteEntity* EntityManager::getSpriteEntity(uint32_t id)
{
    auto it = _entities.find(id);
    if (it != _entities.end())
        return dynamic_cast<SpriteEntity*>(it->second.get());
    return nullptr;
}

std::unique_ptr<Entity> EntityManager::createEntity(EntityType type, float posX, float posY)
{
    switch (type) {
        case EntityType::Player:
            return std::make_unique<SpriteEntity>("client/assets/player.png", posX, posY);
        case EntityType::Monster:
            return std::make_unique<SpriteEntity>("client/assets/monster.png", posX, posY);
        case EntityType::PlayerMissile:
            return std::make_unique<SpriteEntity>("client/assets/p_missile.png", posX, posY);
        case EntityType::MonsterMissile:
            return std::make_unique<SpriteEntity>("client/assets/m_missile.png", posX, posY);
        case EntityType::Monster2:
            return std::make_unique<SpriteEntity>("client/assets/monster2.png", posX, posY);
        case EntityType::Monster3:
            return std::make_unique<SpriteEntity>("client/assets/monster3.png", posX, posY);
        case EntityType::Boss:
            return std::make_unique<SpriteEntity>("client/assets/boss.png", posX, posY);
        case EntityType::Collision:
            return std::make_unique<SpriteEntity>("client/assets/collision.png", posX, posY);
        default:
            return std::make_unique<SpriteEntity>("client/assets/debugsprite.jpg", posX, posY);
    }
}

void EntityManager::clear()
{
    this->_entities.clear();
}
