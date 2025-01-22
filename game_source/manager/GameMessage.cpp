#include "GameMessage.hpp"

void serialize(const GameMessage &message, std::ostringstream &os) {
    os.put(static_cast<char>(message.type));

    switch (message.type) {
        case P_CONNECT: {
            os.write(reinterpret_cast<const char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            os.write(message.msg.username, 8);
            break;
        }
        case P_DISCONNECT: {
            os.write(reinterpret_cast<const char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            break;
        }
        case P_MOVE: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case P_SHOOT: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            break;
        }
        case P_SPAWN: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            os.write(reinterpret_cast<const char*>(&message.msg.asset_id), sizeof(message.msg.asset_id));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case P_KILL: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            break;
        }
        case P_DAMAGE: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            break;
        }
        case P_STATUS: {
            os.write(reinterpret_cast<const char*>(&message.msg.status), sizeof(message.msg.status));
            break;
        }
        case P_ERROR: {
        }
        default: {
            break;
        }
    }
}


GameMessage deserialize(std::istringstream &is) {
    GameMessage message;
    message.type = static_cast<messageType>(is.get());

    switch (message.type) {
        case P_CONNECT: {
            is.read(reinterpret_cast<char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            is.read(message.msg.username, 8);
            message.msg.username[8] = '\0';
            break;
        }
        case P_DISCONNECT: {
            is.read(reinterpret_cast<char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            break;
        }
        case P_MOVE: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            is.read(reinterpret_cast<char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            is.read(reinterpret_cast<char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case P_SHOOT: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            break;
        }
        case P_SPAWN: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            is.read(reinterpret_cast<char*>(&message.msg.asset_id), sizeof(message.msg.asset_id));
            is.read(reinterpret_cast<char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            is.read(reinterpret_cast<char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case P_KILL: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            break;
        }
        case P_DAMAGE: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            break;
        }
        case P_STATUS: {
            is.read(reinterpret_cast<char*>(&message.msg.status), sizeof(message.msg.status));
            break;
        }
        case P_ERROR: {
            break;
        }
        default: {
            break;
        }
    }

    return message;
}