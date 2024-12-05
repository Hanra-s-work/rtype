#pragma once

enum team_enum {
    ALLY,
    MONSTER
};

struct Team {
    const team_enum team;
};