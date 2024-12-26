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

1. Create a folder `build` to contain the

## Running the programs

## Troubleshooting
