#pragma once

#include <cstddef>

enum messageType {
    SPAWN,
    MOVE,
    KILL,
    DAMAGE,
    HEAL,
    BUFF,
    STATUS
};

struct coord{
    float x;
    float y;
};

struct messageInfo {
    int status;
    int asset_id;
    coord coords;
};

struct GameMessage {
    messageType type;
    size_t id;
    messageInfo msg;
};
