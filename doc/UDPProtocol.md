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
    * [UPDATE (0x06)](#update-0x06)
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
| Message Size | 16 | Specifies the payload size in bytes. |
| Payload | Variable | Contains data specific to the message type. Optional depending on the type. |

### **Types of Messages the Server Expects and Sends**

Types of messages sent by the client to the server:

#### **CONNECT (0x01)**

* **Description**: The client connects to the server.
* **Format**:

      | \[0x01\]\[0x00\]\[0x08\]\[username...\] |
      | :---- |

* **Payload**: `username` (8 characters max, padded with null bytes if shorter) is the name of the player.
* **Example**: A client connecting with the username "Player1" sends:

      | 0x01 0x00 0x08 50 6c 61 79 65 72 31 00 |
      | :---- |

#### **DISCONNECT (0x02)**

* **Description**: The client disconnects from the server.

* **Format**:

      | \[0x02\]\[0x00\]\[0x00\] |
      | :---- |

#### **MOVE (0x03)**

* **Description**: Informs the server of player movement direction.
* **Format**:

        | \[0x03\]\[0x00\]\[0x01\]\[direction\] |
        | :---- |

* **Payload**:
  * `0x01` \= UP
  * `0x02` \= DOWN
  * `0x03` \= LEFT
  * `0x04` \= RIGHT

* **Example**: A player moving `UP`:

    | 0x03 0x00 0x01 0x01 |
    | :---- |

#### **SHOOT (0x04)**

* **Description**: The player shoots.
* **Format**:

    | \[0x04\]\[0x00\]\[0x02\]\[angleX\]\[angleY\] |
    | :---- |

* **Payload**: 0x01 0x02 (for example, for a shooting angle in binary coordinates).

#### **SPAWN (0x05)**

* **Description**: Notifies the client of a new entity (enemy, object) in the game world.
* **Format**:

    | \[0x05\]\[0x00\]\[size\]\[id\]\[x\]\[y\]\[type\] |
    | :---- |

* **Payload**: [ID, x, y, type] of the entity to spawn.

  * `id` (1 byte): Unique entity ID.
  * `x`, `y` (2 bytes each): Coordinates.
  * `type` (1 byte): Entity type (e.g., enemy, collectible).

#### **UPDATE (0x06)**

* **Description**: The server sends updated information on the game state to the clients.

* **Format**:

  | \[0x06\]\[0x00\]\[size\]\[entity1\_data\]\[entity2\_data\]... |
  | :---- |

* **Payload**: A series of entity data blocks, each formatted as:

  | \[id\]\[x\]\[y\]\[type\] |
  | :---- |

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

  | 0xFF 0x00 0x01 0x01 |
  | :---- |

* **Code:**
  * `0x01`: Invalid action.

* **Server Errors:**
  Malformed packets or server-side issues result in an error response:

  | 0xFF 0x00 0x02 0x00 0x01 |
  | :---- |

* **Error Code:**
  * `0x00 0x01`: Malformed packet

---

### **Use cases in game logic and GUI**

* **Game Logic**:

* **MOVE** and **SHOOT:** Update player states and synchronize actions.
* **SPAWN:** Trigger in-game events like enemy appearances.
* **UPDATE:** Reconcile server-authoritative state with client predictions.

* **GUI**:

* Render **SPAWN** and **UPDATE** messages for real-time feedback.
* Display error messages from **ERROR** packets.

---

### **Notes on Implementation**

* **Data Integrity**: Ensure strict validation of packet sizes and types to prevent buffer overflows.
* **UDP Characteristics**:

* No guarantee of delivery or order. Implement retries or acknowledgments if necessary.
* Use interpolation for smoother client-side rendering of movement updates.

* **Performance**: Optimize payload sizes and serialize data efficiently.

---
