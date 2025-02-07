//GameWorld.hpp
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
        case EntityType::Monster2:
            r.w = 91.f;  r.h = 100.f;
            break;
        case EntityType::Monster3:
            r.w = 80.f;  r.h = 80.f;
            break;
        case EntityType::Boss:
            r.w = 118.f; r.h = 120.f;
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
    : _monsterSpawnTimer(0.0), _monsterSpawnInterval(5.0)
{
    srand (time(NULL));
}

void GameWorld::update(float dt, bool spawnEnemies, std::vector<DestroyEvent>& destroyEvents, std::vector<CollisionEvent>& collisionEvents)
{
    // 1. Update monster spawn timer.
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

    // 2. Take a snapshot of entities for updating.
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
    
    // 3. Collision detection & resolution.
    std::vector<DestroyEvent> localDestroyEvents;
    std::vector<CollisionEvent> localCollisionEvents;
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        for (size_t i = 0; i < _entities.size(); ++i) {
            for (size_t j = i + 1; j < _entities.size(); ++j) {
                Entity* e1 = _entities[i].get();
                Entity* e2 = _entities[j].get();
                if (!e1 || !e2) continue;
                if (e1->isDestroyed() || e2->isDestroyed())
                    continue;
                
                // Skip collision between a player and its own missile.
                if ((e1->getType() == EntityType::PlayerMissile && e2->getType() == EntityType::Player) ||
                    (e1->getType() == EntityType::Player && e2->getType() == EntityType::PlayerMissile)) {
                    Missile* m = (e1->getType() == EntityType::PlayerMissile) ? dynamic_cast<Missile*>(e1) 
                                                                               : dynamic_cast<Missile*>(e2);
                    Player* p = (e1->getType() == EntityType::Player) ? dynamic_cast<Player*>(e1)
                                                                      : dynamic_cast<Player*>(e2);
                    if (m && p && m->getOwnerId() == p->getId())
                        continue;
                }
                
                Rect r1 = getHitbox(e1);
                Rect r2 = getHitbox(e2);
                if (rectIntersect(r1, r2)) {
                    // Record collision event at the midpoint.
                    float midX = (r1.x + r1.w/2 + r2.x + r2.w/2) / 2;
                    float midY = (r1.y + r1.h/2 + r2.y + r2.h/2) / 2;
                    CollisionEvent colEv;
                    colEv.posX = midX;
                    colEv.posY = midY;
                    localCollisionEvents.push_back(colEv);
                    
                    // Collision resolution:
                    // Case A: PlayerMissile vs (Monster, Monster2, Monster3)
                    if ((e1->getType() == EntityType::PlayerMissile &&
                        (e2->getType() == EntityType::Monster || e2->getType() == EntityType::Monster2 || e2->getType() == EntityType::Monster3)) ||
                        ((e1->getType() == EntityType::Monster || e1->getType() == EntityType::Monster2 || e1->getType() == EntityType::Monster3) &&
                         e2->getType() == EntityType::PlayerMissile))
                    {
                        e1->destroy();
                        e2->destroy();
                        if (onScoreUpdate)
                            onScoreUpdate(100);
                    }
                    // Case B: MonsterMissile vs Player
                    else if ((e1->getType() == EntityType::MonsterMissile && e2->getType() == EntityType::Player) ||
                             (e1->getType() == EntityType::Player && e2->getType() == EntityType::MonsterMissile))
                    {
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
                    // Case C: Monster vs Player
                    else if (((e1->getType() == EntityType::Monster || e1->getType() == EntityType::Monster2 || e1->getType() == EntityType::Monster3) && e2->getType() == EntityType::Player) ||
                             ((e2->getType() == EntityType::Monster || e2->getType() == EntityType::Monster2 || e2->getType() == EntityType::Monster3) && e1->getType() == EntityType::Player))
                    {
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
        
        // Record destroy events.
        for (const auto &ent : _entities) {
            if (ent->isDestroyed()) {
                DestroyEvent ev;
                ev.type = static_cast<uint8_t>(ent->getType());
                ev.id = ent->getId();
                localDestroyEvents.push_back(ev);
            }
        }
        
        // Remove destroyed entities.
        _entities.erase(
            std::remove_if(_entities.begin(), _entities.end(),
                [](const std::unique_ptr<Entity>& e) {
                    return e->isDestroyed();
                }),
            _entities.end()
        );
    }
    destroyEvents = std::move(localDestroyEvents);
    
    if (onCollisionEvent) {
        for (const auto &colEv : localCollisionEvents)
            onCollisionEvent(colEv.posX, colEv.posY);
    }
}

void GameWorld::spawnMonster()
{
    uint32_t monsterId = generateEntityId();
    int r = std::rand() % 3; // 0, 1, or 2
    EntityType type;
    switch(r) {
        case 0:  type = EntityType::Monster;  break;
        case 1:  type = EntityType::Monster2; break;
        case 2:  type = EntityType::Monster3; break;
        default: type = EntityType::Monster;  break;
    }
    auto monster = std::make_unique<Monster>(monsterId, *this);
    monster->_type = type;
    float x = 1920.f;
    float monsterHeight = 51.f;
    if (type == EntityType::Monster2)
        monsterHeight = 100.f;
    else if (type == EntityType::Monster3)
        monsterHeight = 80.f;
    float y = static_cast<float>(std::rand() % static_cast<int>(1080 - monsterHeight));
    monster->setPosition({x, y});
    switch(type) {
        case EntityType::Monster:
            monster->setVelocity({-50.f, 0.f});
            break;
        case EntityType::Monster2:
            monster->setVelocity({-50.f, 30.f});
            break;
        case EntityType::Monster3:
            monster->setVelocity({-50.f, 0.f});
            break;
        default:
            monster->setVelocity({-50.f, 0.f});
            break;
    }
    std::cout << "[GameWorld] Spawned monster type " << static_cast<int>(type)
              << " at x=" << x << ", y=" << y << "\n";
    addEntity(std::move(monster));
}

void GameWorld::spawnBoss()
{
    uint32_t bossId = generateEntityId();
    auto boss = std::make_unique<Monster>(bossId, *this);
    boss->_type = EntityType::Boss;
    float x = 1920.f;
    float y = static_cast<float>(std::rand() % static_cast<int>(1080 - 120));
    boss->setPosition({x, y});
    boss->setVelocity({-30.f, 0.f});
    std::cout << "[GameWorld] Spawned Boss at x=" << x << ", y=" << y << "\n";
    addEntity(std::move(boss));
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

std::vector<Entity*> GameWorld::getPlayersSnapshot() const {
    std::vector<Entity*> players;
    auto snapshot = getEntitiesSnapshot();
    for (Entity* e : snapshot) {
        if (e->getType() == EntityType::Player)
            players.push_back(e);
    }
    return players;
}

void GameWorld::reset() {
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    _entities.clear();
    _monsterSpawnTimer = 0.0;
    // Reset any other state as needed.
}