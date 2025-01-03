# R-Type

This is the r-type project
You can find more information in the sections below:

## Table of contents

* [Introduction](#introduction)
* [Getting started](#getting-started)
  * [Dependencies](./doc/getting_started/README.md#dependencies)
    * [Pre-built](./getting_started/README.md#pre-built)
    * [From source](./doc/getting_started/README.md#from-source)
  * [Obtaining the source code](./doc/getting_started/README.md#obtaining-the-source-code)
  * [Pre-compiled](./doc/getting_started/README.md#pre-compiled)
  * [Deploy from source](./doc/getting_started/README.md#deploy-from-source)
  * [Running the programs](./doc/getting_started/README.md#running-the-programs)
  * [Troubleshooting](./doc/getting_started/README.md#troubleshooting)
    * [Common Issues](./getting_started/README.md#common-issues)
      * [Missing dependencies](./getting_started/README.md#1-missing-dependencies)
      * [Build fails](./getting_started/README.md#2-build-fails)
      * [Missing ressources](./getting_started/README.md#3-missing-resources)
      * [Permission issues](./getting_started/README.md#4-permission-issues)
      * [Runtime errors](./getting_started/README.md#5-runtime-errors)
    * [Debugging tips](./getting_started/README.md#debugging-tips)
    * [Getting help](./getting_started/README.md#getting-help)
* [Client](#client)
  * [Introduction](./doc/client/README.md#introduction)
  * [Compiling](./doc/client/README.md#compiling)
  * [Running the client](./doc/client/README.md#running-the-client)
  * [Configuration file](./doc/client/README.md#configuration-file)
  * [Troubleshooting](./doc/client/README.md#troubleshooting)
    * [Common issues](./doc/client/README.md#common-issues)
      * [Missing dependencies](./doc/client/README.md#1-missing-dependencies)
      * [Cmake configuration fails](./doc/client/README.md#2-cmake-configuration-fails)
      * [Build errors](./doc/client/README.md#3-build-errors)
      * [Runtime errors](./doc/client/README.md#4-runtime-errors)
      * [Graphics issues](./doc/client/README.md#5-graphics-issues)
      * [Missing or corrupted assets](./doc/client/README.md#6-missing-or-corrupted-assets)
    * [Debugging Tips](./doc/client/README.md#debugging-tips)
    * [Getting help](./doc/client/README.md#getting-help)
* [Sever](#server)
  * [Introduction](./doc/server/README.md#introduction)
  * [Compiling](./doc/server/README.md#compiling)
  * [Running the server](./doc/server/README.md#running-the-server)
  * [Configuration file](./doc/server/README.md#configuration-file)
  * [Troubleshooting](./doc/server/README.md#troubleshooting)
    * [Common issues](./doc/server/README.md#common-issues)
      * [Missing dependencies](./doc/server/README.md#1-missing-dependencies)
      * [CMake configuration failure](./doc/server/README.md#2-cmake-configuration-fails)
      * [Build errors](./doc/server/README.md#3-build-errors)
      * [Runtime errors](./doc/server/README.md#4-runtime-errors)
      * [Networking issues](./doc/server/README.md#5-networking-issues)
      * [High latency or disconnects](./doc/server/README.md#6-high-latency-or-disconnects)
    * [Debugging tips](./doc/server/README.md#debugging-tips)
    * [Getting help](./doc/server/README.md#getting-help)
* [Protocol](#protocol)
  * [Brief](./doc/protocol/README.md#brief)
  * [UDP Protocole | SERVER / CLIENT COMMUNICATION](./doc/protocol/README.md#udp-protocol--server--client-communication)
  * [Binary Message Format](./doc/protocol/README.md#binary-message-format)
  * [Types of Messages the Server Expects and Sends](./doc/protocol/README.md#types-of-messages-the-server-expects-and-sends)
  * [Error Handling](./doc/protocol/README.md#error-handling)
  * [Example Usage](./doc/protocol/README.md#example-usage)
    * [Client side](./doc/protocol/README.md#client-side)
    * [Server side](./doc/protocol/README.md#server-side)
* [Commit convention](#commit-convention)
* [Authors](#authors)
* [License](#license)
* [Contributing](#contributing)
* [Code of Conduct](./CODE_OF_CONDUCT.md)

## Introduction

R-type is a game engine that is composed of a server and a client.

The aim is to have a game that can be multiplayer and have many clients connect to it.

## Getting started

* [Dependencies](./doc/getting_started/README.md#dependencies)
  * [Pre-built](./getting_started/README.md#pre-built)
  * [From source](./doc/getting_started/README.md#from-source)
* [Obtaining the source code](./doc/getting_started/README.md#obtaining-the-source-code)
* [Pre-compiled](./doc/getting_started/README.md#pre-compiled)
* [Deploy from source](./doc/getting_started/README.md#deploy-from-source)
* [Running the programs](./doc/getting_started/README.md#running-the-programs)
* [Troubleshooting](./doc/getting_started/README.md#troubleshooting)

## Client

* [Introduction](./doc/client/README.md#introduction)
* [Compiling](./doc/client/README.md#compiling)
* [Running the client](./doc/client/README.md#running-the-client)
* [Configuration file](./doc/client/README.md#configuration-file)

## Server

* [Introduction](./doc/server/README.md#introduction)
* [Compiling](./doc/server/README.md#compiling)
* [Running the server](./doc/server/README.md#running-the-server)
* [Configuration file](./doc/server/README.md#configuration-file)

## Protocol

* [Brief](./doc/protocol/README.md#brief)
* [UDP Protocole | SERVER / CLIENT COMMUNICATION](./doc/protocol/README.md#udp-protocol--server--client-communication)
* [Binary Message Format](./doc/protocol/README.md#binary-message-format)
* [Types of Messages the Server Expects and Sends](./doc/protocol/README.md#types-of-messages-the-server-expects-and-sends)
* [Error Handling](./doc/protocol/README.md#error-handling)
* [Example Usage](./doc/protocol/README.md#example-usage)
  * [Client side](./doc/protocol/README.md#client-side)
  * [Server side](./doc/protocol/README.md#server-side)

## Commit convention

If you wish to contribute, we strongly suggest that you take a look at the [COMMIT_CONVENTION](./COMMIT_CONVENTION.md)

## Authors

This project was written by:

* [Marianna Titova](https://github.com/marianna-titova)
* [Tristan Wehrle](https://github.com/floksdev)
* [Arthur-agusto Claro-sardella](https://github.com/DoctorTangerina)
* [Henry Letellier](https://github.com/HenraL)

## License

This project is licensed under the **[MIT License](LICENSE)**.

However, because this follows the rules of the Epitech school so other terms provided by the school may apply

## Contributing

Contributions are welcome! If you would like to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m 'Add feature'`).
4. Push to the branch (`git push origin feature-name`).
5. Open a pull request.

See the [Contributing Guidelines](CONTRIBUTING.md) for more details

## Code of conduct

Please note that we follow the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md)
. This means that we expect all contributors to behave in a respectful and professional manner.
If you have any questions or concerns, please don't hesitate to reach out.
