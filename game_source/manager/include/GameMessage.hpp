#pragma once

#include <cstddef>

/**
 * @brief Enum representing the different types of game messages.
 * 
 * The `messageType` enum defines various message types used for communication in the game, such as events 
 * like spawning, movement, damage, and status updates.
 */
enum messageType {
    CONNECT,    ///< Represents a connecting player event.
    DISCONNECT, ///< Represents a disconnecting player event.
    MOVE,       ///< Represents a movement event.
    SHOOT,      ///< Represents a player shooting event
    SPAWN,      ///< Represents a spawn event.
    KILL,       ///< Represents a kill event.
    DAMAGE,     ///< Represents a damage event.
    HEAL,       ///< Represents a healing event.
    BUFF,       ///< Represents a buff event.
    STATUS      ///< Represents a status event.
};

/**
 * @brief A structure representing coordinates in a 2D space.
 * 
 * The `coord` structure holds the `x` and `y` values that represent a position in a 2D plane.
 */
struct coord {
    float x; ///< The X coordinate.
    float y; ///< The Y coordinate.
};

/**
 * @brief A structure containing information about a game message.
 * 
 * The `messageInfo` structure holds additional data related to the message, such as status, asset ID, and 
 * coordinates. This information is used to describe the context of a specific event in the game.
 */
struct messageInfo {
    int status;         ///< Status of the event (e.g., success or failure).
    int asset_id;       ///< ID representing the game asset related to the event (e.g., entity or object).
    char username[9];   ///< Username of player connecting
    coord coords;       ///< Coordinates associated with the event, such as the position of an entity.
};

/**
 * @brief A structure representing a game message.
 * 
 * The `GameMessage` structure encapsulates a message in the game. It consists of a message type, a unique ID, 
 * and associated information about the event (e.g., status, asset ID, and coordinates).
 */
struct GameMessage {
    messageType type;   ///< The type of message (e.g., SPAWN, MOVE, etc.).
    size_t id;          ///< The unique identifier for the entity or object involved in the event.
    messageInfo msg;    ///< Additional information about the event (status, asset ID, and coordinates).
};
