# RType

RType is a multiplayer side-scrolling shooter inspired by the classic R-Type game. This project consists of a server and a client application. The server manages the game world, game logic (such as entity updates, collision detection, score and life management, and session control), and communicates with clients using UDP via ASIO. The client renders the game using SFML, displaying the game state received from the server.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Build Instructions](#build-instructions)
- [Running the Project](#running-the-project)
- [Communication Protocol](#communication-protocol)
- [Doxygen Documentation](#doxygen-documentation)
- [License](#license)

## Features

- **Multiplayer Gameplay:**  
  The server supports multiple players, enemy spawns (various monster types and a boss), collision handling, score and life updates, and win/lose conditions.
  
- **Real-Time Networking:**  
  The server and client communicate over UDP using ASIO for low-latency message exchange.

- **Graphics & Audio:**  
  The client uses SFML to render the game world and play audio (background music and sound effects).

- **Dynamic Entities:**  
  The game includes various entity types:
  - **Players**
  - **Monsters:** Three types (Monster, Monster2, Monster3) with different movement and shooting patterns.
  - **Missiles:** PlayerMissile and MonsterMissile.
  - **Boss:** A high-health enemy that spawns after a score threshold is reached.

- **Custom Communication Protocol:**  
  A binary protocol handles messages such as connection/disconnection, heartbeats, entity spawn/update/destroy, life and score updates, collision events, and win/lose conditions.

## Project Structure

- **common:**  
  Contains shared components like the communication protocol (message formats, parsing, etc.).
  
- **server:**  
  - **GameWorld:** Manages entities, collisions, score/life handling, and spawning.
  - **NetworkManager:** Uses ASIO to handle UDP communication.
  - **Server:** Contains the main game loop and session management.
  
- **client:**  
  - **NetworkClient:** Receives and sends game state updates.
  - **EntityManager & HUD:** Render the game state and display player information.
  - **Graphics & Audio:** Use SFML for rendering and playing audio.

## Build Instructions

This project uses CMake with CPM/FetchContent to manage dependencies.

### Prerequisites

- A C++ compiler with C++17 support.
- CMake (version 3.11 or higher recommended).
- Git (to fetch dependencies).

### Building on Linux/Mac

Open a terminal in the project root and run:

mkdir build
cd build
cmake ..
cmake --build .

### Building on Windows

Open a Visual Studio Developer Command Prompt/PowerShell in the project root and run:

mkdir build
cd build
cmake ..
cmake --build .

### Running the Project

    Start the Server:
    Run the server executable (e.g., r-type_server.exe on Windows or ./r-type_server on Linux/Mac). By default, the server listens on UDP port 9000.

    Start the Client(s):
    Run the client executable (e.g., r-type_client.exe on Windows or ./r-type_client on Linux/Mac). The client connects to the server (using localhost or an automatically detected LAN IP).

    Gameplay:
    When a client connects, the server starts a game session and begins sending entity spawn, update, collision, life, and score messages in real time via the custom binary protocol.

### Communication Protocol

The communication between the server and the client is handled via a custom binary protocol over UDP. Each message consists of a header and an optional payload.
Message Format

    Header:
        Type (4 bytes): A 32-bit integer representing the message type.
        Payload Size (4 bytes): A 32-bit integer indicating the number of payload bytes.
    Payload:
    The payload format depends on the message type.

### Common Message Types and Payload Formats

    CONNECT (1):
    Sent by the client to request a connection.

    CONNECT_OK (2):
    Sent by the server to confirm the connection, containing a unique player ID.

    DISCONNECT (3):
    Sent by the client upon disconnecting.

    HEARTBEAT (4):
    Periodic heartbeat messages to ensure the connection is alive.

    PLAYER_LEFT (5):
    Sent by the server to notify other clients when a player disconnects.

    MOVE_UP (6), MOVE_DOWN (7), MOVE_RIGHT (8), MOVE_LEFT (9):
    Movement commands sent by the client.

    SPAWN_ENTITY (18):
    Sent by the server when a new entity spawns.
    Payload: [entity_type (uint8_t), entity_id (uint32_t), posX (float), posY (float)]

    UPDATE_ENTITY (17):
    Sent by the server to update an existing entity’s state.
    Payload: [entity_type (uint8_t), entity_id (uint32_t), posX (float), posY (float)]

    DESTROY_ENTITY (20):
    Sent by the server when an entity is destroyed so that clients remove it.
    Payload: [entity_type (uint8_t), entity_id (uint32_t)]

    LIFE (19):
    Sent by the server to update a player’s remaining life.
    Payload: [entity_type (uint8_t), entity_id (uint32_t), remaining_life (uint32_t)]

    SCORE (21):
    Global score update sent by the server.
    Payload: [score (uint32_t)]

    WIN (23) / DEFEAT (22):
    Sent when the game is won or lost.

    HUB (24):
    Sent by the server to indicate that the game session is over and that clients should return to the hub (or main menu).

    COLLIDE (25):
    Used for collision visual effects.
    Payload: [entity_type (uint8_t), dummy_id (uint32_t), posX (float), posY (float)]

### Message Handling

    Entity Spawning & Updates:
    The server sends SPAWN_ENTITY messages when a new entity (player, monster, boss, missile, etc.) spawns, and UPDATE_ENTITY messages to update their positions and states.

    Entity Destruction:
    When an entity is destroyed (e.g., when a player loses all life or a missile hits a monster), the server sends a DESTROY_ENTITY message so that clients remove that entity.

    Life & Score Updates:
    LIFE messages update a player's health, and SCORE messages update the global score.

    Collision Updates:
    COLLIDE messages are sent to trigger visual collision effects on the client side.