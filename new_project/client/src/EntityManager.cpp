// EntityManager.cpp
#include "EntityManager.hpp"

void EntityManager::update(float dt)
{
    for (auto &pair : _entities)
        pair.second->update(dt);
}

void EntityManager::render(sf::RenderWindow &window)
{
    for (auto &pair : _entities)
        pair.second->render(window);
}

void EntityManager::updateEntity(uint32_t entityId, EntityType type, float posX, float posY)
{
    if (_destroyedEntities.find(entityId) != _destroyedEntities.end())
        return;
    auto it = _entities.find(entityId);
    if (it == _entities.end())
        _entities[entityId] = createEntity(type, posX, posY);
    else {
        auto* se = dynamic_cast<SpriteEntity*>(it->second.get());
        if (se)
            se->setTargetPosition(posX, posY);
        else
            it->second->setPosition(posX, posY);
    }
}

void EntityManager::removeEntity(uint32_t entityId)
{
    _entities.erase(entityId);
    _destroyedEntities.insert(entityId);
}

void EntityManager::updateLife(uint32_t entityId, EntityType type, uint32_t life)
{
    if (_destroyedEntities.find(entityId) != _destroyedEntities.end())
        return;
    auto it = _entities.find(entityId);
    if (it != _entities.end()) {
        auto* spriteEntity = dynamic_cast<SpriteEntity*>(it->second.get());
        if (spriteEntity)
            spriteEntity->setLife(life);
    }
}

SpriteEntity* EntityManager::getSpriteEntity(uint32_t entityId)
{
    auto it = _entities.find(entityId);
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
        default:
            return std::make_unique<SpriteEntity>("client/assets/default.png", posX, posY);
    }
}