#pragma once

enum type_enum{
    PLAYER,
    MONSTER,
    MISSILE,
    OBSTACLE,
    POWERUP
};

struct Type {
    type_enum type;
};