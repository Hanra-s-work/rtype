//EntityManager.hpp

#pragma once
#include <unordered_map>
#include <memory>
#include "Entity.hpp"
#include "HandleSprites.hpp"
#include "../../common/NetworkProtocol.hpp" // Pour EntityType

class EntityManager {
public:
    // Met à jour toutes les entités
    void update(float dt);
    
    // Affiche toutes les entités dans la fenêtre
    void render(sf::RenderWindow &window);
    
    // Met à jour une entité existante ou la crée si elle n'existe pas
    void updateEntity(uint32_t entityId, EntityType type, float posX, float posY);
    void removeEntity(uint32_t entityId);
private:
    // Factory qui crée l'entité selon son type
    std::unique_ptr<Entity> createEntity(EntityType type, float posX, float posY) {
        // Selon le type d'entité, on charge un asset différent.
        // Adapte les chemins et les classes si tu souhaites des comportements spécifiques.
        switch (type) {
            case EntityType::Player:
                return std::make_unique<SpriteEntity>("client/assets/player.png", posX, posY);
            case EntityType::Monster:
                return std::make_unique<SpriteEntity>("client/assets/monster.png", posX, posY);
            case EntityType::PlayerMissile:
                return std::make_unique<SpriteEntity>("client/assets/p_missile.png", posX, posY);
            case EntityType::MonsterMissile:
                return std::make_unique<SpriteEntity>("client/assets/m_missile.png", posX, posY);
            // Tu peux ajouter d'autres cas (Powerup, Boss, etc.)
            default:
                // En cas d'erreur, retourne un sprite par défaut
                return std::make_unique<SpriteEntity>("client/assets/default.png", posX, posY);
                std::unordered_map<uint32_t, std::unique_ptr<Entity>> _entities;

        }
    }
    
    std::unordered_map<uint32_t, std::unique_ptr<Entity>> _entities;
};
