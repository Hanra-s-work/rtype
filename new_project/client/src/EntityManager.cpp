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

// Met à jour une entité existante ou la crée si elle n'existe pas
void EntityManager::updateEntity(uint32_t entityId, EntityType type, float posX, float posY) {
    auto it = _entities.find(entityId);
    if (it == _entities.end()) {
        // L'entité n'existe pas encore : on la crée.
        _entities[entityId] = createEntity(type, posX, posY);
    } else {
        // L'entité existe : on met à jour sa position cible pour l'interpolation (si applicable).
        auto* se = dynamic_cast<SpriteEntity*>(it->second.get());
        if (se) {
            se->setTargetPosition(posX, posY);
        } else {
            // Pour les entités qui ne sont pas des SpriteEntity, on peut faire :
            it->second->setPosition(posX, posY);
        }
    }
}

void EntityManager::removeEntity(uint32_t entityId) {
    _entities.erase(entityId);
}
