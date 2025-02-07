#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <unordered_map>
#include <memory>
#include "Entity.hpp"
#include "SpriteEntity.hpp"
#include "../../common/NetworkProtocol.hpp"
#include <unordered_set>

/**
 * @brief Manages game entities.
 *
 * This class handles creation, updating, rendering, and removal of game entities.
*/
class EntityManager {
    public:
        void update(float dt);
        void render(sf::RenderWindow &window);
        void updateEntity(uint32_t id, EntityType type, float posX, float posY);
        void removeEntity(uint32_t id);
        void updateLife(uint32_t id, EntityType type, uint32_t life);
        SpriteEntity* getSpriteEntity(uint32_t id);
    private:
        std::unique_ptr<Entity> createEntity(EntityType type, float posX, float posY);
        std::unordered_map<uint32_t, std::unique_ptr<Entity>> _entities; ///< Container for entities
        std::unordered_set<uint32_t> _destroyed; ///< Set of destroyed entity IDs
};

#endif // ENTITYMANAGER_HPP
