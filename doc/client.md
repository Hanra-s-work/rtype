# R-Type Client

## Table of contents

* [Introduction](#introduction)
* [Compiling](#compiling)
* [Running the client](#running-the-client)
* [Configuration file](#configuration-file)
* [Troubleshooting](#troubleshooting)
  * [Common issues](#common-issues)
    * [Missing dependencies](#1-missing-dependencies)
    * [Cmake configuration fails](#2-cmake-configuration-fails)
    * [Build errors](#3-build-errors)
    * [Runtime errors](#4-runtime-errors)
    * [Graphics issues](#5-graphics-issues)
    * [Missing or corrupted assets](#6-missing-or-corrupted-assets)
  * [Debugging Tips](#debugging-tips)
  * [Getting help](#getting-help)

## Introduction

This file is dedicated to the R-Type client binary.

This is a binary that will provide a graphical interface to the program and allow the users to be able to interract with the game.

This document will only focus on the following sections of the client binary:

* [Compilation](#compiling) (from scratch) of the client binary
* [Running the client binary](#running-the-client) (and the options for the binary)
* [Editing the configuration file](#configuration-file)

## Compiling

This section focuses on compiling the client binary without compiling the whole project (this means, without compiling the server).

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

* Navigate to the `gui` folder
* Create a `build` folder

We will now configure our project.

We will thus, run `cmake -S . -B ./build` in the `gui` folder and let it run it's course.

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
-- Found X11: /usr/include  found components: Xrandr Xcursor Xi 
-- Looking for XOpenDisplay in /usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXext.so
-- Looking for XOpenDisplay in /usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXext.so - found
-- Looking for gethostbyname
-- Looking for gethostbyname - found
-- Looking for connect
-- Looking for connect - found
-- Looking for remove
-- Looking for remove - found
-- Looking for shmat
-- Looking for shmat - found
-- Looking for IceConnectionNumber in ICE
-- Looking for IceConnectionNumber in ICE - found
-- Found OpenGL: /usr/lib/x86_64-linux-gnu/libOpenGL.so  found components: OpenGL 
-- libudev stable: 1
-- Found UDev: /usr/lib/x86_64-linux-gnu/libudev.so
--    include: /usr/include
-- Found UDev: /usr/include  
-- Performing Test ATOMIC_TEST
-- Performing Test ATOMIC_TEST - Success
-- Found Freetype: /usr/lib/x86_64-linux-gnu/libfreetype.so  
-- Found Vorbis: /usr/include  
-- Found FLAC: /usr/lib/x86_64-linux-gnu/libFLAC.so  
-- Configuring done (93.5s)
-- Generating done (0.1s)
-- Build files have been written to: /home/<user_account>/path/to/the/build/folder/rtype/gui/build
```

Once this command has run it's course, we can move on to the next section `Compiling`.
To do so, while remaining in the same directory, you can run the command: `cmake --build ./build`.

The following output should appear colorised on your terminal (could not be reproduced here), this output should be simmilare to yours:

```bash
[  0%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Clock.cpp.o
[  1%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Err.cpp.o
[  2%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Sleep.cpp.o
[  3%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/String.cpp.o
[  3%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Utils.cpp.o
[  4%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Vector2.cpp.o
[  5%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Vector3.cpp.o
[  6%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/FileInputStream.cpp.o
[  6%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/MemoryInputStream.cpp.o
[  7%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Unix/SleepImpl.cpp.o
[  8%] Linking CXX static library ../../../lib/libsfml-system.a
[  8%] Built target sfml-system
[  9%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/AudioResource.cpp.o
[ 10%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/AudioDevice.cpp.o
[ 11%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Listener.cpp.o
[ 11%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Miniaudio.cpp.o
[ 12%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/MiniaudioUtils.cpp.o
[ 13%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Music.cpp.o
[ 13%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/PlaybackDevice.cpp.o
[ 14%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Sound.cpp.o
[ 15%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundBuffer.cpp.o
[ 16%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundBufferRecorder.cpp.o
[ 16%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/InputSoundFile.cpp.o
[ 17%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/OutputSoundFile.cpp.o
[ 18%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundRecorder.cpp.o
[ 19%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundSource.cpp.o
[ 19%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundStream.cpp.o
[ 20%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileFactory.cpp.o
[ 21%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderFlac.cpp.o
[ 22%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderMp3.cpp.o
[ 22%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderOgg.cpp.o
[ 23%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderWav.cpp.o
[ 24%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileWriterFlac.cpp.o
[ 24%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileWriterOgg.cpp.o
[ 25%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileWriterWav.cpp.o
[ 26%] Linking CXX static library ../../../lib/libsfml-audio.a
[ 26%] Built target sfml-audio
[ 26%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Clipboard.cpp.o
[ 27%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Context.cpp.o
[ 28%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Cursor.cpp.o
[ 29%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/GlContext.cpp.o
[ 29%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/GlResource.cpp.o
[ 30%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Joystick.cpp.o
[ 31%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/JoystickManager.cpp.o
[ 32%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Keyboard.cpp.o
[ 32%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Mouse.cpp.o
[ 33%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Touch.cpp.o
[ 34%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Sensor.cpp.o
[ 35%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/SensorManager.cpp.o
[ 35%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/VideoMode.cpp.o
[ 36%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Vulkan.cpp.o
[ 37%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Window.cpp.o
[ 37%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/WindowBase.cpp.o
[ 38%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/WindowImpl.cpp.o
[ 39%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/CursorImpl.cpp.o
[ 40%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/ClipboardImpl.cpp.o
[ 40%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/InputImpl.cpp.o
[ 41%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/KeyboardImpl.cpp.o
[ 42%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/KeySymToKeyMapping.cpp.o
[ 43%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/KeySymToUnicodeMapping.cpp.o
[ 43%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/SensorImpl.cpp.o
[ 44%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/Display.cpp.o
[ 45%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/VideoModeImpl.cpp.o
[ 46%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/VulkanImplX11.cpp.o
[ 46%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/WindowImplX11.cpp.o
[ 47%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/GlxContext.cpp.o
[ 48%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/JoystickImpl.cpp.o
[ 49%] Linking CXX static library ../../../lib/libsfml-window.a
[ 49%] Built target sfml-window
[ 49%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.o
[ 50%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.o
[ 51%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.o
[ 51%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.o
[ 52%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.o
[ 53%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.o
[ 54%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.o
[ 54%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.o
[ 55%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.o
[ 56%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Unix/SocketImpl.cpp.o
[ 57%] Linking CXX static library ../../../lib/libsfml-network.a
[ 57%] Built target sfml-network
[ 58%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/BlendMode.cpp.o
[ 58%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Font.cpp.o
[ 59%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Glsl.cpp.o
[ 60%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/GLCheck.cpp.o
[ 61%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/GLExtensions.cpp.o
[ 61%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Image.cpp.o
[ 62%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderStates.cpp.o
[ 63%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTexture.cpp.o
[ 64%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTarget.cpp.o
[ 64%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderWindow.cpp.o
[ 65%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Shader.cpp.o
[ 66%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/StencilMode.cpp.o
[ 67%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Texture.cpp.o
[ 67%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/TextureSaver.cpp.o
[ 68%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Transform.cpp.o
[ 69%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Transformable.cpp.o
[ 69%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/View.cpp.o
[ 70%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Shape.cpp.o
[ 71%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/CircleShape.cpp.o
[ 72%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RectangleShape.cpp.o
[ 72%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/ConvexShape.cpp.o
[ 73%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Sprite.cpp.o
[ 74%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Text.cpp.o
[ 75%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/VertexArray.cpp.o
[ 75%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/VertexBuffer.cpp.o
[ 76%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTextureImplFBO.cpp.o
[ 77%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTextureImplDefault.cpp.o
[ 78%] Linking CXX static library ../../../lib/libsfml-graphics.a
[ 78%] Built target sfml-graphics
[ 79%] Building CXX object CMakeFiles/r-type_client.dir/src/Main.cpp.o
[ 80%] Building CXX object CMakeFiles/r-type_client.dir/src/Debug.cpp.o
[ 80%] Building CXX object CMakeFiles/r-type_client.dir/src/RealMain.cpp.o
[ 81%] Building CXX object CMakeFiles/r-type_client.dir/src/MainClass.cpp.o
[ 82%] Building CXX object CMakeFiles/r-type_client.dir/src/TOMLLoader.cpp.o
[ 83%] Building CXX object CMakeFiles/r-type_client.dir/src/HelpFunctions.cpp.o
[ 83%] Building CXX object CMakeFiles/r-type_client.dir/src/ExceptionHandling.cpp.o
[ 84%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/Network/NetworkManager.cpp.o
[ 85%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/Network/ProtocolHandler.cpp.o
[ 86%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Component.cpp.o
[ 86%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/EntityNode.cpp.o
[ 87%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/TextComponent.cpp.o
[ 88%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/MusicComponent.cpp.o
[ 89%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/ShapeComponent.cpp.o
[ 89%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/SpriteComponent.cpp.o
[ 90%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/ButtonComponent.cpp.o
[ 91%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/TextureComponent.cpp.o
[ 91%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/CollisionComponent.cpp.o
[ 92%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/AnimationComponent.cpp.o
[ 93%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/InputSystem.cpp.o
[ 94%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/ButtonSystem.cpp.o
[ 94%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/RenderSystem.cpp.o
[ 95%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/AnimationSystem.cpp.o
[ 96%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/key.cpp.o
[ 97%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/Font.cpp.o
[ 97%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/Clock.cpp.o
[ 98%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/Window.cpp.o
[ 99%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/MouseInfo.cpp.o
[100%] Building CXX object CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/EventManager.cpp.o
[100%] Linking CXX executable r-type_client
[100%] Built target r-type_client
```

Now, when you look into the build folder using `ls -ls build`

> Again, here, your output might be colourised, but due to the limitations of this document, they could ne be represented.

```bash
total 5224
  52 -rw-rw-r--  1 account_name account_name   50826 déc.  26 08:15 CMakeCache.txt
   4 drwxrwxr-x  7 account_name account_name    4096 déc.  26 08:24 CMakeFiles
   4 -rw-rw-r--  1 account_name account_name    1895 déc.  26 08:15 cmake_install.cmake
   4 drwxrwxr-x 11 account_name account_name    4096 déc.  26 08:15 _deps
   4 drwxrwxr-x  6 account_name account_name    4096 déc.  26 08:15 lib
  44 -rw-rw-r--  1 account_name account_name   44494 déc.  26 08:15 Makefile
5112 -rwxrwxr-x  1 account_name account_name 5231784 déc.  26 08:24 r-type_client
```

The next step is to copy the binary `r-type_client` from the `build` folder to the base of the repository `rtype`.

Assuming you are still in the `gui` folder, the following command to execute is: `cp ./build/r-type_client ../`

You can now copy (assuming you are still located in the `gui` folder) the `client_config.toml` to the base of the repository with the following command: `cp client_config.toml ../`.

We are now done with the compilation of the client binary. You can keep this terminal open an run the `cd ..` command (assuming you are still located in the `gui` folder) or reopen a fresh one in the base of the repository.

You can then follow the [Running the client](#running-the-client) section.

## Running the client

To check if the client binary is working, you can, in a terminal located in the same folder as the binary, run the command `./r-type_client --help`

This should output the following content:

```bash
USAGE:
        ./r-type_client [--ip] [--port] [--debug] [--help] [--full-screen] [--window-width] [--window-height] [--frame-rate-limit] [--config-file]

OPTIONS:
        --ip="127.0.0.1"                Set the value of the ip on which the program will communicate. (Default value: 127.0.0.1)
        --port="5000"                   Set the value of the port on which the program will communicate. (Default value: 5000)
        --debug                         Enable debug logging.
        --help                          Display this help message and exit.
        --full-screen                   Enable full screen mode.
        --window-width="800"            Set the width of the window. (Default value: 800)
        --window-height="600"           Set the height of the window. (Default value: 600)
        --frame-rate-limit="60"         Set the frame rate limit of the window. (Default value: 60)
        --config-file="client_config.toml"      Set the path to the toml file that contains the sprites to load. (Default value: client_config.toml)

AUTHORS:
This program was created for Epitech project by students of the Epitech school.
```

Here is a breakdown of the different options for the program:

* `--ip`: The IP address on which the program will communicate to the server, this is an [ipv4](https://en.wikipedia.org/wiki/IPv4) format.
* `--port`: The [port](https://en.wikipedia.org/wiki/Port_(computer_networking)) on which the program will communicate.
* `--debug`: Enable debug logging. this will look something like this: `[<year>-<month>-<day> <hour>:<minute>:<second>.<millisecond>] DEBUG: <message>`,example: `[2024-12-26 8:48:45.608] DEBUG: A key was pressed, it's code is: 'K'.`
* `--help`: Display this help message and exit.
* `--full-screen`: Enable full screen mode, this is a great option for immersive modes.
* `--window-width`: The width of the window, this is a way to control it's width, has no effect in fullScreen.
* `--window-height`: The height of the window, this is a way to control it's height, has no effect in fullScreen.
* `--frame-rate-limit`: The frame rate limit of the window, 60 is the default recommended value, but the minimum accepted is 10 and the maximum is 1000.
* `--config-file`: The path to the toml file that contains the sprites to load, this flag is required if the location of the configuration file differs from the default option. If the program cannot find it's file, it will exit.

## Configuration file

The configuration file is a toml file that contains the sprites, music and fonts to load. Here is the default configuration:

> The field names should not be changed because they are directly referenced by the program, however, feel free to change the field values.
>
> But, be warned, with great power comes great responsability, changing critical ressources can lead to unexpected program behaviours.
>
>
>The default file name if `client_config.toml`
>
>The default expected location is `<the same folder as the executable>`
>
> All relative paths located in the configuration file are based on the location where the program is located, but more importantly, they will be calculated by the program the moment it is run (thus, if not launched in the same folder, ressources may not be available).

```toml
# The font
[font]

# Default structure
# [font.<font_name>] # the name of the font (unique identifier)
# name = "<name of the font>" # set the name of the font  (a human readable name)
# path = "<path to the font file>" # set the path to the file (supported format, ttf, otf [and other SFML Font supported formats])
# default_size = <size> # (0 -> 100) set the default size of the font to display, in pixels
# bold = false # (or true) set the font to bold
# italic = false # (or true) set the font to italic

# The font that will be used for title sections of the program
[font.title]
name = "Color Basic"
path = "assets/font/Color Basic/TTF Fonts/color_basic.ttf"
default_size = 50
bold = false
italic = false

# The font that will be used for the rest of the text to display
[font.body]
name = "Joystix Monospace"
path = "assets/font/Joystix/TTF Fonts/joystix_monospace.ttf"
default_size = 50
bold = false
italic = false

# The font that will be defaulted to when no other font is specified or available
[font.default]
name = "6809 Chargen"
path = "assets/font/6809 Chargen/TTF Fonts/6809_chargen.ttf"
default_size = 50
bold = false
italic = false

# The music
[music]

# Default structure
# [music.<music_name>] # the name of the music (unique identifier)
# name = "<name of the music>" # set the name of the music  (a human readable name)
# path = "<valid path to the audio file>" # set the path to the file (supported format, ogg, wav [and other SFML Music supported formats])
# loop = true # (or false) # play the music on repeat
# volume = <volume> # (0 -> 100) set the volume of the track to play.

[music.mainMenu]
name = "Main Menu"
path = "assets/audio/2019-12-11_-_Retro_Platforming_-_David_Fesliyan.ogg"
loop = true
volume = 100

[music.bossFight]
name = "Boss Fight"
path = "assets/audio/2021-08-30_-_Boss_Time_-_www.FesliyanStudios.com.ogg"
loop = true
volume = 100

[music.gameLoop]
name = "Game Loop"
path = "assets/audio/FASTER-2020-03-22_-_A_Bit_Of_Hope_-_David_Fesliyan.ogg"
loop = true
volume = 100

[music.shooting]
name = "Shooting"
path = "assets/audio/Laser-A1-www.fesliyanstudios.com.ogg"
loop = false
volume = 100

[music.damage]
name = "Damage"
path = "assets/audio/Undertale_Damage_Sound_Effect.ogg"
loop = false
volume = 100

[music.dead]
name = "Dead"
path = "assets/audio/Bomb-Explosion-Big-www.fesliyanstudios.com.ogg"
loop = false
volume = 100

[music.button]
name = "Button"
path = "assets/audio/Game-Menu-Selection-Z-www.fesliyanstudios.com.ogg"
loop = false
volume = 100

[music.gameOver]
name = "Game Over"
path = "assets/audio/game-over-arcade.ogg"
loop = false
volume = 100

[music.success]
name = "Success"
path = "assets/audio/success-fanfare-trumpets-6185.ogg"
loop = false
volume = 100

# The logo of the program

# Default structure
# [icon] # the name of the logo (unique identifier)
# name = "Logo Name" # the name of the logo
# path = "<path to the logo>" # set the path to the logo image
# width = <width> # (0 -> 1000) set the width of the logo (Default: 256)
# height = <height> # (0 -> 1000) set the height of the logo (Default: 256)
# x = <x> # (0 -> 1000) set the x position of the logo (Default: 0)
# y = <y> # (0 -> 1000) set the y position of the logo (Default: 0)

[icon]
name = "R-type"
path = "assets/icon/RtypeLogo.png"
width = 256
height = 256
x = 0
y = 0


# the background for the program
[backgrounds]

# Default structure
# [backgrounds.<background_name>] # the name of the background (unique identifier)
# name = "<name of the background>" # set the name of the background  (a human readable name)
# path = "<path to the background>" # set the path to the background image
# x = <x> # (0 -> 1000) set the x position of the background (Default: 0)
# y = <y> # (0 -> 1000) set the y position of the background (Default: 0)
# allow_as_level_background = true # (or false) allow the background to be used as a level background (Default: true)

# The backgrounds to manage

[backgrounds.mainMenu]
name = "Main Menu"
path = "assets/background/black_hole.jpeg"
x = 0
y = 0
allow_as_level_background = true

[backgrounds.settings]
name = "Settings"
path = "assets/background/blue_star_space.jpeg"
x = 0
y = 0
allow_as_level_background = true

[backgrounds.gameOver]
name = "Game Over"
path = "assets/background/dark_even_sky.jpeg"
x = 0
y = 0
allow_as_level_background = true

[backgrounds.connectionFailed]
name = "Connection Failed"
path = "assets/background/connection_space.jpeg"
x = 0
y = 0
allow_as_level_background = false

[backgrounds.paralax]
name = "Paralax"
path = "assets/background/purple_sky.jpeg"
x = 0
y = 0
allow_as_level_background = true

[backgrounds.space]
name = "Space"
path = "assets/background/dark_blue_stars.jpeg"
x = 0
y = 0
allow_as_level_background = true

# The spritesheets
[spritesheets]

# Default structure
# [spritesheet.<spritesheet_name>] # the name of the spritesheet to load (unique identifier)
# name = "<name of the sprite>" # set the name of the sprite  (a human readable name)
# path = "<valid path to the image file>" # set the path to the file (supported format, gif, png [and other SFML Texture supported formats])
# sprite_width = <width> # (0 -> 1000) set the width of the sprite view field, in pixels
# sprite_height = <height> # (0-> 1000) set the height of the sprite view field, in pixels
# start_left = true # (or false) set the starting position of the sprite view field to start from the left (or not)
# start_top = true # (or false) set the starting position of the sprite view field to start from the top (or not)
# initial_frame = 0 # set the frame that will be used as the first one, here the number represents the index of the frame. (default value: 0)
# end_frame = -1 # (or the index of the frame) set the last frame to be taken from the spritesheet (-1 means all frames present), (default value: -1)
# frame_delay = 100 # (from 0 to 2147483647) delay between each frame in milliseconds (default value: 100)

# The spritesheets to manage

[spritesheets.sprite1_ship]
name = "r-typesheet1_ship"
path = "assets/img/r-typesheet1.gif"
sprite_width = 33
sprite_height = 18
start_left = true
start_top = true
initial_frame = 3 # ship facing right: 3 to 7, ship facing left: 8 to 12
end_frame = 12
frame_delay = 100 # delay between each frame in milliseconds

#The second line of sprites can't be cut because they are not in a matrix like layout

[spritesheets.sprite1_particles]
name = "r-typesheet1_particles"
path = "assets/img/r-typesheet1.gif"
sprite_width = 32
sprite_height = 19
start_left = true
start_top = true
initial_frame = 48 # particles: 48 to 64
end_frame = 64
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite1_small_explosions]
name = "r-typesheet1_small_explosions"
path = "assets/img/r-typesheet1.gif"
sprite_width = 19
sprite_height = 12
start_left = true
start_top = true
initial_frame = 208 # from 208 to 210 fire left, from 210 to 213, fire rigth
end_frame = 213 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

# the next line cannot be cut cleanly because they are not in a matrix-like agency
# the next line cannot be cut cleanly because they are not in a matrix-like agency


[spritesheets.sprite1_big_fire_line]
name = "r-typesheet1_big_fire_line"
path = "assets/img/r-typesheet1.gif"
sprite_width = 66
sprite_height = 17
start_left = true
start_top = true
initial_frame = 74 # from 74 to 75, to the rigth, from 76 to 77 to the left
end_frame = 77 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

# The next line cannot be cut cleanly because they are not in a matrix-like agency
# The next line cannot be cut cleanly because they are not in a matrix-like agency
# The next line cannot be cut cleanly because they are not in a matrix-like agency

[spritesheets.sprite1_red_fireball]
name = "r-typesheet1_red_fireball"
path = "assets/img/r-typesheet1.gif"
sprite_width = 16
sprite_height = 12
start_left = true
start_top = false
initial_frame = 244
end_frame = 250
frame_delay = 100 # delay between each frame in milliseconds

# The next line cannot be cut cleanly because they are not in a matrix-like agency


[spritesheets.sprite1_round_blue_explosions]
name = "r-typesheet1_round_blue_explosions"
path = "assets/img/r-typesheet1.gif"
sprite_width = 33
sprite_height = 31
start_left = true
start_top = false
initial_frame = 0 # to the left: 0 to 8, to the right: 9 to 16
end_frame = 16 
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite1]
name = "r-typesheet1"
path = "assets/img/r-typesheet1.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite2]  # might get split in the future, complex spritesheet containing multiple sprites of different sizes
name = "r-typesheet2"
path = "assets/img/r-typesheet2.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite3]
name = "r-typesheet3"
path = "assets/img/r-typesheet3.gif"
sprite_width = 18
sprite_height = 18
start_left = true
start_top = true
initial_frame = 0 # mas: 11
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite5]
name = "r-typesheet5"
path = "assets/img/r-typesheet5.gif"
sprite_width = 32
sprite_height = 36
start_left = true
start_top = true
initial_frame = 0 # left: 0 to 7, right: 8 to 15
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite7]
name = "r-typesheet7"
path = "assets/img/r-typesheet7.gif"
sprite_width = 33
sprite_height = 34
start_left = true
start_top = true
initial_frame = 0 # looking left, no jets: 0 to 2, left right, no jets: 3 to 5, looking left, jets: 6 to 8, looking right, jets: 9 to 11
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite8]
name = "r-typesheet8"
path = "assets/img/r-typesheet8.gif"
sprite_width = 34
sprite_height = 34
start_left = true
start_top = true
initial_frame = 0 
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds
# looking forward:
# - east: 0
# - east (a bit tilted to the south) 1
# - east (a bit tilted to the east)  2
# - south-east: 3
# - south (a bit tilted to the east) 4
# - south: 5
# - south (a bit tilted to the west) 6
# - south-west: 7
# - west: 8
# - west (a bit tilted to the south) 9
# - north-west: 10
# - north (a bit tilted to the west) 11
# - north: 12
# - north (a bit tilted to the east) 13
# - north-east: 14

[spritesheets.sprite9] # spritesheet to uneven to parse in a matrix like manner
name = "r-typesheet9"
path = "assets/img/r-typesheet9.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds


[spritesheets.sprite10]
name = "r-typesheet10"
path = "assets/img/r-typesheet10.gif"
sprite_width = 33
sprite_height = 30
start_left = true
start_top = true
initial_frame = 0 # craft left: 0 to 5, craft right: 6 to 11, up: 14 to 16, standing left: 17, standing right: 18, up rigth: 19 to 21, missiles will not be cut properly, you would need to realine the spritesheet for that.
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite11]
name = "r-typesheet11"
path = "assets/img/r-typesheet11.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0 # left: 0 to 2, right: 3 to 5
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite12]
name = "r-typesheet12"
path = "assets/img/r-typesheet12.gif"
sprite_width = 17
sprite_height = 18
start_left = true
start_top = true
initial_frame = 0 # craft: up-left: 0 to 2, up-right: 3 to 5, down-left: 6 to 8, down-right: 9 to 11
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite13]
name = "r-typesheet13"
path = "assets/img/r-typesheet13.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0 # brown turret: 0 to 14, blue turrets: 15 to 29, bolder: 34 to 35
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite14]
name = "r-typesheet14"
path = "assets/img/r-typesheet14.gif"
sprite_width = 50
sprite_height = 50
start_left = true
start_top = true
initial_frame = 0 # 0 to 9
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite16]
name = "r-typesheet16"
path = "assets/img/r-typesheet16.gif"
sprite_width = 18
sprite_height = 11
start_left = true
start_top = true
initial_frame = 0 #calculate your own frames, this spritesheet need to be re-aligned to be properly cut.
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite17]
name = "r-typesheet17"
path = "assets/img/r-typesheet17.gif"
sprite_width = 65
sprite_height = 66
start_left = true
start_top = true
initial_frame = 0 # upwards: 0 to 7 , downwards: 8 to 15
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite18]
name = "r-typesheet18"
path = "assets/img/r-typesheet18.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0 # unhatched: 0 to 3, breaking: 7 to 4, entity: 8 to 11
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite19]
name = "r-typesheet19"
path = "assets/img/r-typesheet19.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0 # max: 13
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite19_ship_horizontal]
name = "r-typesheet19_ship_horizontal"
path = "assets/img/r-typesheet19.gif"
sprite_width = 29
sprite_height = 29
start_left = true
start_top = true
initial_frame = 20
end_frame = 21
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite19_bullet]
name = "r-typesheet19_bullet"
path = "assets/img/r-typesheet19.gif"
sprite_width = 10
sprite_height = 8
start_left = true
start_top = false
initial_frame = 11
end_frame = 11
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite20] # badly cut due to the sprite not being in a matrix like manner
name = "r-typesheet20"
path = "assets/img/r-typesheet20.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite21] # badly cut due to sprites not being in a matrix like manner
name = "r-typesheet21"
path = "assets/img/r-typesheet21.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite22]
name = "r-typesheet22"
path = "assets/img/r-typesheet22.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0 # max 15
end_frame = 15
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite23]
name = "r-typesheet23"
path = "assets/img/r-typesheet23.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0 # to the left, : 0 to 7, to the right 8 to 15
end_frame = 15
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite24]
name = "r-typesheet24"
path = "assets/img/r-typesheet24.gif"
sprite_width = 65
sprite_height = 65
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite25]
name = "r-typesheet25"
path = "assets/img/r-typesheet25.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0
end_frame = -1
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite26]
name = "r-typesheet26"
path = "assets/img/r-typesheet26.gif"
sprite_width = 65
sprite_height = 50
start_left = true
start_top = true
initial_frame = 0
end_frame = 5
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite27]
name = "r-typesheet27"
path = "assets/img/r-typesheet27.gif"
sprite_width = 34
sprite_height = 34
start_left = true
start_top = true
initial_frame = 0
end_frame = 1
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite28]
name = "r-typesheet28"
path = "assets/img/r-typesheet28.gif"
sprite_width = 130
sprite_height = 50
start_left = true
start_top = true
initial_frame = 0
end_frame = 0
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite29]
name = "r-typesheet29"
path = "assets/img/r-typesheet29.gif"
sprite_width = 33
sprite_height = 33
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite30] # Spritesheet not aligned, sprites will have missing pieces
name = "r-typesheet30"
path = "assets/img/r-typesheet30.gif"
sprite_width = 172
sprite_height = 209
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite30a]
name = "r-typesheet30a"
path = "assets/img/r-typesheet30a.gif"
sprite_width = 34
sprite_height = 34
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite31_vertical] # Horizontal sprites will be cut in 2 due to them not being aligned in a matrix like manner
name = "r-typesheet31_vertical"
path = "assets/img/r-typesheet31.gif"
sprite_width = 34
sprite_height = 34
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite31_red_stone]
name = "r-typesheet31_red_stone"
path = "assets/img/r-typesheet31.gif"
sprite_width = 11
sprite_height = 10
start_left = true
start_top = false
initial_frame = 12
end_frame = 15
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite32]
name = "r-typesheet32"
path = "assets/img/r-typesheet32.gif"
sprite_width = 260
sprite_height = 144
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite33]
name = "r-typesheet33"
path = "assets/img/r-typesheet33.gif"
sprite_width = 260
sprite_height = 142
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite34]
name = "r-typesheet34"
path = "assets/img/r-typesheet34.gif"
sprite_width = 260
sprite_height = 144
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite35]
name = "r-typesheet35"
path = "assets/img/r-typesheet35.gif"
sprite_width = 264
sprite_height = 143
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite36]
name = "r-typesheet36"
path = "assets/img/r-typesheet36.gif"
sprite_width = 264
sprite_height = 143
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_mothership_intact]
name = "r-typesheet37_mothership_intact"
path = "assets/img/r-typesheet37.gif"
sprite_width = 594
sprite_height = 191
start_left = true
start_top = true
initial_frame = 0
end_frame = 0
frame_delay = 100 # delay between each frame in milliseconds

#Second section of the spritesheet could not be parsed due to the sprites not being aligned in a matrix like manner

[spritesheets.sprite37_turret_firering]
name = "r-typesheet37_turret_firering"
path = "assets/img/r-typesheet37.gif"
sprite_width = 33
sprite_height = 32
start_left = true
start_top = true
initial_frame = 142 # from 142 to 149 and 159 to 166
end_frame = 166
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_gun]
name = "r-typesheet37_emp_gun"
path = "assets/img/r-typesheet37.gif"
sprite_width = 35
sprite_height = 32
start_left = true
start_top = true
initial_frame = 179
end_frame = 179
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_laser]
name = "r-typesheet37_emp_laser"
path = "assets/img/r-typesheet37.gif"
sprite_width = 37
sprite_height = 70
start_left = true
start_top = true
initial_frame = 87
end_frame = 91
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_gun_orientation]
name = "r-typesheet37_emp_gun_orientation"
path = "assets/img/r-typesheet37.gif"
sprite_width = 37
sprite_height = 32
start_left = true
start_top = true
initial_frame = 215
end_frame = 219
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_orientation] # Badly cut due to the sprites not being aligned in a matrix like manner
name = "r-typesheet37_emp_orientation"
path = "assets/img/r-typesheet37.gif"
sprite_width = 73
sprite_height = 64
start_left = true
start_top = true
initial_frame = 57
end_frame = 64
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_broken_emp_gun]
name = "r-typesheet37_broken_emp_gun"
path = "assets/img/r-typesheet37.gif"
sprite_width = 28
sprite_height = 26
start_left = true
start_top = true
initial_frame = 431
end_frame = 431
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_gun_explosion]
name = "r-typesheet37_emp_gun_explosion"
path = "assets/img/r-typesheet37.gif"
sprite_width = 31
sprite_height = 29
start_left = true
start_top = true
initial_frame = 371
end_frame = 371
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_gun_explosion2]
name = "r-typesheet37_emp_gun_explosion2"
path = "assets/img/r-typesheet37.gif"
sprite_width = 31
sprite_height = 29
start_left = true
start_top = true
initial_frame = 390
end_frame = 390
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_gun_explosion3]
name = "r-typesheet37_emp_gun_explosion3]"
path = "assets/img/r-typesheet37.gif"
sprite_width = 31
sprite_height = 29
start_left = true
start_top = true
initial_frame = 409
end_frame = 409
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_emp_gun_explosion4]
name = "r-typesheet37_emp_gun_explosion4]"
path = "assets/img/r-typesheet37.gif"
sprite_width = 31
sprite_height = 29
start_left = true
start_top = true
initial_frame = 428
end_frame = 428
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_big_gun]
name = "r-typesheet37_big_gun"
path = "assets/img/r-typesheet37.gif"
sprite_width = 92
sprite_height = 29
start_left = false
start_top = true
initial_frame = 145
end_frame = 145
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_initial_flame]
name = "r-typesheet37_initial_flame"
path = "assets/img/r-typesheet37.gif"
sprite_width = 65
sprite_height = 62
start_left = true
start_top = true
initial_frame = 106
end_frame = 106
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_mid_flame]
name = "r-typesheet37_mid_flame"
path = "assets/img/r-typesheet37.gif"
sprite_width = 127
sprite_height = 29
start_left = true
start_top = true
initial_frame = 97
end_frame = 98
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_end_flame]
name = "r-typesheet37_end_flame"
path = "assets/img/r-typesheet37.gif"
sprite_width = 31
sprite_height = 29
start_left = true
start_top = true
initial_frame = 458
end_frame = 461
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_small_projectile]
name = "r-typesheet37_small_projectile"
path = "assets/img/r-typesheet37.gif"
sprite_width = 18
sprite_height = 32
start_left = false
start_top = true
initial_frame = 808
end_frame = 811
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_top_turret]
name = "r-typesheet37_top_turret"
path = "assets/img/r-typesheet37.gif"
sprite_width = 35
sprite_height = 35
start_left = true
start_top = false
initial_frame = 328
end_frame = 337
frame_delay = 100 # delay between each frame in milliseconds

# small turrets skipped due to them not being aligned on an round pixel index they could thus not be properly cut

[spritesheets.sprite37_turret_flame]
name = "r-typesheet37_turret_flame"
path = "assets/img/r-typesheet37.gif"
sprite_width = 35
sprite_height = 36
start_left = true
start_top = true
initial_frame = 447 # row1: 447 to 455, row 2: 464 to 472, row3: 481 to 489, row4: 498 to 506
end_frame = 506
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_small_line_craft]
name = "r-typesheet37_small_line_craft"
path = "assets/img/r-typesheet37.gif"
sprite_width = 74
sprite_height = 36
start_left = true
start_top = true
initial_frame = 244 #row1: 244 to 245, row2: 252 to 253, row3: 260 to 261, row4: 268 to 269
end_frame = 269
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_blue_projectiles]
name = "r-typesheet37_blue_projectiles"
path = "assets/img/r-typesheet37.gif"
sprite_width = 14
sprite_height = 12
start_left = true
start_top = false
initial_frame = 1028
end_frame = 1031
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_ship_broken]
name = "r-typesheet37_ship_broken"
path = "assets/img/r-typesheet37.gif"
sprite_width = 591
sprite_height = 178
start_left = true
start_top = false
initial_frame = 0
end_frame = 0
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite37_nuclear_cloud] # Sprites will be a bit cut off due to bad alignement on the spritesheet
name = "r-typesheet37_nuclear_cloud"
path = "assets/img/r-typesheet37.gif"
sprite_width = 23
sprite_height = 39
start_left = true
start_top = false
initial_frame = 6 # mushroom downwards: 6 to 19, mushroom upwards: 32 to 45
end_frame = 45
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite38_parents]
name = "r-typesheet38_parents"
path = "assets/img/r-typesheet38.gif"
sprite_width = 186
sprite_height = 152
start_left = true
start_top = true
initial_frame = 0
end_frame = 1
frame_delay = 100 # delay between each frame in milliseconds

# The intermediate ships of the spritesheet could not be cut because they are not aligned on a square/rectangular grid in a matrix like manner

[spritesheets.sprite38_projectile]
name = "r-typesheet38_projectile"
path = "assets/img/r-typesheet38.gif"
sprite_width = 34
sprite_height = 30
start_left = true
start_top = false
initial_frame = 3
end_frame = 7
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite39] # The parent (split in 2, frame 2 and 3)
name = "r-typesheet39"
path = "assets/img/r-typesheet39.gif"
sprite_width = 33
sprite_height = 68
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite39_underlings] # There are only 4 frames of interest here
name = "r-typesheet39_underlings"
path = "assets/img/r-typesheet39.gif"
sprite_width = 33
sprite_height = 35
start_left = true
start_top = false
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite40_boss] #This is the first line of the spritesheet
name = "r-typesheet40_boss"
path = "assets/img/r-typesheet40.gif"
sprite_width = 66
sprite_height = 59
start_left = true
start_top = true
initial_frame = 0 # the range is 0 to 7
end_frame = 7
frame_delay = 100 # delay between each frame in milliseconds

# The underlings could not be processed because they were not in a matrix like array

[spritesheets.sprite40_platform]
name = "r-typesheet40_platform"
path = "assets/img/r-typesheet40.gif"
sprite_width = 66
sprite_height = 32
start_left = true
start_top = true
initial_frame = 34 # the range is 34 to 37
end_frame = 37
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite40_uob_entity] # uob (unidentified object)
name = "r-typesheet40_uob_entity"
path = "assets/img/r-typesheet40.gif"
sprite_width = 33
sprite_height = 32
start_left = true
start_top = true
initial_frame = 85 # the range is 85 to 88 and 101 to 104
end_frame = 104
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite40_terraform]
name = "r-typesheet40_terraform"
path = "assets/img/r-typesheet40.gif"
sprite_width = 48
sprite_height = 46
start_left = false
start_top = false
initial_frame = 5 # there is only one block
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite41] #spritesheet to uneven to parse in a matrix like manner
name = "r-typesheet41"
path = "assets/img/r-typesheet41.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
initial_frame = 0
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite42] # spaceships
name = "r-typesheet42"
path = "assets/img/r-typesheet42.gif"
sprite_width = 33
sprite_height = 17
start_left = true
start_top = true
initial_frame = 0 # cyan ship: 0 to 4, purple 5 to 9, green: 10 to 14, red: 15 to 19, dark blue: 20 to 24
end_frame = -1 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite43_fireball]
name = "r-typesheet43_fireball"
path = "assets/img/r-typesheet43.gif"
sprite_width = 17
sprite_height = 13
start_left = true
start_top = true
initial_frame = 8
end_frame = 15 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds


[spritesheets.sprite43_small_explosion]
name = "r-typesheet43_small_explosion"
path = "assets/img/r-typesheet43.gif"
sprite_width = 18
sprite_height = 16
start_left = true
start_top = true
initial_frame = 28
end_frame = 37
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite43_laser]
name = "r-typesheet43_laser"
path = "assets/img/r-typesheet43.gif"
sprite_width = 50
sprite_height = 5
start_left = true
start_top = true
initial_frame = 63
end_frame = 69
frame_delay = 100 # delay between each frame in milliseconds

# The last line of sprites from the spritesheet could not be rendered due to them not being aligned in a matrix like manner

[spritesheets.sprite44_small_explosion] # as the explosion is not correctly aligned, the sprites will be cut of in a more or less visible manner
name = "r-typesheet44_small_explosion"
path = "assets/img/r-typesheet44.gif"
sprite_width = 32
sprite_height = 32
start_left = true
start_top = true
initial_frame = 4
end_frame = 15
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite44_medium_explosion] # due to frame alignement, the white and black circles will be cropped as well as some small sections of the medium center sprites
name = "r-typesheet44_medium_explosion"
path = "assets/img/r-typesheet44.gif"
sprite_width = 65
sprite_height = 44
start_left = true
start_top = true
initial_frame = 10
end_frame = 20
frame_delay = 100 # delay between each frame in milliseconds

[spritesheets.sprite44_big_explosion] # due to sprite size, the sprites will be a bit cut off on the top and bottom
name = "r-typesheet44_big_explosion"
path = "assets/img/r-typesheet44.gif"
sprite_width = 65
sprite_height = 53
start_left = true
start_top = false
initial_frame = 0
end_frame = 10 #end of all the frames
frame_delay = 100 # delay between each frame in milliseconds
```

Let's break it down:

```toml
# The font
[font]

# Default structure
# [font.<font_name>] # the name of the font (unique identifier)
# name = "<name of the font>" # set the name of the font  (a human readable name)
# path = "<path to the font file>" # set the path to the file (supported format, ttf, otf [and other SFML Font supported formats])
# default_size = <size> # (0 -> 100) set the default size of the font to display, in pixels
# bold = false # (or true) set the font to bold
# italic = false # (or true) set the font to italic

# The music
[music]

# Default structure
# [music.<music_name>] # the name of the music (unique identifier)
# name = "<name of the music>" # set the name of the music  (a human readable name)
# path = "<valid path to the audio file>" # set the path to the file (supported format, ogg, wav [and other SFML Music supported formats])
# loop = true # (or false) # play the music on repeat
# volume = <volume> # (0 -> 100) set the volume of the track to play.

# The logo of the program
[icon]

# Default structure
# [icon] # the name of the logo (unique identifier)
# name = "Logo Name" # the name of the logo
# path = "<path to the logo>" # set the path to the logo image
# width = <width> # (0 -> 1000) set the width of the logo (Default: 256)
# height = <height> # (0 -> 1000) set the height of the logo (Default: 256)
# x = <x> # (0 -> 1000) set the x position of the logo (Default: 0)
# y = <y> # (0 -> 1000) set the y position of the logo (Default: 0)


# The background for the program
[backgrounds]

# Default structure
# [backgrounds.<background_name>] # the name of the background (unique identifier)
# name = "<name of the background>" # set the name of the background  (a human readable name)
# path = "<path to the background>" # set the path to the background image
# x = <x> # (0 -> 1000) set the x position of the background (Default: 0)
# y = <y> # (0 -> 1000) set the y position of the background (Default: 0)
# allow_as_level_background = true # (or false) allow the background to be used as a level background (Default: true)

# The spritesheets
[spritesheets]

# Default structure
# [spritesheet.<spritesheet_name>] # the name of the spritesheet to load (unique identifier)
# name = "<name of the sprite>" # set the name of the sprite  (a human readable name)
# path = "<valid path to the image file>" # set the path to the file (supported format, gif, png [and other SFML Texture supported formats])
# sprite_width = <width> # (0 -> 1000) set the width of the sprite view field, in pixels
# sprite_height = <height> # (0-> 1000) set the height of the sprite view field, in pixels
# start_left = true # (or false) set the starting position of the sprite view field to start from the left (or not)
# start_top = true # (or false) set the starting position of the sprite view field to start from the top (or not)
# initial_frame = 0 # set the frame that will be used as the first one, here the number represents the index of the frame. (default value: 0)
# end_frame = -1 # (or the index of the frame) set the last frame to be taken from the spritesheet (-1 means all frames present), (default value: -1)
# frame_delay = 100 # (from 0 to 2147483647) delay between each frame in milliseconds (default value: 100)
```

The `[font]`, `[music]`, `[icon]`, `[backgrounds]`, `[spritesheets]` represent the main sections of the configuration file:

* `[font]`: Font configuration
* `[music]`: Music configuration
* `[icon]`: Icon of the program
* `[backgrounds]`: background images used in the program
* `[spritesheets]`: Spritesheet configuration

The `[font]` block will contain the different fonts used for the different sections, i.e: the block `[font.title]` represents the design for text that is supposed to be a title.

The construction of a `[font]` block is the following:

* `[font.<font_name>]` : the name of the font (unique identifier)
* `name = "<name of the font>"` : set the name of the font  (a human readable name)
* `path = "<path to the font file>"` : set the path to the file (supported format, ttf, otf [and other SFML Font supported formats])
* `default_size = <size>` (`0` to `100`) : set the default size of the font to display, in pixels
* `bold = false` (or `true`) : set the font to bold
* `italic = false` (or `true`) : set the font to italic

The `[music]` block will contain the different musics and their names, they are meant to be referenced by name in the program so that the server can tell the client which music to play and when.

The construction of a `[music]` block is the following:

* `[music.<music_name>]` : the name of the music (unique identifier)
* `name = "<name of the music>"` : set the name of the music  (a human readable name)
* `path = "<valid path to the audio file>"` : set the path to the file (supported format, ogg, wav [and other SFML Music supported formats])
* `loop = true` (or `false`) : play the music on repeat
* `volume = <volume>` (`0` to `100`) : set the volume of the track to play

The `[icon]` block will contain the icon of the program so that it can be displayed during the program runtime.

> Note that it is the only block that does not contain any child ones, this is because there is only one icon for the program and thus there is no need to complexify this section.

The construction of the `[icon]` block is as following:

* [icon]: the section representing that the following content is an icon
* `name = "name of the icon"` : set the name of the icon, this will be used for debugging purposes.
* `path = "<valid path to the icon file>"` : set the path to the file
* `width = <width>` : set the initial width of the icon, in pixels
* `height = <height>` : set the initial height of the icon, in pixels
* `x = <x>` : set the initial x position of the icon, in pixels
* `y = <y>` : set the initial y position of the icon, in pixels

The `[backgrounds]` block will contain all the sprites that are available to the client, it is not recommended to remove any of the default ones that are already present.

The construction of a `[backgrounds]` block, element in charge of displaying the characters (images) on screen is the following:

* [backgrounds.<background_name>] : the name of the background to load (unique identifier)
* `name = "<name of the background>"` : set the name of the background  (a human readable name)
* `path = "<valid path to the image file>"` : set the path to the file (supported format, gif, png [and other SFML Texture supported formats])
* `width = <width>` (`0` to `1000`) : set the width of the background view field, in pixels
* `height = <height>` (`0` to `1000`) : set the height of the background view field, in pixels
* `x = <x>` (`0` to `2147483647`) : set the initial x position of the icon, in pixels
* `y = <y>` (`0` to `2147483647`) : set the initial y position of the icon, in pixels
* `allow_as_level_background = true` (or `false`) : allow the background to be used as a level background (Default: `true`)

The `[spritesheet]` block will contain all the sprites that are available to the client, it is not recommended to remove any of the default ones that are already present.

The construction of a `[spritesheet]` block, element in charge of displaying the characters (images) on screen is the following:

* [spritesheet.<spritesheet_name>] : the name of the spritesheet to load (unique identifier)
* `name = "<name of the sprite>"` : set the name of the sprite  (a human readable name)
* `path = "<valid path to the image file>"` : set the path to the file (supported format, gif, png [and other SFML Texture supported formats])
* `sprite_width = <width>` (`0` to `1000`) : set the width of the sprite view field, in pixels
* `sprite_height = <height>` (`0` to `1000`) : set the height of the sprite view field, in pixels
* `start_left = true` (or `false`) : set the starting position of the sprite view field to start from the left (or not)
* `start_top = true` (or `false`) : set the starting position of the sprite view field to start from the top (or not)
* `initial_frame = 0` : set the frame that will be used as the first one, here the number represents the index of the frame. (default value: `0`)
* `end_frame = -1` (or `<the index of the frame>`) : set the last frame to be taken from the spritesheet (`-1` means all frames present), (default value: `-1`)
* `frame_delay = 100` (from 0 to 2147483647) : set the delay between each frame in milliseconds (default value: 100)

## Troubleshooting

This section provides solutions for common issues you might encounter while compiling, running, or configuring the R-Type client.

### Common Issues

#### 1. Missing Dependencies

* **Symptom**: Errors during the `cmake` or `cmake --build` process indicating missing tools or libraries.

* **Solution**:
  * Ensure all dependencies listed in the [Getting Started - Dependencies - From Source](../getting_started/README.md#from-source) section are installed.
  * Verify that `CMake` and `G++` are installed and available in your system's `PATH`.

#### 2. CMake Configuration Fails

* **Symptom**: Errors during the `cmake -S . -B ./build` step, such as `cloning error` or missing components.

* **Solution**:
  * Check your internet connection; cloning errors often occur due to connectivity issues.
  * Verify the integrity of the source code and re-clone the repository if necessary.
  * Install any missing dependencies mentioned in the error logs.

#### 3. Build Errors

* **Symptom**: The `cmake --build ./build` command fails with errors about missing files or incorrect configurations.

* **Solution**:
  * Ensure the `build` folder is located in the `gui` directory.
  * Delete and recreate the `build` directory, then rerun the configuration and build commands.

#### 4. Runtime Errors

* **Symptom**: The client binary crashes or exits with errors when executed.

* **Solution**:
  * Run `./r-type_client --help` to ensure the binary is functioning and the options are properly configured.
  * Verify the presence of the `client_config.toml` file in the same directory as the binary.
  * Ensure all asset paths in the `client_config.toml` file are correct.

#### 5. Graphics Issues

* **Symptom**: The client fails to display graphics properly or does not open a window.

* **Solution**:
  * Check the configuration file (`client_config.toml`) to ensure the paths for fonts, spritesheets, and music are correct.
  * Verify that your system supports OpenGL, as required by SFML.

#### 6. Missing or Corrupted Assets

* **Symptom**: Errors related to missing assets or configuration files during runtime.

* **Solution**:
  * Ensure all assets listed in the `client_config.toml` file are present in their respective directories.
  * Redownload the assets if they appear corrupted.

### Debugging Tips

* Use the `--debug` flag when running the client binary to get detailed log output.

* Verify the configuration file syntax, as an invalid `toml` file can cause runtime issues.
* Run the client binary with a minimal set of options to isolate the issue, e.g., `./r-type_client --config-file client_config.toml`.

### Getting Help

* Refer to the [Getting Started](../getting_started/README.md) guide for dependency setup and compilation instructions.

* Check the [GitHub Issues](https://github.com/Hanra-s-work/rtype/issues) page for previously reported problems.
* Provide detailed information when seeking assistance:
  * Operating system and environment details.
  * Steps to reproduce the issue.
  * Complete error messages or logs.
