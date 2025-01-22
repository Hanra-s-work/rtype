#pragma once

#include <cstddef>
#include <sstream>
#include <cstdint>
#include <cstring>

/**
 * @brief Enum representing the different types of game messages.
 * 
 * The `messageType` enum defines various message types used for communication in the game, such as events 
 * like spawning, movement, damage, and status updates.
 */
enum messageType : uint8_t {
    P_EMPTY,
    P_CONNECT,     ///< Represents a connecting player event.
    P_DISCONNECT,  ///< Represents a disconnecting player event.
    P_MOVE,        ///< Represents a movement event.
    P_SHOOT,       ///< Represents a player shooting event
    P_SPAWN,       ///< Represents a spawn event.
    P_KILL,        ///< Represents a kill event.
    P_DAMAGE,      ///< Represents a damage event.
    P_HEAL,        ///< Represents a healing event.
    P_BUFF,        ///< Represents a buff event.
    P_STATUS,      ///< Represents a status event.
    P_ERROR = 0xFF ///< Represents an error occurred.
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
    uint8_t status;         ///< Status of the event (e.g., success or failure).
    int asset_id;       ///< ID representing the game asset related to the event (e.g., entity or object).
    uint32_t cli_id;    ///< Id of the player's client.
    char username[9];   ///< Username of player connecting.
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
    std::size_t id;          ///< The unique identifier for the entity or object involved in the event.
    messageInfo msg;    ///< Additional information about the event (status, asset ID, and coordinates).
};

/**
     * @brief Deserializes a GameMessage object from a binary stream.
     *
     * This function reads binary data from the provided input stream and reconstructs a `GameMessage` object.
     * The binary data should have been written using the `serialize` function.
     *
     * @param is The input stream from which the binary data will be read.
     * @return GameMessage The reconstructed `GameMessage` object.
     */
GameMessage deserialize(std::istringstream& is);

/**
     * @brief Serializes a GameMessage object into a binary stream.
     *
     * This function writes the `GameMessage` object's data to the provided output stream in binary format.
     * The serialized data can later be read using the `deserialize` function.
     *
     * @param message The `GameMessage` object to serialize.
     * @param os The output stream to which the binary data will be written.
     */
void serialize(const GameMessage& message, std::ostringstream& os);
