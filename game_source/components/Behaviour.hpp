#pragma once

enum behaviour_enum {
    DEFAULT,
    UP_DOWN,
    FOLLOW
};

struct Behaviour {
    behaviour_enum type;
    float timer;
};