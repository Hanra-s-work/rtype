#pragma once

#include <cstddef>

class Registry;

/**
 * @brief Gets entity id by the player's client id.
 * 
 * @param r `Registry` of the game.
 * @param client_id The Id of the player's client.
 * @return Id of the entity.
 */
size_t getIdByClientId(Registry &r, const unsigned int client_id);
