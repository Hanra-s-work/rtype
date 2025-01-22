#include "WinSystem.hpp"
#include "Registry.hpp"
#include "GameMessage.hpp"

namespace Win {
    int enemies_left = 3;
}

bool game_won = false;

void win_system(Registry &r)
{
    if (game_won) return;
    if (Win::enemies_left <= 0) {
        r.dispatcher->notify({P_STATUS, 0, {1, 0, 0, "", {0, 0}}});
        game_won = true;
    }
}