//GameWorld.cpp
#include "GameWorld.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <cmath>

// Define a simple rectangle structure for hitbox detection.
struct Rect {
    float x, y, w, h;
};

static Rect getHitbox(Entity* e) {
    Rect r;
    Vector2 pos = e->getPosition();
    r.x = pos.x;
    r.y = pos.y;
    switch(e->getType()) {
        case EntityType::Player:
            r.w = 128.f; r.h = 89.f;
            break;
        case EntityType::PlayerMissile:
            r.w = 104.f; r.h = 50.f;
            break;
        case EntityType::MonsterMissile:
            r.w = 60.f;  r.h = 58.f;
            break;
        case EntityType::Monster:
            r.w = 99.f;  r.h = 51.f;
            break;
        default:
            r.w = 50.f;  r.h = 50.f;
            break;
    }
    return r;
}

static bool rectIntersect(const Rect& a, const Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

GameWorld::GameWorld() 
    : _monsterSpawnTimer(0.0f), _monsterSpawnInterval(5.0f)
{
}

void GameWorld::update(float dt, bool spawnEnemies, std::vector<DestroyEvent>& destroyEvents)
{
    // 1. Update the monster spawn timer (under lock)
    bool shouldSpawn = false;
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        _monsterSpawnTimer += dt;
        if (spawnEnemies && _monsterSpawnTimer >= _monsterSpawnInterval) {
            shouldSpawn = true;
            _monsterSpawnTimer = 0.0;
        }
    }
    if (shouldSpawn) {
        spawnMonster();
    }

    // 2. Take a snapshot of entities for updating (outside the lock)
    std::vector<Entity*> snapshot;
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        snapshot.reserve(_entities.size());
        for (const auto &ent : _entities)
            snapshot.push_back(ent.get());
    }
    for (Entity* e : snapshot) {
        if (e)
            e->update(dt);
    }
    
    // 3. Collision detection and resolution.
    // We record destroy events as (type, id) pairs.
    std::vector<DestroyEvent> localDestroyEvents;
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        for (size_t i = 0; i < _entities.size(); ++i) {
            for (size_t j = i + 1; j < _entities.size(); ++j) {
                Entity* e1 = _entities[i].get();
                Entity* e2 = _entities[j].get();
                if (!e1 || !e2) continue;
                if (e1->isDestroyed() || e2->isDestroyed())
                    continue;

                // Skip collision if one is a PlayerMissile and the other is a Player and the missile belongs to that player.
                if ((e1->getType() == EntityType::PlayerMissile && e2->getType() == EntityType::Player) ||
                    (e1->getType() == EntityType::Player && e2->getType() == EntityType::PlayerMissile)) {
                    Missile* m = (e1->getType() == EntityType::PlayerMissile) ? dynamic_cast<Missile*>(e1) 
                                                                               : dynamic_cast<Missile*>(e2);
                    Player* p = (e1->getType() == EntityType::Player) ? dynamic_cast<Player*>(e1)
                                                                      : dynamic_cast<Player*>(e2);
                    if (m && p && m->getOwnerId() == p->getId()) {
                        continue; // Skip collision between a player and its own missile.
                    }
                }

                Rect r1 = getHitbox(e1);
                Rect r2 = getHitbox(e2);
                if (rectIntersect(r1, r2)) {
                    // Case A: PlayerMissile vs Monster collision.
                    if ((e1->getType() == EntityType::PlayerMissile && e2->getType() == EntityType::Monster) ||
                        (e1->getType() == EntityType::Monster && e2->getType() == EntityType::PlayerMissile)) {
                        e1->destroy();
                        e2->destroy();
                        // (Score update will be handled outside.)
                        // No need to record score update here—only record destruction events.
                    }
                    // Case B: MonsterMissile vs Player collision.
                    else if ((e1->getType() == EntityType::MonsterMissile && e2->getType() == EntityType::Player) ||
                             (e1->getType() == EntityType::Player && e2->getType() == EntityType::MonsterMissile)) {
                        if (e1->getType() == EntityType::MonsterMissile) {
                            e1->destroy();
                            if (Player* p = dynamic_cast<Player*>(e2))
                                p->decreaseLife();
                        } else {
                            e2->destroy();
                            if (Player* p = dynamic_cast<Player*>(e1))
                                p->decreaseLife();
                        }
                    }
                    // Case C: Monster vs Player collision.
                    else if ((e1->getType() == EntityType::Monster && e2->getType() == EntityType::Player) ||
                             (e1->getType() == EntityType::Player && e2->getType() == EntityType::Monster)) {
                        if (e1->getType() == EntityType::Player) {
                            if (Player* p = dynamic_cast<Player*>(e1))
                                p->decreaseLife();
                        } else {
                            if (Player* p = dynamic_cast<Player*>(e2))
                                p->decreaseLife();
                        }
                    }
                }
            }
        }
        
        // Record destroy events for all entities that are now destroyed.
        for (const auto &ent : _entities) {
            if (ent->isDestroyed()) {
                DestroyEvent ev;
                ev.type = static_cast<uint8_t>(ent->getType());
                ev.id = ent->getId();
                localDestroyEvents.push_back(ev);
            }
        }
        
        // Remove destroyed entities from _entities.
        _entities.erase(
            std::remove_if(_entities.begin(), _entities.end(),
                [](const std::unique_ptr<Entity>& e) {
                    return e->isDestroyed();
                }),
            _entities.end()
        );
    }
    // Set the output parameter.
    destroyEvents = std::move(localDestroyEvents);
}

void GameWorld::spawnMonster()
{
    uint32_t monsterId = generateEntityId();
    auto monster = std::make_unique<Monster>(monsterId, *this);
    float x = 1920.f;
    float y = static_cast<float>(std::rand() % (1080 - 51));
    monster->setPosition({x, y});
    monster->setVelocity({-50.f, 0.f});
    std::cout << "[GameWorld] Spawned monster at x=" << x << ", y=" << y << "\n";
    addEntity(std::move(monster));
}

void GameWorld::addEntity(std::unique_ptr<Entity> entity)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    _entities.push_back(std::move(entity));
}

std::vector<Entity*> GameWorld::getEntitiesSnapshot() const {
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    std::vector<Entity*> snapshot;
    snapshot.reserve(_entities.size());
    for (const auto &ent : _entities)
        snapshot.push_back(ent.get());
    return snapshot;
}

Entity* GameWorld::getEntityById(uint32_t id)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    for (auto &ent : _entities)
        if (ent->getId() == id)
            return ent.get();
    return nullptr;
}