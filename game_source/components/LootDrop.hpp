#pragma once

enum loot_enum {
    NONE,
    POWER_UP,
    HEALTH
};

struct LootDrop {
    loot_enum loot;
};