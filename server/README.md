====================================================================
   MULTIPLAYER GAME - BINARY PROTOCOL (Updated with New Message Types)
====================================================================

This document describes the binary protocol for communication between:
  - Clients (GUI/front-end)
  - Server (bridging component)
  - Game Logic (actual gameplay logic)

The Server simply routes messages:
  Client (port 9000) <--> Server <--> Game Logic (port 9001)

All messages share the same 4-byte header, followed by an optional payload.
This updated specification includes new message types reflecting current needs.

-------------------------------------------------------------------------------
1. MESSAGE FORMAT
-------------------------------------------------------------------------------

Each message starts with a 4-byte header:

    +---------------------+---------------------+
    | 2 bytes: type       | 2 bytes: length    |
    +---------------------+---------------------+
    | payload (length)                        |
    +-----------------------------------------+

 - TYPE   (uint16_t): Identifies which action or command this packet represents  
 - LENGTH (uint16_t): How many bytes of payload follow this 4-byte header  
 - PAYLOAD: Zero or more bytes of data, depending on 'length'

By default, this spec assumes little-endian for these 2-byte fields.  
If cross-platform or big-endian systems are involved, you may need `htons/ntohs` 
to convert (type, length) from/to network byte order.

-------------------------------------------------------------------------------
2. MESSAGE CATEGORIES & TYPES
-------------------------------------------------------------------------------

We divide messages into two categories:
  A) **From Client (GUI) -> Server**  
  B) **From Game Logic -> Server**

The server routes them appropriately:
  - (A) goes to the assigned logic instance.
  - (B) goes to all clients assigned to that logic instance.

You may assign numeric codes as you prefer, but below is an example scheme.

-------------------------------------------------------------------------------
A) CLIENT -> SERVER MESSAGES
-------------------------------------------------------------------------------

The client typically controls a "player," so we have:

1) CONNECT
   - type = 1
   - length = 0
   - payload = none
   - Purpose: “Join the game.” Server assigns this client to a not-full logic.

2) DISCONNECT
   - type = 2
   - length = 0
   - payload = none
   - Purpose: “Leave the game.” Server can free the client slot in the logic.

3) MOVE_PLAYER
   - type = 3
   - payload structure (example):
       [ player_id (uint32_t) | offset_x (float/int) | offset_y (float/int) ]
   - length = 12 (if each field is 4 bytes)
   - Purpose: “Move a specific player (player_id) by (offset_x, offset_y).”

4) FIRE_PLAYER
   - type = 4
   - payload structure:
       [ player_id (uint32_t) ]
   - length = 4
   - Purpose: “Player with ID = player_id fires a shot.”

5) MOVE_MY_PLAYER
   - type = 5
   - payload structure:
       [ offset_x (float/int) | offset_y (float/int) ]
   - length = 8
   - Purpose: “Move the ‘current’ player (this client) by offset_x, offset_y.” 
     The logic can figure out which actual player ID this belongs to.

6) FIRE_MY_PLAYER
   - type = 6
   - length = 0 or small
   - payload = optional
   - Purpose: “This client’s own player fires.”

-------------------------------------------------------------------------------
B) GAME LOGIC -> SERVER MESSAGES
-------------------------------------------------------------------------------

The logic can inform the server about game events; the server forwards them to
the assigned clients. Additionally, the logic must first register itself.

1) REGISTER_LOGIC
   - type = 90  (example)
   - length = 0
   - payload = none
   - Purpose: “Hello, I’m a new logic instance.” Sent to server’s logic port (9001).
     The server then knows to assign new players to this logic (until full).

2) SPAWN
   - type = 100
   - payload:
       [ entity_id (uint32_t) | coord_x (float/int) | coord_y (float/int) | asset_id (uint32_t) ]
   - length = 16
   - Purpose: “Spawn an enemy/obstacle at (coord_x, coord_y) with asset_id, entity_id.”

3) FIRE (from enemy)
   - type = 101
   - length/payload as needed (similar to SPAWN if it spawns a projectile)
   - Purpose: “Enemy fires. Possibly treat it as a spawn event or a special action.”

4) MOVE_ENTITY
   - type = 102
   - payload:
       [ entity_id (uint32_t) | offset_x (float/int) | offset_y (float/int) ]
   - length = 12
   - Purpose: “Move the specified entity by offset_x, offset_y.”

5) KILL_ENTITY
   - type = 103
   - payload:
       [ entity_id (uint32_t) ]
   - length = 4
   - Purpose: “Remove/kill entity with this ID from the game.”

6) DAMAGE_ENTITY
   - type = 104
   - payload:
       [ entity_id (uint32_t) | damage_amount (float/int) ]
   - length = 8
   - Purpose: “Damage entity_id by damage_amount. e.g. 1 if default.”

