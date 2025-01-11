# UDP Communication protocol Documentation

## Table of contents

* [Brief](#brief)
* [UDP Protocole | SERVER / CLIENT COMMUNICATION](#udp-protocol--server--client-communication)
  * [Binary Message Format](#binary-message-format)
  * [Types of Messages the Server Expects and Sends](#types-of-messages-the-server-expects-and-sends)
    * [CONNECT (0x01)](#connect-0x01)
    * [DISCONNECT (0x02)](#disconnect-0x02)
    * [MOVE (0x03)](#move-0x03)
    * [SHOOT (0x04)](#shoot-0x04)
    * [SPAWN (0x05)](#spawn-0x05)
    * [KILL (0x06)](#kill-0x06)
    * [DAMAGE (0x07)](#damage-0x07)
    * [STATUS (0x0A)](#status-0x0a)
    * [ERROR (0xFF)](#error-0xff)
  * [Error Handling](#error-handling)
  * [Use cases in game logic and GUI](#use-cases-in-game-logic-and-gui)
  * [Notes on implementation](#notes-on-implementation)

## Brief

This section describes the binary UDP protocol used for communication between the server and client in the R-Type game. This documentation aims to provide clarity on the structure of packets, message types, and their intended usage in both game logic and GUI components.

This is the current protocol that is used by the server and the client to communicate in order to provide a working game engine.

## UDP PROTOCOL | SERVER / CLIENT COMMUNICATION

### Binary Message Format

Each UDP message exchanged between the client and the server follows a specific format and scalability. A binary packet is structured as follows:

| Field | Size (bits) | Description |
| --- | --- | --- |
| Message Type | 8 | Identifies the type of message (i.e., MOVE, SHOOT). |
| Payload | Variable | Contains data specific to the message type. Optional depending on the type. |

### **Types of Messages the Server Expects and Sends**

Types of messages sent by the client to the server:

#### **CONNECT (0x01)**

* **Description**: The client connects to the server.
* **Format**:

      | \[0x01\]\[username...\] |
      | :---- |

* **Payload**: `username` (8 characters max, padded with null bytes if shorter) is the name of the player.
* **Example**: A client connecting with the username "Player1" sends:

      | 0x01 50 6c 61 79 65 72 31 00 |
      | :---- |

#### **DISCONNECT (0x02)**

* **Description**: The client disconnects from the server.

* **Format**:

      | \[0x02\]\[id...\]|
      | :---- |

* **Payload**: `id` (size_t) is the entity id on the ECS.

#### **MOVE (0x03)**

* **Description**: Informs an entity movement.
* **Format**:

        | \[0x03\]\[id...\]\[x...\]\[y...\] |
        | :---- |

* **Payload**: 
  * `id` (size_t) is the entity id on the ECS.
  * `x` (float) is the X coordinate
  * `y` (float) is the Y coordinate

* **Example**: A player `1` moving to `(16, 8)`:

    | 0x03 0x00 ... 0x01 0x00 ... 0x10 0x00 ... 0x08 |
    | :---- |

#### **SHOOT (0x04)**

* **Description**: An entity shoots.
* **Format**:

    | \[0x04\]\[id...\] |
    | :---- |

* **Payload**: `id` (size_t) is the entity id on the ECS.

#### **SPAWN (0x05)**

* **Description**: Notifies the client of a new entity (enemy, object) in the game world.
* **Format**:

    | \[0x05\]\[id...\]\[asset...\]\[x...\]\[y...\] |
    | :---- |

* **Payload**: [ID, asset, x, y] of the entity to spawn.

  * `id` (size_t): Unique entity ID.
  * `asset` (short): Asset ID.
  * `x`, `y` (4 bytes each): Coordinates.

#### **KILL (0x06)**

* **Description**: The server tells the client to remove an entity.

* **Format**:

  | \[0x06\]\[id...\] |
  | :---- |

* **Payload**: `id` (size_t) is the entity id on the ECS.

#### **DAMAGE (0x07)**

* **Description**: The server tells an entity was damaged (for client to show animations)

* **Format**:

  | \[0x07\]\[id...\] |
  | :---- |

* **Payload**: `id` (size_t) is the entity id on the ECS.

#### **STATUS (0x0A)**

* **Description**: The server tells the client the current game status.

* **Format**:

  | \[0x08\]\[status\] |
  | :---- |

* **Payload**: `status` (1 byte)
  * `0x00`: On going.
  * `0x01`: Victory. 
  * `0xFF`: Defeat.

#### **ERROR (0xFF)**

* **Description**: Communicates an error or invalid action.

* **Format**:

  | \[0xFF\]\[0x00\]\[size\]\[error\_code\] |
  | :---- |

* **Payload**: Error-specific code for debugging.

---

### **Error Handling**

* **Client Errors**
  If a client sends an invalid request (e.g., moving out of bounds), an error packet is returned:

  | 0xFF 0x01 |
  | :---- |

* **Code:**
  * `0x01`: Invalid action.

* **Server Errors:**
  Malformed packets or server-side issues result in an error response:

  | 0xFF 0x02 |
  | :---- |

* **Error Code:**
  * `0x02`: Malformed packet

---

### **Use cases in game logic and GUI**

* **Game Logic**:

* **MOVE**, **KILL** and **DAMAGE:** Update entities states and synchronize actions.
* **SHOOT** and **SPAWN:** Trigger in-game events like enemy and bullets appearances.
* **STATUS:** Updates game state.

* **GUI**:

* Render **SPAWN**, **MOVE**, **SHOOT**, **DAMAGE** and **KILL** messages for real-time feedback.
* Display error messages from **ERROR** packets.

---

### **Notes on Implementation**

* **Data Integrity**: Ensure strict validation of packet sizes and types to prevent buffer overflows.
* **UDP Characteristics**:

* No guarantee of delivery or order. Implement retries or acknowledgments if necessary.
* Use interpolation for smoother client-side rendering of movement updates.

* **Performance**: Optimize payload sizes and serialize data efficiently.

---
