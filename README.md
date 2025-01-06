# R-Type

![The r-type logo](./RtypeLogo.png)

This is the r-type project
You can find more information in the sections below:

## Table of contents

* [Introduction](#introduction)
* [Getting started](#getting-started)
  * [Dependencies](./doc/gettingStarted.md#dependencies)
    * [Pre-built](./doc/gettingStarted.md#pre-built)
    * [From source](./doc/gettingStarted.md#from-source)
  * [Obtaining the source code](./doc/gettingStarted.md#obtaining-the-source-code)
  * [Pre-compiled](./doc/gettingStarted.md#pre-compiled)
  * [Deploy from source](./doc/gettingStarted.md#deploy-from-source)
  * [Running the programs](./doc/gettingStarted.md#running-the-programs)
  * [Troubleshooting](./doc/gettingStarted.md#troubleshooting)
    * [Common Issues](./doc/gettingStarted.md#common-issues)
      * [Missing dependencies](./doc/gettingStarted.md#1-missing-dependencies)
      * [Build fails](./doc/gettingStarted.md#2-build-fails)
      * [Missing ressources](./doc/gettingStarted.md#3-missing-resources)
      * [Permission issues](./doc/gettingStarted.md#4-permission-issues)
      * [Runtime errors](./doc/gettingStarted.md#5-runtime-errors)
    * [Debugging tips](./doc/gettingStarted.md#debugging-tips)
    * [Getting help](./doc/gettingStarted.md#getting-help)
* [Client](#client)
  * [Introduction](./doc/client.md#introduction)
  * [Compiling](./doc/client.md#compiling)
  * [Running the client](./doc/client.md#running-the-client)
  * [Configuration file](./doc/client.md#configuration-file)
  * [Troubleshooting](./doc/client.md#troubleshooting)
    * [Common issues](./doc/client.md#common-issues)
      * [Missing dependencies](./doc/client.md#1-missing-dependencies)
      * [Cmake configuration fails](./doc/client.md#2-cmake-configuration-fails)
      * [Build errors](./doc/client.md#3-build-errors)
      * [Runtime errors](./doc/client.md#4-runtime-errors)
      * [Graphics issues](./doc/client.md#5-graphics-issues)
      * [Missing or corrupted assets](./doc/client.md#6-missing-or-corrupted-assets)
    * [Debugging Tips](./doc/client.md#debugging-tips)
    * [Getting help](./doc/client.md#getting-help)
* [Sever](#server)
  * [Introduction](./doc/server.md#introduction)
  * [Compiling](./doc/server.md#compiling)
  * [Running the server](./doc/server.md#running-the-server)
  * [Configuration file](./doc/server.md#configuration-file)
  * [Troubleshooting](./doc/server.md#troubleshooting)
    * [Common issues](./doc/server.md#common-issues)
      * [Missing dependencies](./doc/server.md#1-missing-dependencies)
      * [CMake configuration failure](./doc/server.md#2-cmake-configuration-fails)
      * [Build errors](./doc/server.md#3-build-errors)
      * [Runtime errors](./doc/server.md#4-runtime-errors)
      * [Networking issues](./doc/server.md#5-networking-issues)
      * [High latency or disconnects](./doc/server.md#6-high-latency-or-disconnects)
    * [Debugging tips](./doc/server.md#debugging-tips)
    * [Getting help](./doc/server.md#getting-help)
* [Protocol](#protocol)
  * [Brief](./doc/UDPProtocol.md#brief)
  * [UDP Protocole | SERVER / CLIENT COMMUNICATION](./doc/UDPProtocol.md#udp-protocol--server--client-communication)
    * [Binary Message Format](./doc/UDPProtocol.md#binary-message-format)
    * [Types of Messages the Server Expects and Sends](./doc/UDPProtocol.md#types-of-messages-the-server-expects-and-sends)
      * [CONNECT (0x01)](./doc/UDPProtocol.md#connect-0x01)
      * [DISCONNECT (0x02)](./doc/UDPProtocol.md#disconnect-0x02)
      * [MOVE (0x03)](./doc/UDPProtocol.md#move-0x03)
      * [SHOOT (0x04)](./doc/UDPProtocol.md#shoot-0x04)
      * [SPAWN (0x05)](./doc/UDPProtocol.md#spawn-0x05)
      * [UPDATE (0x06)](./doc/UDPProtocol.md#update-0x06)
      * [ERROR (0xFF)](./doc/UDPProtocol.md#error-0xff)
    * [Error Handling](./doc/UDPProtocol.md#error-handling)
    * [Use cases in game logic and GUI](./doc/UDPProtocol.md#use-cases-in-game-logic-and-gui)
    * [Notes on implementation](./doc/UDPProtocol.md#notes-on-implementation)
* [Commit convention](#commit-convention)
* [Authors](#authors)
* [License](#license)
* [Contributing](#contributing)
* [Code of Conduct](./CODE_OF_CONDUCT.md)

## Introduction

R-type is a game engine that is composed of a server and a client.

The aim is to have a game that can be multiplayer and have many clients connect to it.

## Getting started

* [Dependencies](./doc/gettingStarted.md#dependencies)
  * [Pre-built](./gettingStarted.md#pre-built)
  * [From source](./doc/gettingStarted.md#from-source)
* [Obtaining the source code](./doc/gettingStarted.md#obtaining-the-source-code)
* [Pre-compiled](./doc/gettingStarted.md#pre-compiled)
* [Deploy from source](./doc/gettingStarted.md#deploy-from-source)
* [Running the programs](./doc/gettingStarted.md#running-the-programs)
* [Troubleshooting](./doc/gettingStarted.md#troubleshooting)

## Client

* [Introduction](./doc/client.md#introduction)
* [Compiling](./doc/client.md#compiling)
* [Running the client](./doc/client.md#running-the-client)
* [Configuration file](./doc/client.md#configuration-file)

## Server

* [Introduction](./doc/server.md#introduction)
* [Compiling](./doc/server.md#compiling)
* [Running the server](./doc/server.md#running-the-server)
* [Configuration file](./doc/server.md#configuration-file)

## Protocol

* [Brief](./doc/UDPProtocol.md#brief)
* [UDP Protocole | SERVER / CLIENT COMMUNICATION](./doc/UDPProtocol.md#udp-protocol--server--client-communication)
  * [Binary Message Format](./doc/UDPProtocol.md#binary-message-format)
  * [Types of Messages the Server Expects and Sends](./doc/UDPProtocol.md#types-of-messages-the-server-expects-and-sends)
    * [CONNECT (0x01)](./doc/UDPProtocol.md#connect-0x01)
    * [DISCONNECT (0x02)](./doc/UDPProtocol.md#disconnect-0x02)
    * [MOVE (0x03)](./doc/UDPProtocol.md#move-0x03)
    * [SHOOT (0x04)](./doc/UDPProtocol.md#shoot-0x04)
    * [SPAWN (0x05)](./doc/UDPProtocol.md#spawn-0x05)
    * [UPDATE (0x06)](./doc/UDPProtocol.md#update-0x06)
    * [ERROR (0xFF)](./doc/UDPProtocol.md#error-0xff)
  * [Error Handling](./doc/UDPProtocol.md#error-handling)
  * [Use cases in game logic and GUI](./doc/UDPProtocol.md#use-cases-in-game-logic-and-gui)
  * [Notes on implementation](./doc/UDPProtocol.md#notes-on-implementation)

## Commit convention

If you wish to contribute, we strongly suggest that you take a look at the [COMMIT_CONVENTION](./COMMIT_CONVENTION.md)

## Authors

This project was written by:

* [Marianna Titova](https://github.com/marianna-titova)
* [Tristan Wehrle](https://github.com/floksdev)
* [Arthur-agusto Claro-sardella](https://github.com/DoctorTangerina)
* [Henry Letellier](https://github.com/HenraL)

## License

This project is licensed under the **[MIT License](./LICENSE)**.

However, because this follows the rules of the Epitech school so other terms provided by the school may apply

## Contributing

Contributions are welcome! If you would like to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m 'Add feature'`).
4. Push to the branch (`git push origin feature-name`).
5. Open a pull request.

See the [Contributing Guidelines](./CONTRIBUTING.md) for more details

## Code of conduct

Please note that we follow the [Contributor Covenant Code of Conduct](./CODE_OF_CONDUCT.md).
This means that we expect all contributors to behave in a respectful and professional manner.
If you have any questions or concerns, please don't hesitate to reach out.
