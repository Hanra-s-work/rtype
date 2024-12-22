#pragma once

#include "Registry.hpp"

void event_system(Registry &r);
bool validateAction(const GameMessage& event, Registry& r);
bool performAction(const GameMessage& event, Registry& r);