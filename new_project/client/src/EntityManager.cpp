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

void EntityManager::printEntitiesSizes() const {
    std::cout << "Taille des entités dans le jeu :" << std::endl;
    for (const auto &pair : _entities) {
        // On suppose ici que toutes les entités sont des SpriteEntity.
        // On peut utiliser dynamic_cast pour vérifier.
        const SpriteEntity* spriteEntity = dynamic_cast<const SpriteEntity*>(pair.second.get());
        if (spriteEntity) {
            sf::Vector2f size = spriteEntity->getSize();
            std::cout << "Entity ID: " << pair.first 
                      << " - Taille: (" << size.x << ", " << size.y << ")" 
                      << std::endl;
        } else {
            std::cout << "Entity ID: " << pair.first << " n'est pas une SpriteEntity." << std::endl;
        }
    }
}

// void EntityManager::printEntitiesPositions() const {
//     for (const auto &pair : _entities) {
//         sf::Vector2f pos = pair.second->getPosition();
//         std::cout << "Entity " << pair.first 
//                   << " position: (" << pos.x << ", " << pos.y << ")" 
//                   << std::endl;
//     }
// }