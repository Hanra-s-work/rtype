#include "SyncingSystem.hpp"
#include "Registry.hpp"
#include "Components.hpp"
#include "IndexedZipper.hpp"

std::vector<GameMessage> syncGameState(Registry &r)
{
    std::vector<GameMessage> state;
    auto &&[positions, types] = r.get_component_array<Position, Type>();
    for (auto &&[idx, pos, type] : IndexedZipper(positions, types)) {
        // if killed or not created continue
        if (!pos || !type) continue;

        // need to spawn
        GameMessage msg;
        msg.type = SPAWN;
        msg.id = idx;

        // get position
        msg.msg.coords.x = pos->X;
        msg.msg.coords.y = pos->Y;

        // check type and assign asseet
        if (type->type == PLAYER) {
            msg.msg.asset_id = PLAYER_ASSET;
        } else if (type->type == MONSTER) {
            msg.msg.asset_id = MONSTER1_ASSET;
        } else {
            msg.msg.asset_id = MISSILE1_ASSET;
        }

        // done
    }
    return state;
}