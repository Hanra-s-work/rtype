#pragma once

enum image_enum {
    PLAYER,
    MONSTER1,
    MONSTER2,
    MISSILE1,
    MISSILE2,
    OBSTACLE1,
    OBSTACLE2,
    POWERUP,
    HEALTHPACK
};

struct Image {
    image_enum asset_id;
    float width, height;
};