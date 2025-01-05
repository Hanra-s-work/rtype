# **UDP Protocol Documentation**

This section describes the binary UDP protocol used for communication between the server and client in the R-Type game. This documentation aims to provide clarity on the structure of packets, message types, and their intended usage in both game logic and GUI components.

#### **1\. Binary Message Format**

Each UDP message exchanged follows a binary format designed for efficiency and scalability. The structure of a packet is as follows:

| Field | Size (bits) | Description |
| :---- | :---- | :---- |
| Message Type | 8 | Identifies the type of message (e.g., MOVE, SHOOT). |
| Message Size | 16 | Specifies the payload size in bytes. |
| Payload | Variable | Contains data specific to the message type. Optional depending on the type. |

####

#### ---

####

#### **2\. Message Types and Formats**

Below is a detailed list of message types, their formats, and how they are used.

1. **CONNECT (0x01)**
   * **Description**: Used by the client to establish a connection with the server.
   * **Format**:

        | \[0x01\]\[0x00\]\[0x08\]\[username...\] |
        | :---- |

   * **Payload**: `username` (max 8 characters), padded with null bytes if shorter.
   * **Example**: A client connecting with the username "Player1" sends:

        | 0x01 0x00 0x08 50 6c 61 79 65 72 31 00 |
        | :---- |

2. **DISCONNECT (0x02)**

* **Description:** Sent by the client to disconnect from the server.

* **Format:**

      | \[0x02\]\[0x00\]\[0x00\] |
      | :---- |

3. **MOVE (0x03)**

* **Description:** Informs the server of player movement direction.

* **Format:**

        | \[0x03\]\[0x00\]\[0x01\]\[direction\] |
        | :---- |

* **Payload:**

  * `0x01` \= UP
  * `0x02` \= DOWN
  * `0x03` \= LEFT
  * `0x04` \= RIGHT

* **Example:** A player moving UP:

    | 0x03 0x00 0x01 0x01 |
    | :---- |

4. **SHOOT (0x04)**

* **Description:** Indicates a shooting action by the player.

* **Format:**

    | \[0x04\]\[0x00\]\[0x02\]\[angleX\]\[angleY\] |
    | :---- |

* **Payload: Binary representation of shooting angle.**

5. **SPAWN (0x05)**

* **Description:** Notifies the client of a new entity (enemy, object) in the game world.

* **Format:**

    | \[0x05\]\[0x00\]\[size\]\[id\]\[x\]\[y\]\[type\] |
    | :---- |

* **Payload:**

  * `id` (1 byte): Unique entity ID.
  * `x`, `y` (2 bytes each): Coordinates.
  * `type` (1 byte): Entity type (e.g., enemy, collectible).

6. **UPDATE (0x06)**

* **Description:** Sends game state updates to all clients.

* **Format:**

  | \[0x06\]\[0x00\]\[size\]\[entity1\_data\]\[entity2\_data\]... |
  | :---- |

* **Payload:** A series of entity data blocks, each formatted as:

| \[id\]\[x\]\[y\]\[type\] |
| :---- |

7. **ERROR (0xFF)**

* **Description**: Communicates an error or invalid action.

* **Format**:

  | \[0xFF\]\[0x00\]\[size\]\[error\_code\] |
  | :---- |

* **Payload**: Error-specific code for debugging.

---

#### **3\. Error Handling**

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

#### **4\. Use Cases in Game Logic and GUI**

* **Game Logic**:

* **MOVE** and **SHOOT:** Update player states and synchronize actions.
* **SPAWN:** Trigger in-game events like enemy appearances.
* **UPDATE:** Reconcile server-authoritative state with client predictions.

* **GUI**:

* Render **SPAWN** and **UPDATE** messages for real-time feedback.
* Display error messages from **ERROR** packets.

---

####

#### **5\. Notes on Implementation**

* **Data Integrity**: Ensure strict validation of packet sizes and types to prevent buffer overflows.
* **UDP Characteristics**:

* No guarantee of delivery or order. Implement retries or acknowledgments if necessary.
* Use interpolation for smoother client-side rendering of movement updates.

* **Performance**: Optimize payload sizes and serialize data efficiently.

---
