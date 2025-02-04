//EntityManager.cpp

#include "EntityManager.hpp"

// Met à jour toutes les entités
void EntityManager::update(float dt) {
    for (auto &pair : _entities) {
        pair.second->update(dt);
    }
}

// Affiche toutes les entités dans la fenêtre
void EntityManager::render(sf::RenderWindow &window) {
    for (auto &pair : _entities) {
        pair.second->render(window);
    }
}

void EntityManager::updateEntity(uint32_t entityId, EntityType type, float posX, float posY) {
    // If the entity was previously destroyed, do not re-create it.
    if (_destroyedEntities.find(entityId) != _destroyedEntities.end()) {
        return;
    }
    
    auto it = _entities.find(entityId);
    if (it == _entities.end()) {
        // Entity does not exist: create it.
        _entities[entityId] = createEntity(type, posX, posY);
    } else {
        // Update the existing entity.
        auto* se = dynamic_cast<SpriteEntity*>(it->second.get());
        if (se) {
            se->setTargetPosition(posX, posY);
        } else {
            it->second->setPosition(posX, posY);
        }
    }
}

void EntityManager::removeEntity(uint32_t entityId) {
    _entities.erase(entityId);
    _destroyedEntities.insert(entityId);
}


void EntityManager::updateLife(uint32_t entityId, EntityType type, uint32_t life) {
    if (_destroyedEntities.find(entityId) != _destroyedEntities.end()) {
    return;
    }

    auto it = _entities.find(entityId);
    if (it != _entities.end()) {
        // On suppose que l'entité est un SpriteEntity (par exemple un joueur ou un monstre)
        auto* spriteEntity = dynamic_cast<SpriteEntity*>(it->second.get());
        if (spriteEntity) {
            spriteEntity->setLife(life);
        }
    }
}

SpriteEntity* EntityManager::getSpriteEntity(uint32_t entityId) {
    auto it = _entities.find(entityId);
    if (it != _entities.end()) {
        return dynamic_cast<SpriteEntity*>(it->second.get());
    }
    return nullptr;
}
