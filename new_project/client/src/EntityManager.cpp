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
        // Création de la nouvelle entité via la factory
        _entities[entityId] = createEntity(type, posX, posY);
    } else {
        // Mise à jour de la position de l'entité existante
        it->second->setPosition(posX, posY);
    }
}
