# R-Type server

## Table of contents

1. [Introduction](#introduction)
2. [Compiling](#compiling)
3. [Running the server](#running-the-server)
4. [Configuration file](#configuration-file)

## Introduction

This file is dedicated to the R-Type server binary.

This is a binary that will provide a graphical interface to the program and allow the users to be able to interract with the game.

This document will only focus on the following sections of the server binary:

* [Compilation](#compiling) (from scratch) of the server binary
* [Running the server binary](#running-the-server) (and the options for the binary)
* [Editing the configuration file](#configuration-file)

## Compiling

This section focuses on compiling the server binary without compiling the whole project (this means, without compiling the client).

If you wish to compile the project, please refer to the [Getting Stated - Dependency - from source](../getting_started/README.md#from-source) to make sure you have the required dependencies set up on your system.

If you wish to compile the whole project from source, please refer to the [Getting Started - Deploy from source](../getting_started/README.md#deploy-from-source)

Wether you are on Mac, Windows or Linux, the lines are the same, however, where Linux and Mac will use bash, Windows will use batch `cmd.exe`, most of the commands used are similare, however:

* `ls` becomes `dir`
* `cd` is the same
* `rm` becomes `del`
* `cp` becomes `copy`
* `mv` becomes `move`
* `rm -rf` becomes `rmdir /s /q`
* `tree` is the same (although it is not natively installed on all linux systems)

In Windows, `/`  become `\` and you do not need to prefix files with `./`.

Now that the differences are explained, let us attend to the core of this subject, compiling the program.

To do so, we will:

* Navigate to the `server` folder
* Create a `build` folder

We will now configure our project.

We will thus, run `cmake -S . -B ./build` in the `server` folder and let it run it's course.

> Please make sure you have a stable internet connection or you will need to re-run this command for it to finish completing it's tasks.
>
> This is only the case if you get a cloning error, red text saying something simmilare the following: `Trying to clone , attempt 1 [...] attempt 3 error`
>
> However, if it is a missing dependency, try and install it, then re-run the cmake command.

The output of the command should be similare to the following:

> The exact output may vary depending on the system but a simple rule to keep in mind is, `no red color`=`no error`.

```bash
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- Configuring done (14.7s)
-- Generating done (0.0s)
-- Build files have been written to: /home/<user_account>/path/to/the/project/rtype/server/build
```

Once this command has run it's course, we can move on to the next section `Compiling`.
To do so, while remaining in the same directory, you can run the command: `cmake --build ./build`.

The following output should appear colorised on your terminal (could not be reproduced here), this output should be simmilare to yours:

```bash
[ 14%] Building CXX object CMakeFiles/r-type_server.dir/src/GameManager.cpp.o
[ 28%] Building CXX object CMakeFiles/r-type_server.dir/src/main.cpp.o
[ 42%] Building CXX object CMakeFiles/r-type_server.dir/src/NetworkManager.cpp.o
[ 57%] Building CXX object CMakeFiles/r-type_server.dir/src/ProtocolHandler.cpp.o
[ 71%] Building CXX object CMakeFiles/r-type_server.dir/src/Server.cpp.o
[ 85%] Building CXX object CMakeFiles/r-type_server.dir/src/ThreadPool.cpp.o
[100%] Linking CXX executable r-type_server
[100%] Built target r-type_server
```

Now, when you look into the build folder using `ls -ls build`

> Again, here, your output might be colourised, but due to the limitations of this document, they could ne be represented.

```bash
total 5224
  20 -rw-rw-r--  1 account_name account_name   50826 déc.  26 08:15 CMakeCache.txt
   4 drwxrwxr-x  6 account_name account_name    4096 déc.  26 08:24 CMakeFiles
   4 -rw-rw-r--  1 account_name account_name    1895 déc.  26 08:15 cmake_install.cmake
   4 drwxrwxr-x  8 account_name account_name    4096 déc.  26 08:15 _deps
   4 drwxrwxr-x  5 account_name account_name    4096 déc.  26 08:15 lib
  12 -rw-rw-r--  1 account_name account_name   10147 déc.  26 08:15 Makefile
 420 -rwxrwxr-x  1 account_name account_name  426040 déc.  26 08:24 r-type_server
```

The next step is to copy the binary `r-type_server` from the `build` folder to the base of the repository `rtype`.

Assuming you are still in the `server` folder, the following command to execute is: `cp ./build/r-type_server ../`

You can now copy (assuming you are still located in the `server` folder) the `server_config.toml` to the base of the repository with the following command: `cp server_config.toml ../`.

We are now done with the compilation of the server binary. You can keep this terminal open an run the `cd ..` command (assuming you are still located in the `server` folder) or reopen a fresh one in the base of the repository.

You can then follow the [Running the server](#running-the-server) section.

## Running the server

To check if the server binary is working, you can, in a terminal located in the same folder as the binary, run the command `./r-type_server --help`

This should output the following content:

```bash
UDP Socket initialized on port 4242
Initializing game manager in progress
Server components build : ✅
Server started : ✅
```

## Configuration file

The configuration file is a toml file that contains the settings for the server. Here is the default configuration:

> The field names should not be changed because they are directly referenced by the program, however, feel free to change the field values.
>
> But, be warned, with great power comes great responsability, changing critical ressources can lead to unexpected program behaviours.
>
>
>The default file name if `server_config.toml`
>
>The default expected location is `<the same folder as the executable>`
>
> All relative paths located in the configuration file are based on the location where the program is located, but more importantly, they will be calculated by the program the moment it is run (thus, if not launched in the same folder, ressources may not be available).

```toml
[Connectivity]
# The host on which the server is listening
host="0.0.0.0"
# The port on which the server is listening
port=4242

[client]
# The maximum number of clients that can connect to the server
max_clients=100
# The maximum number of clients that can be in the same room
max_clients_per_room=10
# The maximum number of rooms that can be created
max_rooms=10

[timeouts]
# The maximum time in seconds a client can stay inactive connected before being disconnected (in seconds)
max_connection_time=300
```

Let's break it down:

Located in the `[Connectivity]` section is:

* `host`: The host on which the server is listening. It can be a local IP address
* `port`: The port on which the server is listening

Located in the `[client]`  section:

* `max_clients`: The maximum number of clients that can connect to the server
* `max_clients_per_room`: The maximum number of clients that can be in the same room
* `max_rooms`: The maximum number of rooms that can be created
* `max_connection_time`: The maximum time in seconds a client can stay inactive connected before being disconnected

Located in the `[timeouts]` section:

* `max_connection_time`: The maximum time in seconds a client can stay inactive connected before being disconnected
