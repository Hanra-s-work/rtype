#pragma once

enum type_enum{
    PLAYER,
    MONSTER,
    MISSILE,
    OBSTACLE,
    POWERUP
};

struct Type {
    const type_enum type;
};