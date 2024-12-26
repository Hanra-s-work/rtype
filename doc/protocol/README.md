# Communication protocol

## Table of contents

* [Brief](#brief)
* [UDP Protocole | SERVER / CLIENT COMMUNICATION](#udp-protocol--server--client-communication)
* [Binary Message Format](#binary-message-format)
* [Types of Messages the Server Expects and Sends](#types-of-messages-the-server-expects-and-sends)
* [Error Handling](#error-handling)
* [Example Usage](#example-usage)
  * [Client side](#client-side)
  * [Server side](#server-side)

## Brief

This is the current protocol that is used by the server and the client to communicate in order to provide a working game engine.

### UDP PROTOCOL | SERVER / CLIENT COMMUNICATION

#### **Binary Message Format**

Each message exchanged between the client and the server follows a specific format. A binary packet is structured as follows:

* **Message Type (1 byte)**: An identifier indicating the type of action (e.g., MOVE, SHOOT, etc.).
* **Message Size (2 bytes)**: The size of the message payload (content).
* **Payload**: The data associated with the action (e.g., the direction of movement or an error code).

#### **Types of Messages the Server Expects and Sends**

Types of messages sent by the client to the server:

* **CONNECT (0x01)**
  * **Description**: The client connects to the server.
  * **Format**:

        ```
        0x01 0x00 0x08 username
        ```

        `username` is the name of the player (e.g., "Player1").

* **DISCONNECT (0x02)**
  * **Description**: The client disconnects from the server.
  * **Format**:

        ```
        0x02 0x00 0x00
        ```

* **MOVE (0x03)**
  * **Description**: The player moves.
  * **Format**:

        ```
        0x03 0x00 0x01 0x01
        ```

        **Payload**:
    * 0x01 for "UP"
    * 0x02 for "DOWN"
    * 0x03 for "LEFT"
    * 0x04 for "RIGHT"

* **SHOOT (0x04)**
  * **Description**: The player shoots.
  * **Format**:

        ```
        0x04 0x00 0x02 0x01 0x02
        ```

        **Payload**: 0x01 0x02 (for example, for a shooting angle in binary coordinates).

* **SPAWN (0x05)**
  * **Description**: A spawn of an enemy or an object in the game.
  * **Format**:

        ```
        0x05 0x00 0x04 0x01 0x0A 0x14 0x02
        ```

        **Payload**: [ID, x, y, type] of the entity to spawn.

* **UPDATE (0x06)**
  * **Description**: The server sends updated information on the game state.
  * **Format**:

        ```
        0x06 0x00 0x08 0x01 0x0A 0x14 0x02 0x02 0x1E 0x28
        ```

        **Payload**: A list of entities (players, enemies) with their positions (x, y) and their type.

#### **Error Handling**

Errors sent by the client to the server:

The client (GUI) may encounter errors, such as when an action is invalid or when game conditions are not met (e.g., trying to move a player outside the game area). In such cases, the client should send an error to the server in binary format to report the problem.

Example of an error message: If a player tries to perform an invalid action, the client can send an error like this:

```
0xFF 0x00 0x01 0x01  // Type: ERROR, Size: 1, Payload: 0x01 (error for invalid movement)
```

Errors sent by the server to the client:

The server can also send errors to the client, for example:

* Malformed packets received from the client.
* Errors during the execution of client actions.

The server sends an error message structured in binary form with a message type of 0xFF. Example of an error message sent by the server:

```
0xFF 0x00 0x02 0x00 0x01  // Type: ERROR, Size: 2, Payload: 0x00 0x01 (error for malformed packet)
```

#### **Example Usage**

##### **Client Side**

* Moving a player upwards:
  * The client sends a MOVE packet with the direction upwards.
  * Message: `0x03 0x00 0x01 0x01`.

* Shooting a projectile:
  * The client sends a SHOOT packet with the angle coordinates.
  * Message: `0x04 0x00 0x02 0x01 0x02`.

##### **Server Side**

* Updating entity positions:
  * The server sends an UPDATE packet to inform clients of the updated positions of players and enemies.
  * Message: `0x06 0x00 0x08 0x01 0x0A 0x14 0x02 0x02 0x1E 0x28`.

* Server's error response:
  * If a malformed packet is received, the server sends an error message.
  * Message: `0xFF 0x00 0x02 0x00 0x01`.