7) STATUS
   - type = 105
   - payload:
       [ status_code (uint32_t) ]
   - length = 4
   - Purpose: “Set or report current game status: waiting=0, playing=1, etc.”

-------------------------------------------------------------------------------
3. EXAMPLE PAYLOAD ENCODING
-------------------------------------------------------------------------------

Example: client sends MOVE_PLAYER (type=3) with length=12, specifying:
   player_id=123, offset_x=2.0, offset_y=-1.0 in little-endian bytes.

Header (4 bytes):
   03 00 0C 00
Payload (12 bytes):
   7B 00 00 00  (123 as uint32_t)
   00 00 00 40  (2.0f in little-endian, approx 0x40000000)
   00 00 80 BF  (-1.0f in little-endian, approx 0xBF800000)

Total 16 bytes. Server receives on port 9000, sees type=3, length=12, 
extracts the payload, and forwards to the assigned logic.

-------------------------------------------------------------------------------
4. SAMPLE MESSAGE FLOW
-------------------------------------------------------------------------------

1) LOGIC → SERVER (REGISTER_LOGIC)
   - Logic binds, say, port=9100, sends a 4-byte packet:
        (type=90, length=0) =>  5A 00 00 00   (0x5A=90 in hex)
     to 127.0.0.1:9001.  
   - Server registers that logic as logicId=1 (or 2, etc.), so new players can be assigned there.

2) CLIENT → SERVER (CONNECT)
   - type=1, length=0 => 01 00 00 00  
   - Server assigns the client to logic #1 if it’s not full, or logic #2 otherwise,
     then forwards the same 4 bytes to logic’s bound port.

3) LOGIC → SERVER (SPAWN entity)
   - type=100, length=16 with [entity_id=500, x=200, y=300, asset_id=10].
   - Server looks up which clients belong to that logic, forwards the same packet
     (header+payload) to each.

4) CLIENT → SERVER (MOVE_MY_PLAYER)
   - type=5, length=8 with [offset_x, offset_y].
   - The server decodes (5,8), passes the payload to logic.

5) LOGIC → SERVER (KILL_ENTITY)
   - type=103, length=4 with [entity_id].
   - The server forwards to all clients in that logic’s session. They remove the entity.

-------------------------------------------------------------------------------
5. RELIABILITY & LIMITATIONS
-------------------------------------------------------------------------------

- **UDP-based**: No guaranteed delivery or ordering. If needed, add your own 
  reliability or use a more reliable transport.
- **Security**: No authentication or encryption in this example.
- **Ports**:
   - Server: 9000 (clients), 9001 (logic).
   - Logic picks its own port (e.g., 9100) and issues a REGISTER_LOGIC (type=90)
     to 127.0.0.1:9001 so the server knows it exists.
- **4-Player Limit**: Each logic instance can handle 4 players by default. 
  This can be changed in the server code.

-------------------------------------------------------------------------------
6. MAPPING CLIENT & LOGIC MESSAGES - QUICK REFERENCE
-------------------------------------------------------------------------------

CLIENT → SERVER (on port 9000)
----------------------------------------------------------------
 - (1) CONNECT                 [no payload]
 - (2) DISCONNECT              [no payload]
 - (3) MOVE_PLAYER             [player_id, offset_x, offset_y]
 - (4) FIRE_PLAYER             [player_id]
 - (5) MOVE_MY_PLAYER          [offset_x, offset_y]
 - (6) FIRE_MY_PLAYER          [optional payload]

GAME LOGIC → SERVER (on port 9001)
----------------------------------------------------------------
 - (90) REGISTER_LOGIC         [no payload]
 - (100) SPAWN                 [entity_id, coord_x, coord_y, asset_id]
 - (101) FIRE (enemy)          [or skip if you treat it as SPAWN]
 - (102) MOVE_ENTITY           [entity_id, offset_x, offset_y]
 - (103) KILL_ENTITY           [entity_id]
 - (104) DAMAGE_ENTITY         [entity_id, damage_amount]
 - (105) STATUS                [status_code: e.g. 0=waiting,1=playing,2=game_over,etc]

-------------------------------------------------------------------------------
7. CONCLUSION
-------------------------------------------------------------------------------

This updated protocol supports:

 - **Client** actions like Connect/Disconnect, Move, Fire (either for a specific 
   player_id or the current player).
 - **Logic** actions like Registering (type=90), Spawning, Firing, Moving, 
   Killing, Damaging entities, plus sending Status codes.
 - The server uses only the 4-byte header (type + length) to decide how to route 
   the messages. The logic and clients must agree on the payload structures.

All other details (like how you encode floats/ints or handle sequence numbers) 
can be adapted as your project evolves.