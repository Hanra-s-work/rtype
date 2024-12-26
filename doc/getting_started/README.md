# Getting started

## Table of content

* [Dependencies](#dependencies)
  * [Pre-built](#pre-built)
  * [From source](#from-source)
* [Obtaining the source code](#obtaining-the-source-code)
* [Pre-compiled](#pre-compiled)
* [Deploy from source](#deploy-from-source)
* [Running the programs](#running-the-programs)
* [Troubleshooting](#troubleshooting)

## Dependencies

### Pre-built

If you wish to use the pre-built binaries, the only dependencies you need are:

> All these files can be found on the release page.

* The `assets` folder
* The `r-type_client` binary
* The `r-type_server` binary
* The client configuration `client_config.toml`
* The server configuration `server_config.toml`
* Some basic command line knowledge (potentially)

Once you have these elements, please head to the [Pre-compiled](#pre-compiled) section for more details on how to launch the project.

### From source

However, if you wish to compile the code from source, you will need the following:

> It is recommended to follow the [Obtaining the source code](#obtaining-the-source-code) section for an explanation on how to (obviously) obtain the source code so that you can compile the project.

> If you are on Linux or Mac, it might be simpler to obtain these dependencies via you system package manager (i.e. `apt`, `dnf`, `brew` (apple))

* [Cmake](https://cmake.org/download/)
* [Git](https://git-scm.com/downloads)
* [G++](https://gurucodes.dev/learn/introduction-to-programming/installation-gcc-compiler/)
* A copy of this [repository](https://github.com/Hanra-s-work/rtype)
* Some basic command line knowledge

Once you made sure you have these dependencies, please head to [Deploy from source](#deploy-from-source) section for more details on how to compile and run the project.

## Obtaining the source code

You can obtain the code in one of two ways:

Option 1 (preferred): Clone the repository using the following command:

 ```bash
 git clone https://github.com/Hanra-s-work/rtype rtype && cd rtype
 ```

Option 2: Download the repository as a zip file from the [GitHub repository page](https://github.com/Hanra-s-work/rtype)

Once you have obtained the zip folder, extract it to the directory of your choice.

Once you have extracted the folder to the directory of you choice, you should see a certain amount of folder and 3 files: `RUN_ME.sh`, `RUN_ME.bat`  and `RUN_ME.ps1`.

If this is not the case, please try downloading the zip folder again or chose the first method.

## Pre-compiled

Once you have downloaded the required ressources, please put them all in the same directory.

Once done, your folder should look like this:

```bash
.
├── r-type_client
├── r-type_server
├── client_config.toml
├── server_config.toml
└── assets
    ├── audio
    │   ├── 2019-12-11_-_Retro_Platforming_-_David_Fesliyan.ogg
    │   ├── 2021-08-30_-_Boss_Time_-_www.FesliyanStudios.com.ogg
    │   ├── Bomb-Explosion-Big-www.fesliyanstudios.com.ogg
    │   ├── FASTER-2020-03-22_-_A_Bit_Of_Hope_-_David_Fesliyan.ogg
    │   ├── Game-Menu-Selection-Z-www.fesliyanstudios.com.ogg
    │   ├── game-over-arcade.ogg
    │   ├── Laser-A1-www.fesliyanstudios.com.ogg
    │   ├── links.csv
    │   ├── success-fanfare-trumpets-6185.ogg
    │   ├── Undertale_Damage_Sound_Effect.ogg
    │   └── undertale_new.wav
    ├── font
    │   ├── Color Basic
    │   │   ├── Licenses
    │   │   │   └── Desktop EULA 1.7.txt
    │   │   └── TTF Fonts
    │   │       └── color_basic.ttf
    │   └── Joystix
    │       ├── Licenses
    │       │   └── Desktop Ebook EULA 1.7.txt
    │       └── TTF Fonts
    │           └── joystix_monospace.ttf
    └── img
        ├── r-typesheet10.gif
        ├── r-typesheet11.gif
        ├── r-typesheet12.gif
        ├── r-typesheet13.gif
        ├── r-typesheet14.gif
        ├── r-typesheet16.gif
        ├── r-typesheet17.gif
        ├── r-typesheet18.gif
        ├── r-typesheet19.gif
        ├── r-typesheet1.gif
        ├── r-typesheet20.gif
        ├── r-typesheet21.gif
        ├── r-typesheet22.gif
        ├── r-typesheet23.gif
        ├── r-typesheet24.gif
        ├── r-typesheet25.gif
        ├── r-typesheet26.gif
        ├── r-typesheet27.gif
        ├── r-typesheet28.gif
        ├── r-typesheet29.gif
        ├── r-typesheet2.gif
        ├── r-typesheet30a.gif
        ├── r-typesheet30.gif
        ├── r-typesheet31.gif
        ├── r-typesheet32.gif
        ├── r-typesheet33.gif
        ├── r-typesheet34.gif
        ├── r-typesheet35.gif
        ├── r-typesheet36.gif
        ├── r-typesheet37.gif
        ├── r-typesheet38.gif
        ├── r-typesheet39.gif
        ├── r-typesheet3.gif
        ├── r-typesheet40.gif
        ├── r-typesheet41.gif
        ├── r-typesheet42.gif
        ├── r-typesheet43.gif
        ├── r-typesheet44.gif
        ├── r-typesheet5.gif
        ├── r-typesheet7.gif
        ├── r-typesheet8.gif
        └── r-typesheet9.gif
```

> Note: Regarding the `font` folder, here, only the current fonts that are used by the program are shown, but there can be more fonts.

If this is not the case, please download the missing ressources before proceeding to [Running the programs](#running-the-programs) section.

## Deploy from source

This section assumes you have successfully completed in the [dependencies](#dependencies) section, the [from source](#from-source) category.

If you wish to only compile the client, please follow the [client - compiling](../client/README.md#compiling) section.

In order to compile the client program, you can either:

* run the `RUN_ME.sh` (if on linux or mac) or run the `RUN_ME.bat` or `RUN_ME.ps1` if on windows.
* run cmake at the root of the directory
* run cmake in the directory of the gui folder

If you wish to use the `RUN_ME` scripts, you will need to do the following actions:

* If you are on linux or mac:
  * Open a terminal at the root of the project
  * Enter `chmod +x RUN_ME.sh`
  * Enter `./RUN_ME.sh`
* If you are on Windows:
  * If you prefer to run the batch script (Recommended)
    * Open a terminal `cmd.exe` and navigate to the current directory `cd path\to\the\project`
    * Enter `RUN_ME.bat`
    * You should see the build process happen.
    * Another method is to double click on the file, this should open a window that will generate the necessary dependencies.
  * If you prefer Powershell:
    * Open a terminal `powershell.exe` and navigate to the current directory `cd path\to\the\project`
    * Enter `RUN_ME.ps1`

If you wish to compile the project at the root, please use the following steps:

Create a folder `build` to contain the configuration build.

While in the root of the project, run the command: `cmake -S . -B ./build` (or `cmake -S . -B build` for Windows).

This should provide the following output (or at least a similar one):

```cmake
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
-- Configuring done (40.1s)
-- Generating done (0.1s)
-- Build files have been written to: /home/<user_account>/path/to/the/project/rtype/build

```

If there were no errors, (no red text), while remaining in the root of the project, you can run the command: `cmake --build ./build` (or `cmake --build build`), this should output the following output (or at least something similar):

```cmake
[  1%] Building CXX object server/CMakeFiles/r-type_server.dir/src/GameManager.cpp.o
[  2%] Building CXX object server/CMakeFiles/r-type_server.dir/src/main.cpp.o
[  2%] Building CXX object server/CMakeFiles/r-type_server.dir/src/NetworkManager.cpp.o
[  3%] Building CXX object server/CMakeFiles/r-type_server.dir/src/ProtocolHandler.cpp.o
[  4%] Building CXX object server/CMakeFiles/r-type_server.dir/src/Server.cpp.o
[  4%] Building CXX object server/CMakeFiles/r-type_server.dir/src/ThreadPool.cpp.o
[  5%] Linking CXX executable /home/eletellier/Documents/001_github/Hanra-s-work/rtype/bin/r-type_server
[  5%] Built target r-type_server
[  6%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Clock.cpp.o
[  7%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Err.cpp.o
[  7%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Sleep.cpp.o
[  8%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/String.cpp.o
[  9%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Utils.cpp.o
[  9%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Vector2.cpp.o
[ 10%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Vector3.cpp.o
[ 11%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/FileInputStream.cpp.o
[ 11%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/MemoryInputStream.cpp.o
[ 12%] Building CXX object _deps/sfml-build/src/SFML/System/CMakeFiles/sfml-system.dir/Unix/SleepImpl.cpp.o
[ 13%] Linking CXX static library ../../../lib/libsfml-system.a
[ 13%] Built target sfml-system
[ 14%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/AudioResource.cpp.o
[ 14%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/AudioDevice.cpp.o
[ 15%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Listener.cpp.o
[ 16%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Miniaudio.cpp.o
[ 17%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/MiniaudioUtils.cpp.o
[ 17%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Music.cpp.o
[ 18%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/PlaybackDevice.cpp.o
[ 19%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/Sound.cpp.o
[ 19%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundBuffer.cpp.o
[ 20%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundBufferRecorder.cpp.o
[ 21%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/InputSoundFile.cpp.o
[ 21%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/OutputSoundFile.cpp.o
[ 22%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundRecorder.cpp.o
[ 23%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundSource.cpp.o
[ 24%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundStream.cpp.o
[ 24%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileFactory.cpp.o
[ 25%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderFlac.cpp.o
[ 26%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderMp3.cpp.o
[ 26%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderOgg.cpp.o
[ 27%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileReaderWav.cpp.o
[ 28%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileWriterFlac.cpp.o
[ 28%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileWriterOgg.cpp.o
[ 29%] Building CXX object _deps/sfml-build/src/SFML/Audio/CMakeFiles/sfml-audio.dir/SoundFileWriterWav.cpp.o
[ 30%] Linking CXX static library ../../../lib/libsfml-audio.a
[ 30%] Built target sfml-audio
[ 31%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Clipboard.cpp.o
[ 31%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Context.cpp.o
[ 32%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Cursor.cpp.o
[ 33%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/GlContext.cpp.o
[ 33%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/GlResource.cpp.o
[ 34%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Joystick.cpp.o
[ 35%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/JoystickManager.cpp.o
[ 35%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Keyboard.cpp.o
[ 36%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Mouse.cpp.o
[ 37%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Touch.cpp.o
[ 38%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Sensor.cpp.o
[ 38%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/SensorManager.cpp.o
[ 39%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/VideoMode.cpp.o
[ 40%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Vulkan.cpp.o
[ 40%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Window.cpp.o
[ 41%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/WindowBase.cpp.o
[ 42%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/WindowImpl.cpp.o
[ 42%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/CursorImpl.cpp.o
[ 43%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/ClipboardImpl.cpp.o
[ 44%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/InputImpl.cpp.o
[ 45%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/KeyboardImpl.cpp.o
[ 45%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/KeySymToKeyMapping.cpp.o
[ 46%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/KeySymToUnicodeMapping.cpp.o
[ 47%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/SensorImpl.cpp.o
[ 47%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/Display.cpp.o
[ 48%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/VideoModeImpl.cpp.o
[ 49%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/VulkanImplX11.cpp.o
[ 49%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/WindowImplX11.cpp.o
[ 50%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/GlxContext.cpp.o
[ 51%] Building CXX object _deps/sfml-build/src/SFML/Window/CMakeFiles/sfml-window.dir/Unix/JoystickImpl.cpp.o
[ 52%] Linking CXX static library ../../../lib/libsfml-window.a
[ 52%] Built target sfml-window
[ 53%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.o
[ 54%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.o
[ 55%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.o
[ 55%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.o
[ 56%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.o
[ 57%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.o
[ 57%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.o
[ 58%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.o
[ 59%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.o
[ 59%] Building CXX object _deps/sfml-build/src/SFML/Network/CMakeFiles/sfml-network.dir/Unix/SocketImpl.cpp.o
[ 60%] Linking CXX static library ../../../lib/libsfml-network.a
[ 60%] Built target sfml-network
[ 61%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/BlendMode.cpp.o
[ 61%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Font.cpp.o
[ 62%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Glsl.cpp.o
[ 63%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/GLCheck.cpp.o
[ 63%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/GLExtensions.cpp.o
[ 64%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Image.cpp.o
[ 65%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderStates.cpp.o
[ 65%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTexture.cpp.o
[ 66%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTarget.cpp.o
[ 67%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderWindow.cpp.o
[ 68%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Shader.cpp.o
[ 68%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/StencilMode.cpp.o
[ 69%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Texture.cpp.o
[ 70%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/TextureSaver.cpp.o
[ 70%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Transform.cpp.o
[ 71%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Transformable.cpp.o
[ 72%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/View.cpp.o
[ 72%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Shape.cpp.o
[ 73%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/CircleShape.cpp.o
[ 74%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RectangleShape.cpp.o
[ 75%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/ConvexShape.cpp.o
[ 75%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Sprite.cpp.o
[ 76%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/Text.cpp.o
[ 77%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/VertexArray.cpp.o
[ 77%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/VertexBuffer.cpp.o
[ 78%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTextureImplFBO.cpp.o
[ 79%] Building CXX object _deps/sfml-build/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/RenderTextureImplDefault.cpp.o
[ 79%] Linking CXX static library ../../../lib/libsfml-graphics.a
[ 79%] Built target sfml-graphics
[ 80%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/Main.cpp.o
[ 81%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/Debug.cpp.o
[ 81%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/RealMain.cpp.o
[ 82%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/MainClass.cpp.o
[ 83%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/TOMLLoader.cpp.o
[ 83%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/HelpFunctions.cpp.o
[ 84%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/ExceptionHandling.cpp.o
[ 85%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/Network/NetworkManager.cpp.o
[ 85%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/Network/ProtocolHandler.cpp.o
[ 86%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Component.cpp.o
[ 87%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/EntityNode.cpp.o
[ 88%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/TextComponent.cpp.o
[ 88%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/MusicComponent.cpp.o
[ 89%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/ShapeComponent.cpp.o
[ 90%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/SpriteComponent.cpp.o
[ 90%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/ButtonComponent.cpp.o
[ 91%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/TextureComponent.cpp.o
[ 92%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/CollisionComponent.cpp.o
[ 92%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Components/AnimationComponent.cpp.o
[ 93%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/InputSystem.cpp.o
[ 94%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/ButtonSystem.cpp.o
[ 95%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/RenderSystem.cpp.o
[ 95%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Systems/AnimationSystem.cpp.o
[ 96%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/key.cpp.o
[ 97%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/Font.cpp.o
[ 97%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/Clock.cpp.o
[ 98%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/Window.cpp.o
[ 99%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/MouseInfo.cpp.o
[ 99%] Building CXX object gui/CMakeFiles/r-type_client.dir/src/GUI/ECS/Utilities/EventManager.cpp.o
[100%] Linking CXX executable /home/<user_account>/pat/to/project/rtype/bin/r-type_client
[100%] Built target r-type_client
[100%] Built target copy_binaries
```

If you type `ls` (or `dir` for Windows) in your terminal you should now see 2 new files :

* `r-type_server` (the server executable)
* `r-type_client` (the client executable)

However, we are not done yet, it is necessary to copy the `client_config.toml` to the root of the project, `cp ./gui/client_config.toml .` (or `copy gui/client_config.toml .`)

We can now go to run the programs by going to the [Running the programs](#running-the-programs) section.

## Running the programs

This section assumes that you have either followed the [Pre-compiled](#pre-compiled) or [Deploy from source](#deploy-from-source) route.

One you have the client configuration file, it is recommended to take a look at the [client - Running the client](../client/README.md#running-the-client) section in order to learn how to start the client binary, if you wish to edit the configuration file, you can have a look at the [client - Configuration file](../client/README.md#configuration-file) section.

But what is a client without a server, you can thus follow the [server - running the server](../server/README.md#running-the-server) section in order to learn how to start the server binary, if you wish to edit the configuration file, you can have a look at the [server - Configuration file](../server/README.md#configuration-file) section.

## Troubleshooting
