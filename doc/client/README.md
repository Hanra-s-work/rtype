# R-Type Client

## Table of contents

1. [Introduction](#introduction)
2. [Compiling](#compiling)
3. [Running the client](#running-the-client)
4. [Configuration file](#configuration-file)

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

# The spritesheets to manage

[spritesheets.sprite1]
name = "r-typesheet1"
path = "assets/img/r-typesheet1.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite2]
name = "r-typesheet2"
path = "assets/img/r-typesheet2.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite3]
name = "r-typesheet3"
path = "assets/img/r-typesheet3.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite5]
name = "r-typesheet5"
path = "assets/img/r-typesheet5.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite7]
name = "r-typesheet7"
path = "assets/img/r-typesheet7.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite8]
name = "r-typesheet8"
path = "assets/img/r-typesheet8.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite9]
name = "r-typesheet9"
path = "assets/img/r-typesheet9.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite10]
name = "r-typesheet10"
path = "assets/img/r-typesheet10.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite11]
name = "r-typesheet11"
path = "assets/img/r-typesheet11.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite12]
name = "r-typesheet12"
path = "assets/img/r-typesheet12.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite13]
name = "r-typesheet13"
path = "assets/img/r-typesheet13.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite14]
name = "r-typesheet14"
path = "assets/img/r-typesheet14.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite16]
name = "r-typesheet16"
path = "assets/img/r-typesheet16.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite17]
name = "r-typesheet17"
path = "assets/img/r-typesheet17.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite18]
name = "r-typesheet18"
path = "assets/img/r-typesheet18.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite19]
name = "r-typesheet19"
path = "assets/img/r-typesheet19.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite20]
name = "r-typesheet20"
path = "assets/img/r-typesheet20.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite21]
name = "r-typesheet21"
path = "assets/img/r-typesheet21.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite22]
name = "r-typesheet22"
path = "assets/img/r-typesheet22.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite23]
name = "r-typesheet23"
path = "assets/img/r-typesheet23.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite24]
name = "r-typesheet24"
path = "assets/img/r-typesheet24.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite25]
name = "r-typesheet25"
path = "assets/img/r-typesheet25.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite26]
name = "r-typesheet26"
path = "assets/img/r-typesheet26.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite27]
name = "r-typesheet27"
path = "assets/img/r-typesheet27.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite28]
name = "r-typesheet28"
path = "assets/img/r-typesheet28.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite29]
name = "r-typesheet29"
path = "assets/img/r-typesheet29.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite30]
name = "r-typesheet30"
path = "assets/img/r-typesheet30.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite30a]
name = "r-typesheet30a"
path = "assets/img/r-typesheet30a.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite31]
name = "r-typesheet31"
path = "assets/img/r-typesheet31.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite32]
name = "r-typesheet32"
path = "assets/img/r-typesheet32.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite33]
name = "r-typesheet33"
path = "assets/img/r-typesheet33.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite34]
name = "r-typesheet34"
path = "assets/img/r-typesheet34.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite35]
name = "r-typesheet35"
path = "assets/img/r-typesheet35.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite36]
name = "r-typesheet36"
path = "assets/img/r-typesheet36.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite37]
name = "r-typesheet37"
path = "assets/img/r-typesheet37.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite38]
name = "r-typesheet38"
path = "assets/img/r-typesheet38.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite39]
name = "r-typesheet39"
path = "assets/img/r-typesheet39.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite40]
name = "r-typesheet40"
path = "assets/img/r-typesheet40.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite41]
name = "r-typesheet41"
path = "assets/img/r-typesheet41.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite42]
name = "r-typesheet42"
path = "assets/img/r-typesheet42.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite43]
name = "r-typesheet43"
path = "assets/img/r-typesheet43.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true

[spritesheets.sprite44]
name = "r-typesheet44"
path = "assets/img/r-typesheet44.gif"
sprite_width = 20
sprite_height = 20
start_left = true
start_top = true
```

Let's break it down:
