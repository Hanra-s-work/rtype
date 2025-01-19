/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MainClass.cpp
*/

/**
 * @file MainClass.cpp
 *
 * @brief This is the file in charge of containing the class Main of the program.
 */

#include <cstdint>
#include <sstream>
#include <fstream>
#include "RealMain.hpp"

 /**
  * @brief Constructor for the Main class.
  *
  * @param ip The IP address to use for connections (default: "127.0.0.1").
  * @param port The port number to use for connections (default: 9000).
  * @param windowWidth The width of the application window (default: 800).
  * @param windowHeight The height of the application window (default: 600).
  * @param windowCursor Whether the cursor should be visible (default: true).
  * @param windowFullscreen Whether the window should start in fullscreen mode (default: false).
  * @param windowTitle The title of the window (default: "R-Type").
  * @param windowX The X position of the window (default: 0).
  * @param windowY The Y position of the window (default: 0).
  * @param windowCursorIcon Path to the cursor icon image (default: "NULL").
  * @param imageIsSprite Whether the cursor is rendered as a sprite (default: false).
  * @param spriteStartTop Whether the sprite rendering starts from the top (default: false).
  * @param spriteStartLeft Whether the sprite rendering starts from the left (default: false).
  * @param spriteWidth The width of the sprite (default: 20).
  * @param spriteHeight The height of the sprite (default: 20).
  * @param frameLimit The frame rate limit for the application (default: 60).
  * @param configFilePath Path to the configuration file (default: "client_config.toml").
  * @param log Inform the program if it needs to output logs or not (default: false).
  * @param debug Whether debug mode is enabled (default: false).
  * @param username The name of the user that is going to play (default: player)
  */
Main::Main(
    const std::string &ip,
    unsigned int port,
    unsigned int windowWidth,
    unsigned int windowHeight,
    bool windowCursor,
    bool windowFullscreen,
    const std::string &windowTitle,
    unsigned int windowX,
    unsigned int windowY,
    const std::string &windowCursorIcon,
    bool imageIsSprite,
    bool spriteStartTop,
    bool spriteStartLeft,
    unsigned int spriteWidth,
    unsigned int spriteHeight,
    unsigned int frameLimit,
    const std::string &configFilePath,
    const bool log,
    const bool debug,
    const std::string &player
) :
_windowWidth(windowWidth),
_windowHeight(windowHeight),
_windowCursor(windowCursor),
_windowFullscreen(windowFullscreen),
_windowTitle(windowTitle),
_windowX(windowX),
_windowY(windowY),
_imageIsSprite(imageIsSprite),
_spriteStartTop(spriteStartTop),
_spriteStartLeft(spriteStartLeft),
_spriteWidth(spriteWidth),
_configFilePath(configFilePath),
_spriteHeight(spriteHeight),
_networkManager(),
_player(player)
{
    _log = log;
    Logging::Log::getInstance().setLogEnabled(log);
    PRETTY_INFO << "Logging is enabled" << std::endl;
    _debug = debug;
    Logging::Log::getInstance().setDebugEnabled(debug);
    PRETTY_DEBUG << "The debug section of the log is enabled" << std::endl;
    PRETTY_INFO << "Processing ip" << std::endl;
    if (_isIpInRange(ip) == true) {
        _ip = ip;
    } else {
        throw CustomExceptions::InvalidIp(ip);
    }
    PRETTY_INFO << "Processing port" << std::endl;
    if (_isPortCorrect(port) == true) {
        _port = port;
    } else {
        throw CustomExceptions::InvalidPort(std::to_string(port));
    }
    PRETTY_INFO << "Processing cursor icon" << std::endl;
    std::string windowText = _lowerText(windowCursorIcon);
    if (windowText.empty() || windowText == "null" || windowText == "none") {
        _windowCursorIcon = "";
    } else if (_isFilePresent(windowCursorIcon) == true) {
        _windowCursorIcon = windowCursorIcon;
    } else {
        throw CustomExceptions::FileNotFound(windowCursorIcon);
    }
    PRETTY_INFO << "Processing frame limit" << std::endl;
    if (_isFrameLimitCorrect(frameLimit)) {
        _windowFrameLimit = frameLimit;
    } else {
        throw CustomExceptions::InvalidFrameLimit(frameLimit);
    }
    PRETTY_INFO << "Initialising the network manager" << std::endl;
    _networkManager = std::make_shared<GUI::Network::ThreadCapsule>(_baseId);
    _baseId += 1;
    PRETTY_INFO << "Setting the player name" << std::endl;
    _networkManager->setPlayerName(_player);
    PRETTY_INFO << "End of processing" << std::endl;
    // PRETTY_INFO << "Initialising the connection with the server" << std::endl;
    // _networkManager->setAddress(_ip, _port);
    // PRETTY_SUCCESS << "Connection with ther server initialised" << std::endl;
}

/**
 * @brief Destroy the Main:: Main object
 *
 */
Main::~Main() {}

/**
 * @brief Function in charge of converting a string of characters
 * to their lowercase version.
 *
 * @param text The string to process
 *
 * @return std::string A lowercased string.
 */
std::string Main::_lowerText(const std::string &text)
{
    std::string lowerText = text;
    if (lowerText.empty()) {
        return lowerText;
    }
    std::transform(
        lowerText.begin(),
        lowerText.end(),
        lowerText.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        }
    );
    return lowerText;
}

/**
 * @brief Checks if the ip provided is correct.
 *
 * @param ip
 *
 * @return true The ip is correct
 * @return false The ip is incorrect
 */
const bool Main::_isIpInRange(const std::string &ip) const
{
    std::istringstream iss(ip);
    std::string segment;
    int count = 0;

    while (std::getline(iss, segment, '.')) {
        if (count >= 4) {
            return false;
        }
        try {
            int octet = std::stoi(segment);
            if (octet < 0 || octet > 255) {
                return false;
            }
        }
        catch (...) {
            return false;
        }
        count++;
    }

    return count == 4;
}

/**
 * @brief Checks if the provided port is correct.
 *
 * @param port
 *
 * @return true The port is correct.
 * @return false The port is incorrect.
 */
const bool Main::_isPortCorrect(const unsigned int port) const
{
    return port >= 0 && port <= 65535;
}

/**
 * @brief Check if the provided file path is present and can be opened.
 *
 * @param filepath
 *
 * @return true The path is present
 * @return false The path is not present
 */
const bool Main::_isFilePresent(const std::string &filepath) const
{
    return std::ifstream(filepath).good();
}

/**
 * @brief The function in charge of checking if the provided frame limit is correct.
 *
 * @param frameLimit
 *
 * @return true The frame limit is correct
 * @return false The frame limit is incorrect
 */
const bool Main::_isFrameLimitCorrect(const unsigned int frameLimit) const
{
    if (frameLimit < 10 || frameLimit > 1000) {
        return false;
    }
    return true;
}

/**
 * @brief Check if a font configuration is correct.
 *
 * @param node
 *
 * @return true The configuration is correct
 * @return false The configuration is incorrect
 */
const bool Main::_isFontConfigurationCorrect(const TOMLLoader &node) const
{
    if (
        !_isKeyPresentAndOfCorrectType(node, "name", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "path", toml::node_type::string)
        ) {
        return false;
    }

    return true;
}

/**
 * @brief A function to check that the Icon configuration is correct.
 *
 * @param node
 *
 * @return true The configuration is correct
 * @return false The configuration is incorrect
 */
const bool Main::_isIconConfigurationCorrect(const TOMLLoader &node) const
{
    if (
        !_isKeyPresentAndOfCorrectType(node, "name", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "path", toml::node_type::string)
        ) {
        return false;
    }
    return true;
}

/**
 * @brief Check if a music configuration is correct.
 *
 * @param node
 *
 * @return true The configuration is correct
 * @return false The configuration is incorrect
 */
const bool Main::_isMusicConfigurationCorrect(const TOMLLoader &node) const
{
    if (
        !_isKeyPresentAndOfCorrectType(node, "name", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "path", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "loop", toml::node_type::boolean) ||
        !_isKeyPresentAndOfCorrectType(node, "volume", toml::node_type::integer)
        ) {
        return false;
    }
    return true;
}

/**
 * @brief Check if a sprite configuration is correct.
 *
 * @param node
 *
 * @return true The configuration is correct
 * @return false The configuration is incorrect
 */
const bool Main::_isSpriteConfigurationCorrect(const TOMLLoader &node) const
{
    if (
        !_isKeyPresentAndOfCorrectType(node, "name", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "path", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "sprite_width", toml::node_type::integer) ||
        !_isKeyPresentAndOfCorrectType(node, "sprite_height", toml::node_type::integer) ||
        !_isKeyPresentAndOfCorrectType(node, "start_left", toml::node_type::boolean) ||
        !_isKeyPresentAndOfCorrectType(node, "start_top", toml::node_type::boolean)
        ) {
        return false;
    }
    return true;
}

/**
 * @brief Check if a background image configuration is correct.
 *
 * @param node
 *
 * @return true The configuration is correct
 * @return false The configuration is incorrect
 */
const bool Main::_isBackgroundConfigurationCorrect(const TOMLLoader &node) const
{
    if (
        !_isKeyPresentAndOfCorrectType(node, "name", toml::node_type::string) ||
        !_isKeyPresentAndOfCorrectType(node, "path", toml::node_type::string)
        ) {
        return false;
    }
    return true;
}

/**
 * @brief This is a generic function that will check if a given key is present and that the type of the value is correct.
 *
 * @param node
 * @param key
 * @param valueType
 *
 * @return true
 * @return false
 */
const bool Main::_isKeyPresentAndOfCorrectType(const TOMLLoader &node, const std::string &key, const toml::node_type &valueType) const
{
    if (!node.hasKey(key)) {
        return false;
    }
    if (node.getValueType(key) != valueType) {
        return false;
    }
    return true;
}

/**
 * @brief The function in charge of initialising the connection to the server.
 *
 * @return int
 */
void Main::_initialiseConnection()
{
    std::string address = _ip + ":" + std::to_string(_port);
    PRETTY_DEBUG << "Connecting to the server at " << address << std::endl;
    _networkManager->setAddress(_ip, _port);
    _networkManager->startGame();
    // if (_networkManager->isConnected()) {
    //     PRETTY_SUCCESS << "We are connected to the server" << std::endl;
    // } else {
    //     PRETTY_WARNING << "We are not connected to the server" << std::endl;
    // }
}

/**
 * @brief Close the connection with the server.
 *
 */
void Main::_closeConnection()
{
    _networkManager->stopThread();
}

/**
 * @brief This is the function in charge of loading the ²s into the program.
 *
 * @return std::uint32_t
 */
std::uint32_t Main::_initialiseAudio()
{
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string musicKey = "music";
    const std::string musicKeyAlt = "musics";
    std::vector<std::string> audios;
    std::unordered_map<std::string, TOMLLoader> loadedAudios;

    const TOMLLoader audio = _getTOMLNodeContent<CustomExceptions::InvalidConfigurationMusicType, CustomExceptions::NoMusicInConfigFile>(_tomlContent, musicKey, musicKeyAlt);

    TOMLLoader tempNode(audio);

    audios.push_back("mainMenu");
    audios.push_back("bossFight");
    audios.push_back("gameLoop");
    audios.push_back("shooting");
    audios.push_back("damage");
    audios.push_back("dead");
    audios.push_back("button");
    audios.push_back("gameOver");
    audios.push_back("success");

    const std::string &expectedStringType = _tomlContent.getTypeAsString(toml::node_type::table);

    PRETTY_INFO << "Getting the music configuration chunks" << std::endl;

    for (std::string &iterator : audios) {
        _updateLoadingText("Processing music '" + iterator + "'...");
        if (!audio.hasKey(iterator)) {
            throw CustomExceptions::NoTOMLKey(tomlPath, iterator);
        }
        loadedAudios[iterator] = tempNode;
        if (audio.getValueType(iterator) != toml::node_type::table) {
            throw CustomExceptions::InvalidTOMLKeyType(tomlPath, iterator, audio.getTypeAsString(iterator), expectedStringType);
        }
        loadedAudios[iterator].update(audio.getTable(iterator));
        if (!_isMusicConfigurationCorrect(loadedAudios[iterator])) {
            std::string userConfig = loadedAudios[iterator].getTOMLString();
            throw CustomExceptions::InvalidMusicConfiguration(userConfig, iterator);
        }
        _updateLoadingText("Processing music '" + iterator + "'...[OK]");
    }

    PRETTY_INFO << "Initialising the musics" << std::endl;

    for (std::unordered_map<std::string, TOMLLoader>::iterator it = loadedAudios.begin(); it != loadedAudios.end(); ++it) {
        std::string application = it->first;
        std::string name = it->second.getValue<std::string>("name");
        std::string path = it->second.getValue<std::string>("path");
        int volume = 100;
        bool loop = false;

        _updateLoadingText("Loading music '" + name + "'...");

        if (_isKeyPresentAndOfCorrectType(it->second, "volume", toml::node_type::integer)) {
            volume = it->second.getValue<int>("volume");
        }
        if (_isKeyPresentAndOfCorrectType(it->second, "loop", toml::node_type::boolean)) {
            loop = it->second.getValue<bool>("loop");
        }
        std::shared_ptr<GUI::ECS::Components::MusicComponent> node = std::make_shared<GUI::ECS::Components::MusicComponent>(_baseId, path, name, application, volume, loop);
        _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)].push_back(node);
        _baseId++;
        _updateLoadingText("Loading music '" + name + "'...[OK]");
    }

    PRETTY_SUCCESS << "The musics are loaded." << std::endl;
    PRETTY_INFO << "Value of the base id: " << std::to_string(_baseId) << std::endl;
    return _baseId;
}

/**
 *@brief This function is in charge of loading the fonts into the program.
 *
* @return std::uint32_t
*/
std::uint32_t Main::_initialiseFonts()
{
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string fontKey = "font";
    const std::string fontKeyAlt = "fonts";
    const TOMLLoader font = _getTOMLNodeContent<CustomExceptions::InvalidConfigurationFontType, CustomExceptions::NoFontInConfigFile>(_tomlContent, fontKey, fontKeyAlt);
    std::unordered_map<std::string, TOMLLoader> loadedFonts;

    const std::string titleFontNode = "title";
    const std::string bodyFontNode = "body";
    const std::string defaultFontNode = "default";
    const std::string buttonFontNode = "button";

    if (!font.hasKey(titleFontNode)) {
        throw CustomExceptions::NoTitleFontConfiguration(tomlPath);
    }
    if (!font.hasKey(bodyFontNode)) {
        throw CustomExceptions::NoBodyFontConfiguration(tomlPath);
    }
    if (!font.hasKey(defaultFontNode)) {
        throw CustomExceptions::NoDefaultFontConfiguration(tomlPath);
    }
    if (!font.hasKey(buttonFontNode)) {
        throw CustomExceptions::NoButtonFontConfiguration(tomlPath);
    }

    TOMLLoader tempNode(font);

    loadedFonts["title"] = tempNode;
    loadedFonts["body"] = tempNode;
    loadedFonts["default"] = tempNode;
    loadedFonts["button"] = tempNode;


    loadedFonts["body"].update(font.getTable(titleFontNode));
    loadedFonts["title"].update(font.getTable(bodyFontNode));
    loadedFonts["default"].update(font.getTable(defaultFontNode));
    loadedFonts["button"].update(font.getTable(buttonFontNode));

    if (!_isFontConfigurationCorrect(loadedFonts["title"])) {
        const std::string userConfig = loadedFonts["title"].getTOMLString();
        const std::string fontName = titleFontNode;
        throw CustomExceptions::InvalidFontConfiguration(userConfig, fontName);
    }
    if (!_isFontConfigurationCorrect(loadedFonts["body"])) {
        const std::string userConfig = loadedFonts["body"].getTOMLString();
        const std::string fontName = bodyFontNode;
        throw CustomExceptions::InvalidFontConfiguration(userConfig, fontName);
    }
    if (!_isFontConfigurationCorrect(loadedFonts["default"])) {
        const std::string userConfig = loadedFonts["default"].getTOMLString();
        const std::string fontName = defaultFontNode;
        throw CustomExceptions::InvalidFontConfiguration(userConfig, fontName);
    }
    if (!_isFontConfigurationCorrect(loadedFonts["button"])) {
        const std::string userConfig = loadedFonts["button"].getTOMLString();
        const std::string fontName = buttonFontNode;
        throw CustomExceptions::InvalidFontConfiguration(userConfig, fontName);
    }


    for (std::unordered_map<std::string, TOMLLoader>::iterator it = loadedFonts.begin(); it != loadedFonts.end(); ++it) {
        std::string application = it->first;
        PRETTY_INFO << "Font application = '" + application + "'" << std::endl;
        std::string name = it->second.getValue<std::string>("name");
        std::string path = it->second.getValue<std::string>("path");
        int defaultSize = 50;
        bool bold = false;
        bool italic = false;

        if (_isKeyPresentAndOfCorrectType(it->second, "default_size", toml::node_type::integer)) {
            defaultSize = it->second.getValue<int>("default_size");
        }
        if (_isKeyPresentAndOfCorrectType(it->second, "bold", toml::node_type::boolean)) {
            bold = it->second.getValue<bool>("bold");
        }
        if (_isKeyPresentAndOfCorrectType(it->second, "italic", toml::node_type::boolean)) {
            italic = it->second.getValue<bool>("italic");
        }
        PRETTY_DEBUG << "Loading font '" << application << "' ... [LOADING]" << std::endl;
        std::shared_ptr<GUI::ECS::Systems::Font> node = std::make_shared<GUI::ECS::Systems::Font>(_baseId, name, path, defaultSize, application, bold, italic);
        PRETTY_DEBUG << "Font '" << application << "' [LOADED]" << std::endl;
        PRETTY_DEBUG << "Storing in ecs entity" << std::endl;
        _ecsEntities[typeid(GUI::ECS::Systems::Font)].push_back(node);
        if (application == titleFontNode) {
            _titleFontIndex = _ecsEntities[typeid(GUI::ECS::Systems::Font)].size() - 1;
        }
        if (application == bodyFontNode) {
            _bodyFontIndex = _ecsEntities[typeid(GUI::ECS::Systems::Font)].size() - 1;
        }
        if (application == defaultFontNode) {
            _defaultFontIndex = _ecsEntities[typeid(GUI::ECS::Systems::Font)].size() - 1;
        }
        if (application == buttonFontNode) {
            _buttonFontIndex = _ecsEntities[typeid(GUI::ECS::Systems::Font)].size() - 1;
        }
        PRETTY_DEBUG << "Stored in ecs entity" << std::endl;
        _baseId++;
    }
    PRETTY_INFO << "Value of the base id: " << std::to_string(_baseId) << std::endl;
    return _baseId;
}


std::uint32_t Main::_initialiseIcon()
{
    const std::string iconKey = "icon";
    const std::string iconKeyAlt = "icons";
    const TOMLLoader sprites = _getTOMLNodeContent<CustomExceptions::InvalidIconConfiguration, CustomExceptions::NoIconInConfigFile>(_tomlContent, iconKey, iconKeyAlt);
    std::unordered_map<std::string, TOMLLoader> loadedSprites;

    PRETTY_INFO << "Getting the icon configuration chunks" << std::endl;

    if (!_isIconConfigurationCorrect(sprites)) {
        std::string iconName = "";
        if (_isKeyPresentAndOfCorrectType(sprites, "name", toml::node_type::string)) {
            iconName = sprites.getValue<std::string>("name");
        }
        throw CustomExceptions::InvalidIconConfiguration(sprites.getTOMLPath(), "", iconName, "");
    }

    _updateLoadingText("Getting icon information...");
    const std::string name = sprites.getValue<std::string>("name");
    const std::string path = sprites.getValue<std::string>("path");
    int width = 256;
    int height = 256;
    int x = 0;
    int y = 0;

    if (_isKeyPresentAndOfCorrectType(sprites, "width", toml::node_type::integer)) {
        const int tmpWidth = sprites.getValue<int>("width");
        if (tmpWidth > 0) {
            width = tmpWidth;
        }
    }
    if (_isKeyPresentAndOfCorrectType(sprites, "height", toml::node_type::integer)) {
        const int tmpHeight = sprites.getValue<int>("height");
        if (tmpHeight > 0) {
            height = tmpHeight;
        }
    }
    if (_isKeyPresentAndOfCorrectType(sprites, "x", toml::node_type::integer)) {
        const int tmpX = sprites.getValue<int>("x");
        if (tmpX > 0) {
            x = tmpX;
        }
    }
    if (_isKeyPresentAndOfCorrectType(sprites, "y", toml::node_type::integer)) {
        const int tmpY = sprites.getValue<int>("y");
        if (tmpY > 0) {
            y = tmpY;
        }
    }
    _updateLoadingText("Getting icon information...[OK]");
    _updateLoadingText("Loading icon...");
    std::shared_ptr<GUI::ECS::Components::ImageComponent> icon = std::make_shared<GUI::ECS::Components::ImageComponent>(_baseId, path, name);
    icon->setDimension({ width, height });
    icon->setPosition({ x,y });
    _baseId++;
    _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)].push_back(icon);
    _iconIndex = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)].size() - 1;
    _updateLoadingText("Loading icon...[OK]");

    return _baseId;
}

/**
 *@brief This is the function in charge of loading the Sprites and Spritesheets into the program.
 *
* @return std::uint32_t
*/
std::uint32_t Main::_initialiseSprites()
{
    const std::string spriteSheetKey = "spritesheets";
    const std::string spriteSheetKeyAlt = "spritesheet";
    const TOMLLoader sprites = _getTOMLNodeContent<CustomExceptions::InvalidConfigurationSpritesheetType, CustomExceptions::NoSpritesInConfigFile>(_tomlContent, spriteSheetKey, spriteSheetKeyAlt);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    std::unordered_map<std::string, TOMLLoader> loadedSprites;

    TOMLLoader tempNode(sprites);

    PRETTY_INFO << "Getting the sprite configuration chunks" << std::endl;

    unsigned int counter = 1;
    std::string data = "Processed Sprites: \n";
    const std::string &expectedStringType = _tomlContent.getTypeAsString(toml::node_type::table);

    for (std::string &it : sprites.getKeys()) {
        _updateLoadingText("Processing '" + it + "'...");
        data += "\t" + std::to_string(counter) + " : " + "'" + it + "'\n";
        PRETTY_INFO << "Processing sprite: '" << it << "'" << std::endl;
        if (!sprites.hasKey(it)) {
            throw CustomExceptions::NoTOMLKey(tomlPath, it);
        }
        loadedSprites[it] = tempNode;
        if (sprites.getValueType(it) != toml::node_type::table) {
            throw CustomExceptions::InvalidTOMLKeyType(tomlPath, it, sprites.getTypeAsString(it), expectedStringType);
        }
        loadedSprites[it].update(sprites.getTable(it));
        if (!_isSpriteConfigurationCorrect(loadedSprites[it])) {
            std::string userConfig = loadedSprites[it].getTOMLString();
            throw CustomExceptions::InvalidSpriteConfiguration(userConfig, it);
        }
        counter++;
        _updateLoadingText("Processing '" + it + "'...[OK]");
    };
    PRETTY_SUCCESS << data << std::endl;

    PRETTY_INFO << "Initialising the sprites" << std::endl;

    for (std::unordered_map<std::string, TOMLLoader>::iterator it = loadedSprites.begin(); it != loadedSprites.end(); ++it) {
        std::string application = it->first;
        std::string name = it->second.getValue<std::string>("name");
        std::string path = it->second.getValue<std::string>("path");
        int spriteWidth = it->second.getValue<int>("sprite_width");
        int spriteHeight = it->second.getValue<int>("sprite_height");
        bool startLeft = it->second.getValue<bool>("start_left");
        bool startTop = it->second.getValue<bool>("start_top");
        int initialFrame = 0;
        int endFrame = (-1);
        int frameDelay = 100;

        if (it->second.hasKey("initial_frame")) {
            initialFrame = it->second.getValue<int>("initial_frame");
        }
        if (it->second.hasKey("end_frame")) {
            endFrame = it->second.getValue<int>("end_frame");
        }
        if (it->second.hasKey("frame_delay")) {
            frameDelay = it->second.getValue<int>("frame_delay");
            if (frameDelay < 0) {
                std::string errMsg = "<A number between 0 and 2147483647 was expected, however, you entered: '";
                errMsg += Recoded::myToString(frameDelay);
                errMsg += "'>";
                throw CustomExceptions::InvalidSpriteConfiguration(it->second.getTOMLString(), name, errMsg);
            }
        }

        _updateLoadingText("Loading sprite '" + name + "'...");
        PRETTY_INFO << "Loading sprite '" << name << "' [LOADING]" << std::endl;


        PRETTY_INFO << "Processing Animation component, id: '" << Recoded::myToString(_baseId) << "'" << std::endl;
        PRETTY_INFO << "Passed parameters are: " <<
            "name='" << name << "', " <<
            "path='" << path << "', " <<
            "sprite_width=" << Recoded::myToString(spriteWidth) << ", " <<
            "sprite_height=" << Recoded::myToString(spriteHeight) << ", " <<
            "start_left=" << Recoded::myToString(startLeft) << ", " <<
            "start_top=" << Recoded::myToString(startTop) << ", " <<
            "initial_frame=" << Recoded::myToString(initialFrame) << ", " <<
            "end_frame=" << Recoded::myToString(endFrame) <<
            "frame_delay=" << Recoded::myToString(frameDelay) << std::endl;

        std::shared_ptr<GUI::ECS::Components::AnimationComponent> animationPointer = std::make_shared<GUI::ECS::Components::AnimationComponent>(_baseId, path, spriteWidth, spriteHeight, startLeft, startTop, initialFrame, endFrame);
        _ecsEntities[typeid(GUI::ECS::Components::AnimationComponent)].push_back(animationPointer);
        _baseId++;
        PRETTY_DEBUG << "Setting animation delay to : '" << Recoded::myToString(frameDelay) << "'" << std::endl;
        animationPointer->setDelay(frameDelay);
        PRETTY_INFO << "Animation component info: " << *animationPointer << std::endl;
        PRETTY_SUCCESS << "Animation component processed" << std::endl;
        PRETTY_INFO << "Creating sprite id '" << name << "', id: '" << Recoded::myToString(_baseId) << "'" << std::endl;
        PRETTY_DEBUG << "Setting animation, animation id: '" << Recoded::myToString(animationPointer->getEntityNodeId()) << "', sprite entity id: '" << _baseId << "'" << std::endl;
        std::shared_ptr<GUI::ECS::Components::SpriteComponent> spriteEntity = std::make_shared<GUI::ECS::Components::SpriteComponent>(_baseId, name, *animationPointer);
        PRETTY_SUCCESS << "Sprite entity added to sprite '" << name << "'" << std::endl;
        PRETTY_SUCCESS << "Sprite '" << name << "' loaded" << std::endl;
        spriteEntity->setApplication(application);
        PRETTY_INFO << "Storing " << name << " into the ecs" << std::endl;
        _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)].push_back(spriteEntity);
        PRETTY_SUCCESS << name << " stored into the ecs entity" << std::endl;
        _baseId++;

        PRETTY_SUCCESS << "Sprite '" << name << "' [LOADED]" << std::endl;
        _updateLoadingText("Loading sprite '" + name + "'...[OK]");

        PRETTY_INFO << "buffer line1 between two sprite loads" << std::endl;
        PRETTY_INFO << "buffer line2 between two sprite loads" << std::endl;
        PRETTY_INFO << "buffer line3 between two sprite loads" << std::endl;
        PRETTY_INFO << "buffer line4 between two sprite loads" << std::endl;
    }

    PRETTY_SUCCESS << "The sprites are loaded." << std::endl;
    PRETTY_INFO << "Value of the base id: " << std::to_string(_baseId) << std::endl;
    return _baseId;
}

/**
 * @brief This is the function in charge of initialising the different backgrounds used throughout the game
 *
 * @return std::uint32_t
 */
std::uint32_t Main::_initialiseBackgrounds()
{
    const std::string iconKey = "backgrounds";
    const std::string iconKeyAlt = "background";
    const std::string path = _tomlContent.getTOMLPath();
    const TOMLLoader backgrounds = _getTOMLNodeContent<CustomExceptions::InvalidBackgroundConfiguration, CustomExceptions::NoBackgroundInConfigFile>(_tomlContent, iconKey, iconKeyAlt);
    std::unordered_map<std::string, TOMLLoader> loadedBackgrounds;
    std::vector<std::string> systemBackgrounds;

    systemBackgrounds.push_back("mainMenu");
    systemBackgrounds.push_back("settings");
    systemBackgrounds.push_back("gameOver");
    systemBackgrounds.push_back("connectionFailed");

    PRETTY_INFO << "Getting the background configuration chunks" << std::endl;

    for (std::string &item : backgrounds.getKeys()) {
        std::string checkMsg = "Checking for the presence of '" + item + "' in the config file...";
        _updateLoadingText(checkMsg);
        if (std::find(systemBackgrounds.begin(), systemBackgrounds.end(), item) != systemBackgrounds.end() && !backgrounds.hasKey(item)) {
            PRETTY_CRITICAL << "No TOML key '" << item << "' in the file path '" << path << "'." << std::endl;
            throw CustomExceptions::NoBackgroundInConfigFile(path, item);
        }
        if (!_isKeyPresentAndOfCorrectType(backgrounds, item, toml::node_type::table)) {
            PRETTY_CRITICAL << "The key '" << item << "' is not a table in the file." << std::endl;
            throw CustomExceptions::InvalidBackgroundConfiguration(path, item);
        }
        loadedBackgrounds[item] = backgrounds.getTable(item);
        _updateLoadingText(checkMsg + "[OK]");
    }

    std::unordered_map<std::string, TOMLLoader>::iterator it;

    for (it = loadedBackgrounds.begin(); it != loadedBackgrounds.end(); it++) {
        PRETTY_INFO << "Loading background: " << it->first << std::endl;
        _updateLoadingText("Loading background '" + it->first + "'...");
        std::string name = it->second.getValue<std::string>("name");
        std::string path = it->second.getValue<std::string>("path");
        int x = 0;
        int y = 0;
        bool allowAsLevelBackground = false;
        if (_isKeyPresentAndOfCorrectType(it->second, "x", toml::node_type::integer)) {
            int tmpX = it->second.getValue<int>("x");
            if (tmpX < 0) {
                PRETTY_CRITICAL << "The value of 'x' for the background '" << name << "'." << std::endl;
                throw CustomExceptions::InvalidBackgroundConfiguration(path, name, "x", "<The x value must be a number greater or equal to 0>");
            }
            x = tmpX;
        }
        if (_isKeyPresentAndOfCorrectType(it->second, "y", toml::node_type::integer)) {
            int tmpY = it->second.getValue<int>("y");
            if (tmpY < 0) {
                PRETTY_CRITICAL << "The value of 'y' for the background '" << name << "'." << std::endl;
                throw CustomExceptions::InvalidBackgroundConfiguration(path, name, "y", "<The y value must be a number greater or equal to 0>");
            }
            y = tmpY;
        }
        if (_isKeyPresentAndOfCorrectType(it->second, "allow_as_level_background", toml::node_type::boolean)) {
            bool allowAsLevelBackground = it->second.getValue<bool>("allow_as_level_background");
        }
        std::shared_ptr<GUI::ECS::Components::ImageComponent> node = std::make_shared<GUI::ECS::Components::ImageComponent>(_baseId, path, name, it->first);
        _baseId++;
        node->setPosition({ x, y });
        node->setLevelBackgroundCompatible(allowAsLevelBackground);
        _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)].push_back(node);
        _updateLoadingText("Loading background '" + it->first + "'...[OK]");
        PRETTY_INFO << "buffer line1 between two background loads" << std::endl;
        PRETTY_INFO << "buffer line2 between two background loads" << std::endl;
        PRETTY_INFO << "buffer line3 between two background loads" << std::endl;
        PRETTY_INFO << "buffer line4 between two background loads" << std::endl;
    }

    return _baseId;
}

/**
 * @brief This is the function in charge of initialise the default ressources for the class.
 *
 */
void Main::_initialiseRessources()
{
    std::uint32_t _baseId = 0;
    _ecsEntities.clear();

    PRETTY_INFO << "========================== Displaying loaded toml data. ==========================" << std::endl;
    _tomlContent.printTOML();
    PRETTY_SUCCESS << "========================== Displayed loaded toml data.  ==========================" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::Window> window = std::make_shared<GUI::ECS::Systems::Window>(_baseId, _windowWidth, _windowHeight, _windowTitle);
    PRETTY_DEBUG << "Setting the window position to : " << std::pair<int, int>({ _windowX, _windowY }) << std::endl;
    window->setPosition({ _windowX, _windowY });
    _baseId++;
    std::shared_ptr<GUI::ECS::Systems::EventManager> event = std::make_shared<GUI::ECS::Systems::EventManager>(_baseId);
    _baseId++;

    window->setFullScreen(_windowFullscreen);
    window->setFramerateLimit(_windowFrameLimit);

    _ecsEntities[typeid(GUI::ECS::Systems::Window)].push_back(window);
    _ecsEntities[typeid(GUI::ECS::Systems::EventManager)].push_back(event);

    _mainWindowIndex = _ecsEntities[typeid(GUI::ECS::Systems::Window)].size() - 1;

    _mainEventIndex = _ecsEntities[typeid(GUI::ECS::Systems::EventManager)].size() - 1;

    _baseId = _initialiseFonts();

    if (_baseId == 0 || _ecsEntities[typeid(GUI::ECS::Systems::Font)].size() == 0) {
        PRETTY_CRITICAL << "There are no fonts that were loaded in the program, aborting." << std::endl;
        throw CustomExceptions::NoFont("<No fonts are loaded into the program>");
    }

    PRETTY_INFO << "Fetching loaded font for displaying a loading text on screen." << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> firstFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>, CustomExceptions::NoFont>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_defaultFontIndex], true);
    if (!firstFontCapsule.has_value()) {
        throw CustomExceptions::NoFont();
    }

    GUI::ECS::Systems::Font firstFont = *firstFontCapsule.value();
    std::shared_ptr<GUI::ECS::Components::TextComponent> loading = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, firstFont, "Loading...", 20, GUI::ECS::Systems::Colour::Aqua, GUI::ECS::Systems::Colour::Aquamarine, GUI::ECS::Systems::Colour::Chartreuse1);
    _baseId++;
    _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(loading);
    window->draw(*loading);
    window->display();
    _loadingIndex = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].size() - 1;


    std::shared_ptr<SoundLib> soundLib = std::make_shared<SoundLib>(_baseId, _ecsEntities);
    _ecsEntities[typeid(SoundLib)].push_back(soundLib);
    _baseId += 1;
    PRETTY_SUCCESS << "Sound library initialised" << std::endl;

    _baseId = _initialiseIcon();
    _baseId = _initialiseBackgrounds();
    _baseId = _initialiseSprites();
    _baseId = _initialiseAudio();
    PRETTY_INFO << "Final value of the base Id: " << std::to_string(_baseId) << std::endl;
}

void Main::_updateLoadingText(const std::string &detail)
{
    PRETTY_DEBUG << "Updating loading display" << std::endl;
    std::vector<std::any> windows = _ecsEntities[typeid(GUI::ECS::Systems::Window)];
    std::vector<std::any> eventManagers = _ecsEntities[typeid(GUI::ECS::Systems::EventManager)];
    std::vector<std::any> textComponents = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];

    if (_mainWindowIndex > windows.size()) {
        PRETTY_ERROR << "Index out of bounds." << std::endl;
        throw CustomExceptions::NoWindow("The window index you tried to access does not exist, the index was: " + Recoded::myToString(_mainWindowIndex));
    }
    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> windowCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(windows[_mainWindowIndex], true, "The type of the window is unknown, system error: ");
    if (!windowCapsule.has_value()) {
        PRETTY_CRITICAL << "There is no window to access" << std::endl;
        throw CustomExceptions::NoWindow("The window index you tried to access does not exist, the index was: " + Recoded::myToString(_mainWindowIndex));
    }
    std::shared_ptr<GUI::ECS::Systems::Window> window = windowCapsule.value();

    if (_mainEventIndex > eventManagers.size()) {
        PRETTY_ERROR << "Index out of bounds." << std::endl;
        throw CustomExceptions::NoEventManager("The event manager index you tried to access does not exist, the index was: " + Recoded::myToString(_mainEventIndex));
    }
    std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> eventManagerCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>, CustomExceptions::NoEventManager>(eventManagers[_mainEventIndex], true, "The type of the event manager is unknown, system error: ");
    if (!eventManagerCapsule.has_value()) {
        PRETTY_CRITICAL << "There is no event manager to access" << std::endl;
        throw CustomExceptions::NoEventManager("The event manager index you tried to access does not exist, the index was: " + Recoded::myToString(_mainEventIndex));
    }
    std::shared_ptr<GUI::ECS::Systems::EventManager> event = eventManagerCapsule.value();

    if (_loadingIndex > textComponents.size()) {
        PRETTY_ERROR << "Index out of bounds." << std::endl;
        throw CustomExceptions::NoText("The text component index you tried to access does not exist, the index was: " + Recoded::myToString(_loadingIndex));
    }
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>, CustomExceptions::NoText>(textComponents[_loadingIndex], true, "The type of the text component is unknown, system error: ");
    if (!textCapsule.has_value()) {
        PRETTY_CRITICAL << "There is no text to access" << std::endl;
        throw CustomExceptions::NoText("The text index you tried to access does not exist, the index was: " + Recoded::myToString(_loadingIndex));
    }
    std::shared_ptr<GUI::ECS::Components::TextComponent> text = textCapsule.value();

    if (!window->isOpen()) {
        throw CustomExceptions::NoWindow("There is no window to draw on!");
    }
    event->processEvents(*window);
    if (!window->isOpen()) {
        throw CustomExceptions::NoWindow("There is no window to draw on!");
    }

    text->update(event->getMouseInfo());
    text->setText(detail);
    window->clear();
    window->draw(*text);
    window->display();
    PRETTY_SUCCESS << "Loading text updated" << std::endl;
}

void Main::_updateMouseForAllRendererables(const GUI::ECS::Systems::MouseInfo &mouse)
{
    PRETTY_INFO << "Updating mouse information for renderable components." << std::endl;
    std::vector<std::any> sprites = _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)];
    std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];
    std::vector<std::any> shapes = _ecsEntities[typeid(GUI::ECS::Components::ShapeComponent)];
    std::vector<std::any> images = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];

    for (unsigned int index = 0; index < sprites.size(); index++) {
        PRETTY_INFO << "Processing index for sprite : " << std::to_string(index) << std::endl;
        try {
            std::shared_ptr<GUI::ECS::Components::SpriteComponent> sprite = std::any_cast<std::shared_ptr<GUI::ECS::Components::SpriteComponent>>(sprites[index]);
            sprite->update(mouse);
        }
        catch (std::bad_any_cast &e) {
            PRETTY_ERROR << "Error casting sprite component, system error: " + std::string(e.what()) << std::endl;
        }
    }
    for (unsigned int index = 0; index < texts.size(); index++) {
        PRETTY_INFO << "Processing index for text : " << std::to_string(index) << std::endl;
        try {
            std::shared_ptr<GUI::ECS::Components::TextComponent> text = std::any_cast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(texts[index]);
            text->update(mouse);
        }
        catch (std::bad_any_cast &e) {
            PRETTY_ERROR << "Error casting text component, system error: " + std::string(e.what()) << std::endl;
        }
    }
    for (unsigned int index = 0; index < buttons.size(); index++) {
        PRETTY_INFO << "Processing index for button : " << std::to_string(index) << std::endl;
        try {
            std::shared_ptr<GUI::ECS::Components::ButtonComponent> button = std::any_cast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttons[index]);
            button->update(mouse);
        }
        catch (std::bad_any_cast &e) {
            PRETTY_ERROR << "Error casting button component, system error: " + std::string(e.what()) << std::endl;
        }
    }
    for (unsigned int index = 0; index < shapes.size(); index++) {
        PRETTY_INFO << "Processing index for shape : " << std::to_string(index) << std::endl;
        try {
            std::shared_ptr<GUI::ECS::Components::ShapeComponent> shape = std::any_cast<std::shared_ptr<GUI::ECS::Components::ShapeComponent>>(shapes[index]);
            shape->update(mouse);
        }
        catch (std::bad_any_cast &e) {
            PRETTY_ERROR << "Error casting shape component, system error: " + std::string(e.what()) << std::endl;
        }
    }
    for (unsigned int index = 0; index < images.size(); index++) {
        PRETTY_INFO << "Processing index for image : " << std::to_string(index) << std::endl;
        try {
            std::shared_ptr<GUI::ECS::Components::ImageComponent> image = std::any_cast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(images[index]);
            image->update(mouse);
        }
        catch (std::bad_any_cast &e) {
            PRETTY_ERROR << "Error casting shape component, system error: " + std::string(e.what()) << std::endl;
        }
    }
    PRETTY_SUCCESS << "Updated mouse information for renderable components." << std::endl;
}

/**
 * @brief Function in charge of sending all the packets that are
 * located in the outgoing buffer
 *
 */
void Main::_sendAllPackets()
{
    PRETTY_DEBUG << "Sending any packets that have been buffered and not sent" << std::endl;
    // GUI::Network::MessageNode item;
    // item.id = 0;
    // item.info.assetId = 0;
    // item.info.coords = { 0,0 };
    // item.info.status = 0;
    // item.info.username = "user";
    // item.type = GUI::Network::MessageType::ERROR;
    // if (_networkManager->isConnected()){
    //     _networkManager->sendMessage(item);
    // }
};

/**
 * @brief Function in charge of processing (treating) all the packets that have
 * been received into actions that can be understood by the program.
 *
 */
void Main::_processIncommingPackets()
{
    PRETTY_DEBUG << "Getting the buffer from the incoming packets" << std::endl;
    _bufferPackets.clear();
    const bool connected = _networkManager->isConnected();
    PRETTY_DEBUG << "Connection status: " << Recoded::myToString(connected) << std::endl;
    if (connected) {
        _bufferPackets = _networkManager->getReceivedMessages();
        PRETTY_DEBUG << "Buffer packet size: " << Recoded::myToString(_bufferPackets.size()) << std::endl;
    }
    PRETTY_DEBUG << "Out of _processIncommingPackets" << std::endl;
}

/**
 * @brief Retrieves a chunk of an IP address based on the provided index.
 *
 * This function extracts a chunk from the IP address stored in the `_ip` member
 * variable by locating the dots (`"."`) as separators. The function returns the
 * chunk corresponding to the given `index`. If no dot is found or the chunk is
 * empty, the function returns the provided default value.
 *
 * The `index` parameter specifies the segment of the IP address to retrieve,
 * starting from `0` for the first segment (before the first dot). If the IP
 * address has fewer segments than the specified `index`, the content after the
 * last dot is returned. If no dots exist in the IP address, the entire string
 * is returned or the `defaultValue` is returned if the string is empty.
 *
 * @param index The index of the chunk to retrieve. A value of `0` returns the
 * first chunk, `1` returns the second, etc.
 * @param defaultValue The value to return if the chunk is empty or no dot is
 * found in the IP address.
 *
 * @return The chunk of the IP address at the specified index, or the
 * `defaultValue` if the chunk is empty, the index is out of bounds, or no dot
 *  is found.
 *
 * @note This function handles IP addresses with varying numbers of segments,
 * returning either the part of the string before a dot or the content after
 * the last dot. If no dots exist, the full string is considered a single chunk.
 */
const std::string Main::_getIpChunk(const unsigned int index, const std::string &defaultValue) const
{
    PRETTY_DEBUG << "In _getIpChunk" << std::endl;

    PRETTY_DEBUG << "Handling edge case when the _ip is empty" << std::endl;
    if (_ip.empty()) {
        PRETTY_DEBUG << "_ip is empty, returning defaultValue" << std::endl;
        return defaultValue;
    }

    std::string resp;
    size_t startPos = 0;
    size_t dotPos = 0;
    unsigned int currentIndex = 0;

    PRETTY_DEBUG << "Looping through the dots in the IP address." << std::endl;
    while (true) {
        PRETTY_DEBUG << "Finding the next dot" << std::endl;
        dotPos = _ip.find('.', startPos);
        if (dotPos == std::string::npos) {
            PRETTY_DEBUG << "No more dots found, returning the rest of the string" << std::endl;
            break;
        }

        if (currentIndex == index) {
            resp = _ip.substr(startPos, dotPos - startPos);
            PRETTY_DEBUG << "Found node at index " << index << ": " << resp << std::endl;
            return resp;
        }

        PRETTY_DEBUG << "Moving to the next segment after the current dot" << std::endl;
        startPos = dotPos + 1;
        ++currentIndex;
    }

    if (currentIndex == index) {
        PRETTY_DEBUG << "Returning the content after the last dot if any" << std::endl;
        PRETTY_DEBUG << "Getting the part after the last dot" << std::endl;
        resp = _ip.substr(startPos);
        PRETTY_DEBUG << "Found node at last index: " << resp << std::endl;
        if (resp.empty()) {
            PRETTY_DEBUG << "Returning the defaultValue because resp is empty" << std::endl;
            return defaultValue;
        }
        return resp;
    }

    PRETTY_DEBUG << "No dot was found or index was too large, returning the default value.\n"
        << "Content of defaultValue: " << defaultValue << std::endl;
    return defaultValue;
}

/**
 * @brief Retrieves a TextComponent based on the provided key.
 *
 * This function searches through a collection of `TextComponent` entities within the ECS (Entity Component System).
 * It attempts to find the `TextComponent` whose application matches the provided `textComponentKey`.
 * If a matching `TextComponent` is found, it returns it as a `shared_ptr`. If no match is found,
 * it returns an empty `std::optional` object (`std::nullopt`).
 *
 * @param textComponentKey The key used to identify the desired `TextComponent` based on its associated application.
 *
 * @return A `std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>>` containing the matching `TextComponent`
 *         if found, or `std::nullopt` if no matching component is found.
 *
 * @note This function iterates over all `TextComponent` entities and compares the `application` field of each one
 *       with the provided `textComponentKey`. If no match is found, it returns `std::nullopt`.
 */
const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> Main::_getTextComponent(const std::string &textComponentKey)
{
    const std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];

    PRETTY_DEBUG << "texts.size() = " << Recoded::myToString(texts.size()) << std::endl;

    for (std::any node : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> chunk = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(node, false);
        if (node.has_value()) {
            PRETTY_DEBUG << "node type: '" << node.type().name() << "'" << std::endl;
        }
        if (!chunk.has_value()) {
            PRETTY_DEBUG << "Text component is empty" << std::endl;
            continue;
        }
        if (chunk.value()->getApplication() == textComponentKey || chunk.value()->getName() == textComponentKey) {
            PRETTY_DEBUG << "Found node with key: " << chunk.value()->getApplication() << std::endl;
            return chunk;
        }
    }
    PRETTY_DEBUG << "No matching text component found" << std::endl;
    return std::nullopt;
}

/**
 * @brief Increments an IPv4 node value represented as a string.
 *
 * This function takes a string representing an IPv4 node (e.g., "0" to "255")
 * and increments it by 1. If the input is invalid, it defaults to "0".
 * If the input is "255", it wraps around to "0".
 *
 * @param v4Node The IPv4 node value as a string. Expected to be in the range "0" to "255".
 *
 * @return The incremented IPv4 node value as a string. Returns "0" for invalid
 * input or when the input is "255".
 *
 * @warning Logs a warning message if the input is not a valid number.
 *
 * @note Leading zeros in the input are accepted but ignored
 * (e.g., "000" is treated as "0").
 */
const std::string Main::_incrementIpV4Node(const std::string &v4Node)
{
    if (v4Node == "0" || v4Node == "000") {
        return "1";
    }
    try {
        const unsigned int v4int = std::max({ std::stoi(v4Node), 0 });
        if (v4int < 255) {
            return std::to_string(v4int + 1);
        } else {
            return "0";
        }
    }
    catch (std::invalid_argument &e) {
        PRETTY_WARNING << "The argument passed is not a number, you entered: '"
            << v4Node << "', stoi error: '" << std::string(e.what()) << "'"
            << ", defaulting to: '0'"
            << std::endl;
        return "0";
    }
}

/**
 * @brief Decrements an IPv4 node value represented as a string.
 *
 * This function takes a string representing an IPv4 node (e.g., "0" to "255")
 * and decrements it by 1. If the input is invalid, it defaults to "0".
 * If the input is "0", it wraps around to "255".
 *
 * @param v4Node The IPv4 node value as a string. Expected to be in the range "0" to "255".
 *
 * @return The decremented IPv4 node value as a string. Returns "0" for invalid input or
 * when the input is "0".
 *
 * @warning Logs a warning message if the input is not a valid number.
 *
 * @note Leading zeros in the input are accepted but ignored
 * (e.g., "000" is treated as "0").
 */
const std::string Main::_decrementIpV4Node(const std::string &v4Node)
{
    try {
        const unsigned int v4int = std::max({ std::stoi(v4Node), 0 });
        if (v4int > 0) {
            return std::to_string(v4int - 1);
        } else {
            return "255";
        }
    }
    catch (std::invalid_argument &e) {
        PRETTY_WARNING << "The argument passed is not a number, you entered: '"
            << v4Node << "', stoi error: '" << std::string(e.what()) << "'"
            << ", defaulting to: '0'"
            << std::endl;
        return "0";
    }
}

/**
 * @brief Increments a port counter value represented as a string.
 *
 * This function takes a string representing a port value (e.g., "0" to `_maximumPortRange`) and increments
 * it by 1. If the input is invalid, it defaults to "0". If the port value reaches `_maximumPortRange`,
 * it wraps around to "0".
 *
 * @param portSection The port value as a string. Expected to be a numeric value in the range "0" to `_maximumPortRange`.
 * @return The incremented port value as a string. Returns "0" for invalid input or when the port value equals `_maximumPortRange`.
 *
 * @warning Logs a warning message if the input is not a valid number.
 *
 * @note Leading zeros in the input are accepted but ignored (e.g., "000" is treated as "0").
 * @note The `_maximumPortRange` variable should be properly defined to set the upper limit of the port range.
 */
const std::string Main::_incrementPortCounter(const std::string &portSection)
{
    if (portSection == "0" || portSection == "000") {
        return "1";
    }
    try {
        const unsigned int port = std::max({ std::stoi(portSection), 0 });
        if (port < _maximumPortRange) {
            return std::to_string(port + 1);
        } else {
            return "0";
        }
    }
    catch (std::invalid_argument &e) {
        PRETTY_WARNING << "The argument passed is not a number, you entered: '"
            << portSection << "', stoi error: '" << std::string(e.what()) << "'"
            << ", defaulting to: '0'"
            << std::endl;
        return "0";
    }
}

/**
 * @brief Decrements a port counter value represented as a string.
 *
 * This function takes a string representing a port value (e.g., "0" to `_maximumPortRange`) and decrements
 * it by 1. If the input is invalid, it defaults to "0". If the port value is "0", it wraps around
 * to `_maximumPortRange`.
 *
 * @param portSection The port value as a string. Expected to be a numeric value in the range "0" to `_maximumPortRange`.
 * @return The decremented port value as a string. Returns "0" for invalid input or when the port value is negative.
 *
 * @warning Logs a warning message if the input is not a valid number.
 *
 * @note Leading zeros in the input are accepted but ignored (e.g., "000" is treated as "0").
 * @note The `_maximumPortRange` variable should be properly defined to set the upper limit of the port range.
 */
const std::string Main::_decrementPortCounter(const std::string &portSection)
{
    try {
        const unsigned int port = std::max({ std::stoi(portSection), 0 });
        if (port > 0) {
            return std::to_string(port - 1);
        } else {
            return std::to_string(_maximumPortRange);
        }
    }
    catch (std::invalid_argument &e) {
        PRETTY_WARNING << "The argument passed is not a number, you entered: '"
            << portSection << "', stoi error: '" << std::string(e.what()) << "'"
            << ", defaulting to: '0'"
            << std::endl;
        return "0";
    }
}

/**
 * @brief Increments the value of the first chunk of the IP address.
 *
 * This function retrieves the current value of the first IP chunk, increments it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_incrementIpChunkOne()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4FirstChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the first IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _incrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The first chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Increments the value of the second chunk of the IP address.
 *
 * This function retrieves the current value of the second IP chunk, increments it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_incrementIpChunkTwo()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4SecondChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the second IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _incrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The second chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Increments the value of the third chunk of the IP address.
 *
 * This function retrieves the current value of the third IP chunk, increments it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_incrementIpChunkThree()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4ThirdChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the third IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _incrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The third chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Increments the value of the fourth chunk of the IP address.
 *
 * This function retrieves the current value of the fourth IP chunk, increments it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_incrementIpChunkFour()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4FourthChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the fourth IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _incrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The fourth chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}


/**
 * @brief Increments the value of the port chunk.
 *
 * This function retrieves the current value of the port chunk, increments it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_incrementPortChunk()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_portV4ChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the port chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _incrementPortCounter(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The port chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}


/**
 * @brief Decrements the value of the first chunk of the IP address.
 *
 * This function retrieves the current value of the first IP chunk, decrements it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_decrementIpChunkOne()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4FirstChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the first IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _decrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The first chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Decrements the value of the second chunk of the IP address.
 *
 * This function retrieves the current value of the second IP chunk, decrements it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_decrementIpChunkTwo()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4SecondChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the second IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _decrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The second chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Decrements the value of the third chunk of the IP address.
 *
 * This function retrieves the current value of the third IP chunk, decrements it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_decrementIpChunkThree()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4ThirdChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the third IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _decrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The third chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Decrements the value of the fourth chunk of the IP address.
 *
 * This function retrieves the current value of the fourth IP chunk, decrements it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_decrementIpChunkFour()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_ipV4FourthChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the fourth IP chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _decrementIpV4Node(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The fourth chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}


/**
 * @brief Decrements the value of the port chunk.
 *
 * This function retrieves the current value of the port chunk, decrements it, and updates the corresponding
 * `TextComponent`. If the `TextComponent` cannot be found, an error message is logged.
 */
void Main::_decrementPortChunk()
{
    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Flushing cached events" << std::endl;
    events->flushEvents();
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> text = _getTextComponent(_portV4ChunkKey);
    if (!text.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the port chunk." << std::endl;
        return;
    }
    const std::string currentChunk = text.value()->getText();
    const std::string newChunk = _decrementPortCounter(currentChunk);
    text.value()->setText(newChunk);
    PRETTY_DEBUG << "The port chunk has it's value that has been set to: '"
        << newChunk << "', the previous value was: '" << currentChunk << "'"
        << std::endl;
}

/**
 * @brief Retrieves the EventManager component from the ECS system.
 *
 * This function attempts to fetch the `GUI::ECS::Systems::EventManager` component from the ECS entity system.
 * If the component cannot be found or an uncasting error occurs, an exception is thrown.
 *
 * @throws CustomExceptions::NoEventManager If the `EventManager` component is not found or uncasting fails.
 *
 * @return A `std::shared_ptr` to the `GUI::ECS::Systems::EventManager` component.
 *
 * @note Debug messages are logged to indicate the success or failure of the operation.
 */
const std::shared_ptr<GUI::ECS::Systems::EventManager> Main::_getEventManager()
{
    PRETTY_DEBUG << "Getting the event manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(_ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0], false);
    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<std::any un-casting failed>");
    }
    PRETTY_SUCCESS << "Event manager component found" << std::endl;
    return event_ptr.value();
}

/**
 * @brief Creates a TextComponent entity and initializes its properties.
 *
 * This function constructs a new `GUI::ECS::Components::TextComponent` instance with the
 * specified text, font, and appearance settings, then adds it to the ECS system's entity list.
 *
 * @param application The name of the application the text component belongs to.
 * @param name The name identifier for the text component.
 * @param text The text content to display in the text component.
 * @param font The font to use for rendering the text.
 * @param size The font size to render the text with.
 * @param normal The color of the text in its normal state.
 * @param hover The color of the text when hovered over.
 * @param clicked The color of the text when clicked.
 *
 * @return A `std::shared_ptr` to the created `GUI::ECS::Components::TextComponent`.
 */
const std::shared_ptr<GUI::ECS::Components::TextComponent> Main::_createText(const std::string &application, const std::string &name, const std::string &text, const GUI::ECS::Systems::Font &font, const unsigned int size, const GUI::ECS::Systems::Colour &normal, const GUI::ECS::Systems::Colour &hover, const GUI::ECS::Systems::Colour &clicked)
{
    std::shared_ptr<GUI::ECS::Components::TextComponent> textNode = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, font, text, size);
    textNode->setApplication(application);
    textNode->setName(name);
    textNode->setNormalColor(normal);
    textNode->setHoverColor(hover);
    textNode->setClickedColor(clicked);
    PRETTY_DEBUG << "Ecs before push_backs:\n" << "- TextComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::TextComponent)].size()) << std::endl;
    _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(textNode);
    PRETTY_DEBUG << "Ecs after push_backs:\n" << "- TextComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::TextComponent)].size()) << std::endl;
    _baseId += 1;
    return textNode;
}

/**
 * @brief Function in charge of creating and adding a button component to the ecs system.
 *
 * @param application
 * @param title
 * @param callback
 * @param callbackName
 * @param width
 * @param height
 * @param textSize
 * @param bg
 * @param normal
 * @param hover
 * @param clicked
 *
 * @return const std::shared_ptr<GUI::ECS::Components::ButtonComponent>
 */
const std::shared_ptr<GUI::ECS::Components::ButtonComponent> Main::_createButton(const std::string &application, const std::string &title, std::function<void()> callback, const std::string &callbackName, const int width, const int height, const int textSize, const GUI::ECS::Systems::Colour &bg, const GUI::ECS::Systems::Colour &normal, const GUI::ECS::Systems::Colour &hover, const GUI::ECS::Systems::Colour &clicked, const std::shared_ptr<GUI::ECS::Systems::Font> &textFont)
{
    const std::string errMsgFont = "<Required font not found for the text of the button>, system error: ";
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> fontInstance;
    if (textFont == nullptr) {
        fontInstance = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>, CustomExceptions::NoFont>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], true, errMsgFont);
        if (!fontInstance.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the unknown screen screen." << std::endl;
            throw CustomExceptions::NoFont(errMsgFont);
        }
    } else {
        fontInstance.emplace(textFont);
    }
    std::shared_ptr<GUI::ECS::Components::ShapeComponent> shapeItem = std::make_shared<GUI::ECS::Components::ShapeComponent>(_baseId);
    _baseId += 1;
    shapeItem->setShape(std::pair<float, float>(width, height));
    shapeItem->setNormalColor(bg);
    shapeItem->setHoverColor(bg);
    shapeItem->setClickedColor(bg);
    shapeItem->setApplication(std::string(application + "Shape"));

    std::shared_ptr<GUI::ECS::Components::TextComponent> textItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(fontInstance.value()), title, textSize, normal, hover, clicked);
    textItem->setApplication(std::string(application + "Text"));
    _baseId += 1;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> buttonItem = std::make_shared<GUI::ECS::Components::ButtonComponent>(_baseId, *shapeItem, *textItem);
    buttonItem->setCallback(callback, callbackName);
    buttonItem->setApplication(application);
    _baseId += 1;
    PRETTY_DEBUG << "Ecs before push_backs:\n" <<
        "- TextComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::TextComponent)].size()) << "\n"
        "- ShapeComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::ShapeComponent)].size()) << "\n"
        "- ButtonComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)].size()) << "\n"
        << std::endl;
    PRETTY_DEBUG << "Inserting a TextComponent with key: " << title << std::endl;
    _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(textItem);
    PRETTY_DEBUG << "Inserting a ShapeComponent with key: " << application << std::endl;
    _ecsEntities[typeid(GUI::ECS::Components::ShapeComponent)].push_back(shapeItem);
    PRETTY_DEBUG << "Inserting a Button Component with key: " << Recoded::myToString(_baseId) << std::endl;
    _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)].push_back(buttonItem);
    PRETTY_DEBUG << "Ecs after push_backs:\n" <<
        "- TextComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::TextComponent)].size()) << "\n"
        "- ShapeComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::ShapeComponent)].size()) << "\n"
        "- ButtonComponent: " << Recoded::myToString(_ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)].size()) << "\n"
        << std::endl;
    return buttonItem;
}

/**
 * @brief Function in charge of getting the center X axis of the screen.
 *
 * @return unsigned int
 *
 * @throws CustomExceptions::NoWindow if there is no window instance to gather the information from.
 */
const unsigned int Main::_getScreenCenterX()
{
    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_DEBUG << "Setting the icon at the top center of the main menu." << std::endl;
    const std::pair<int, int> windowDimensions = win.value()->getDimensions();
    if (windowDimensions.first <= 0.0) {
        PRETTY_CRITICAL << "Skipping calculations and rendering because the window is smaller or equal to 0." << std::endl;
        throw CustomExceptions::NoWindow("<There is no window or it's size is smaller than 1>");
    }
    PRETTY_DEBUG << "Calculating the y-coordinate (center of the window)." << std::endl;
    return static_cast<unsigned int>(windowDimensions.first / 2);
}


/**
 * @brief Function in charge of getting the center Y axis of the screen.
 *
 * @return unsigned int
 *
 * @throws CustomExceptions::NoWindow if there is no window instance to gather the information from.
 */
const unsigned int Main::_getScreenCenterY()
{
    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_DEBUG << "Setting the icon at the top center of the main menu." << std::endl;
    const std::pair<int, int> windowDimensions = win.value()->getDimensions();
    if (windowDimensions.second <= 0.0) {
        PRETTY_CRITICAL << "Skipping calculations and rendering because the window is smaller or equal to 0." << std::endl;
        throw CustomExceptions::NoWindow("<There is no window or it's size is smaller than 1>");
    }
    PRETTY_DEBUG << "Calculating the y-coordinate (center of the window)." << std::endl;
    return static_cast<unsigned int>(windowDimensions.second / 2);
}

void Main::_gameScreen()
{
    PRETTY_DEBUG << "In _onlineScreen" << std::endl;
    PRETTY_DEBUG << "_onlineInitialised = " << Recoded::myToString(_onlineInitialised) << ", _onlineStarted = " << Recoded::myToString(_onlineStarted) << std::endl;

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;

    if (!_networkClassSet) {
        PRETTY_DEBUG << "The online brain does not have the network class, providing" << std::endl;
        _onlineBrain.setNetworkClass(_networkManager);
        PRETTY_DEBUG << "The brain now has the network class" << std::endl;
    }

    if (!_onlineInitialised) {
        PRETTY_DEBUG << "The online brain is not initialised, initialising" << std::endl;
        _onlineBrain.initialiseClass(_ecsEntities);
        _onlineInitialised = true;
        _onlineStarted = false;
        PRETTY_DEBUG << "The brain has been initialised" << std::endl;
    }

    if (!_onlineStarted) {
        PRETTY_DEBUG << "The online has not started, starting" << std::endl;
        _onlineBrain.reset();
        _onlineBrain.start();
        _onlineStarted = true;
        PRETTY_DEBUG << "The online has started" << std::endl;
    }

    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _onlineBrain.reset();
        _onlineBrain.stop();
        _onlineStarted = false;
        _connectionInitialised = false;
        _networkManager->stopThread();
        _goHome();
        return;
    }

    if (_onlineBrain.isGameOver()) {
        PRETTY_DEBUG << "The online is over, resetting" << std::endl;
        _onlineBrain.reset();
        _onlineBrain.stop();
        _onlineStarted = false;
        _connectionInitialised = false;
        _networkManager->stopThread();
        PRETTY_DEBUG << "The online has been reset" << std::endl;
        PRETTY_DEBUG << "The user has lost, going to the game over screen" << std::endl;
        _goGameOver();
        PRETTY_DEBUG << "The game over screen has been set to play next" << std::endl;
        return;
    }

    if (_onlineBrain.isGameWon()) {
        PRETTY_DEBUG << "The online has been won, resetting" << std::endl;
        _onlineBrain.reset();
        _onlineBrain.stop();
        _onlineStarted = false;
        _connectionInitialised = false;
        _networkManager->stopThread();
        PRETTY_DEBUG << "The online has been reset" << std::endl;
        PRETTY_DEBUG << "The user has won, going to the game won screen" << std::endl;
        _goGameWon();
        PRETTY_DEBUG << "The game won screen has been set to play next" << std::endl;
        return;
    }

    if (!_connectionInitialised) {
        PRETTY_INFO << "Initialising the connection with the server" << std::endl;
        _initialiseConnection();
        PRETTY_SUCCESS << "Connection with ther server initialised" << std::endl;
        _connectionInitialised = true;
    }

    PRETTY_DEBUG << "Ticking the online brain" << std::endl;
    _onlineBrain.tick(_bufferPackets);
    PRETTY_DEBUG << "Rendering content" << std::endl;
    _onlineBrain.render();
    PRETTY_DEBUG << "Ticked and rendered content" << std::endl;
}

void Main::_demoScreen()
{
    PRETTY_DEBUG << "In _demoScreen" << std::endl;
    PRETTY_DEBUG << "_demoInitialised = " << Recoded::myToString(_demoInitialised) << ", _demoStarted = " << Recoded::myToString(_demoStarted) << std::endl;

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;

    if (!_demoInitialised) {
        PRETTY_DEBUG << "The demo brain is not initialised, initialising" << std::endl;
        _demoBrain.initialiseClass(_ecsEntities);
        _demoInitialised = true;
        _demoStarted = false;
        PRETTY_DEBUG << "The brain has been initialised" << std::endl;
    }

    if (!_demoStarted) {
        PRETTY_DEBUG << "The demo has not started, starting" << std::endl;
        _demoBrain.reset();
        _demoBrain.start();
        _demoStarted = true;
        PRETTY_DEBUG << "The demo has started" << std::endl;
    }

    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _demoBrain.reset();
        _demoBrain.stop();
        _demoStarted = false;
        _goHome();
        return;
    }

    if (_demoBrain.isGameOver()) {
        PRETTY_DEBUG << "The demo is over, resetting" << std::endl;
        _demoBrain.reset();
        _demoBrain.stop();
        _demoStarted = false;
        PRETTY_DEBUG << "The demo has been reset" << std::endl;
        PRETTY_DEBUG << "The user has lost, going to the game over screen" << std::endl;
        _goGameOver();
        PRETTY_DEBUG << "The game over screen has been set to play next" << std::endl;
        return;
    }

    if (_demoBrain.isGameWon()) {
        PRETTY_DEBUG << "The demo has been won, resetting" << std::endl;
        _demoBrain.reset();
        _demoBrain.stop();
        _demoStarted = false;
        PRETTY_DEBUG << "The demo has been reset" << std::endl;
        PRETTY_DEBUG << "The user has won, going to the game won screen" << std::endl;
        _goGameWon();
        PRETTY_DEBUG << "The game won screen has been set to play next" << std::endl;
        return;
    }

    PRETTY_DEBUG << "Ticking the demo brain" << std::endl;
    _demoBrain.tick();
    PRETTY_DEBUG << "Rendering content" << std::endl;
    _demoBrain.render();
    PRETTY_DEBUG << "Ticked and rendered content" << std::endl;
}

void Main::_settingsMenu()
{

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }

    PRETTY_DEBUG << "Getting the sound library if present" << std::endl;
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    PRETTY_DEBUG << "Fetched the sound library" << std::endl;

    PRETTY_DEBUG << "Declaring size customisation options" << std::endl;
    const unsigned int titleTextSize = 40;
    const unsigned int bodyTextSize = 20;
    const unsigned int soundTextSize = 20;
    const unsigned int musicTextSize = 20;
    const unsigned int soundButtonTextSize = 20;
    const unsigned int soundButtonWidth = 50;
    const unsigned int soundButtonHeight = 20;
    const unsigned int musicButtonTextSize = 20;
    const unsigned int musicButtonWidth = 50;
    const unsigned int musicButtonHeight = 20;
    PRETTY_DEBUG << "Declared size customisation options" << std::endl;

    PRETTY_DEBUG << "Declaring colour customisation options" << std::endl;
    const GUI::ECS::Systems::Colour titleColour = GUI::ECS::Systems::Colour::Cyan;
    const GUI::ECS::Systems::Colour bodyColour = GUI::ECS::Systems::Colour::Cyan;
    const GUI::ECS::Systems::Colour soundColour = GUI::ECS::Systems::Colour::Cyan;
    const GUI::ECS::Systems::Colour musicColour = GUI::ECS::Systems::Colour::Cyan;
    const GUI::ECS::Systems::Colour stoppedSoundButtonBackgroundColour = GUI::ECS::Systems::Colour::Red;
    const GUI::ECS::Systems::Colour stoppedSoundButtonNormalColour = GUI::ECS::Systems::Colour::White;
    const GUI::ECS::Systems::Colour stoppedSoundButtonHoverColour = GUI::ECS::Systems::Colour::Grey50;
    const GUI::ECS::Systems::Colour stoppedSoundButtonClickedColour = GUI::ECS::Systems::Colour::Green;
    const GUI::ECS::Systems::Colour playingSoundButtonBackgroundColour = GUI::ECS::Systems::Colour::Green;
    const GUI::ECS::Systems::Colour playingSoundButtonNormalColour = GUI::ECS::Systems::Colour::Black;
    const GUI::ECS::Systems::Colour playingSoundButtonHoverColour = GUI::ECS::Systems::Colour::Grey50;
    const GUI::ECS::Systems::Colour playingSoundButtonClickedColour = GUI::ECS::Systems::Colour::Red;
    const GUI::ECS::Systems::Colour stoppedMusicButtonBackgroundColour = GUI::ECS::Systems::Colour::Red;
    const GUI::ECS::Systems::Colour stoppedMusicButtonNormalColour = GUI::ECS::Systems::Colour::White;
    const GUI::ECS::Systems::Colour stoppedMusicButtonHoverColour = GUI::ECS::Systems::Colour::Grey50;
    const GUI::ECS::Systems::Colour stoppedMusicButtonClickedColour = GUI::ECS::Systems::Colour::Green;
    const GUI::ECS::Systems::Colour playingMusicButtonBackgroundColour = GUI::ECS::Systems::Colour::Green;
    const GUI::ECS::Systems::Colour playingMusicButtonNormalColour = GUI::ECS::Systems::Colour::Black;
    const GUI::ECS::Systems::Colour playingMusicButtonHoverColour = GUI::ECS::Systems::Colour::Grey50;
    const GUI::ECS::Systems::Colour playingMusicButtonClickedColour = GUI::ECS::Systems::Colour::Red;
    PRETTY_DEBUG << "Declared colour customisation options" << std::endl;

    PRETTY_DEBUG << "Declaring required item keys" << std::endl;
    const std::string titleTextKey = "settingsMenuTitleTextKey";
    const std::string bodyTextKey = "settingsMenuBodyTextKey";
    const std::string soundTextKey = "settingsMenuSoundTextKey";
    const std::string musicTextKey = "settingsMenuMusicTextKey";
    const std::string soundButtonKey = "settingsMenuSoundButtonKey";
    const std::string musicButtonKey = "settingsMenuMusicButtonKey";
    PRETTY_DEBUG << "Declared required item keys" << std::endl;

    PRETTY_DEBUG << "Getting the lists of ressources we want" << std::endl;
    // The list of font components to allow the screen to find the ressources it needs if present
    const std::vector<std::any> fonts = _ecsEntities[typeid(GUI::ECS::Systems::Font)];

    // The list of text components to allow the screen to find the ressources it needs if present
    std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];

    // The list of button components to allow the screen to find the ressources it needs if present
    std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];

    // The list of the background components to allow the screen to find the ressources it needs (if present)
    std::vector<std::any> backgrounds = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];
    PRETTY_DEBUG << "Got the list of ressources we want" << std::endl;

    PRETTY_DEBUG << "Declaring the ressources required for the settings menu (for the texts)" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> bodyTextItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> titleTextItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> musicTextItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> soundTextItem;
    PRETTY_DEBUG << "Declared the ressources required for the settings menu (for the texts)" << std::endl;

    PRETTY_DEBUG << "Declaring the ressources required for the settings menu (for the buttons)" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> musicButtonItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> soundButtonItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> mainMenuButtonItem;
    PRETTY_DEBUG << "Declared the ressources required for the settings menu (for the buttons)" << std::endl;

    PRETTY_DEBUG << "Declaring font holder instances" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> defaultFont;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFont;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> buttonFont;
    PRETTY_DEBUG << "Declared font holder instances" << std::endl;

    PRETTY_DEBUG << "Declaring the ressource required for the settings menu to have a background" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundItem;
    PRETTY_DEBUG << "Declared the ressource required for the settings menu to have a background" << std::endl;


    for (std::any textCast : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(textCast, false);
        if (textCapsule.has_value()) {
            continue;
        }
        std::string application = textCapsule.value()->getApplication();
        std::string name = textCapsule.value()->getName();
        if (application == titleTextKey || name == titleTextKey) {
            titleTextItem.emplace(textCapsule.value());
        } else if (application == bodyTextKey || name == bodyTextKey) {
            bodyTextItem.emplace(textCapsule.value());
        } else if (application == soundTextKey || name == soundTextKey) {
            soundTextItem.emplace(textCapsule.value());
        } else if (application == musicTextKey || name == musicTextKey) {
            musicTextItem.emplace(textCapsule.value());
        } else {
            continue;
        }
    }

    for (std::any buttonCast : buttons) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> buttonCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttonCast, false);
        if (buttonCapsule.has_value()) {
            continue;
        }
        std::string application = buttonCapsule.value()->getApplication();
        std::string name = buttonCapsule.value()->getName();
        if (application == soundButtonKey || name == soundButtonKey) {
            soundButtonItem.emplace(buttonCapsule.value());
        } else if (application == _mainMenuKey) {
            mainMenuButtonItem.emplace(buttonCapsule.value());
        } else if (application == musicButtonKey || name == musicButtonKey) {
            musicButtonItem.emplace(buttonCapsule.value());
        } else {
            continue;
        }
    }

    for (std::any backgroundCast : backgrounds) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(backgroundCast, false);
        if (!backgroundCapsule.has_value()) {
            continue;
        }
        if (
            backgroundCapsule.value()->getApplication() == "settings" || backgroundCapsule.value()->getName() == "settings" ||
            backgroundCapsule.value()->getApplication() == "Settings" || backgroundCapsule.value()->getName() == "Settings"
            ) {
            backgroundItem.emplace(backgroundCapsule.value());
        }
    }

    if (!titleTextItem.has_value() || !bodyTextItem.has_value() || !soundTextItem.has_value() || !musicButtonItem.has_value() || !soundButtonItem.has_value() || !mainMenuButtonItem.has_value()) {
        PRETTY_DEBUG << "Fetching the fonts that will be used in the window" << std::endl;
        unsigned int index = 0;
        unsigned int titleFontIndex = 0;
        unsigned int bodyFontIndex = 0;
        unsigned int defaultFontIndex = 0;
        unsigned int buttonFontIndex = 0;
        for (std::any fontCast : fonts) {
            std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> fontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fontCast, false);
            if (!fontCapsule.has_value()) {
                continue;
            }
            std::string applicationContext = fontCapsule.value()->getApplication();
            if (applicationContext == "title") {
                titleFontIndex = index;
            } else if (applicationContext == "body") {
                bodyFontIndex = index;
            } else if (applicationContext == "default") {
                defaultFontIndex = index;
            } else if (applicationContext == "button") {
                buttonFontIndex = index;
            } else {
                index++;
                continue;
            }
            index++;
        }
        const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[titleFontIndex], false);
        const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[bodyFontIndex], false);
        const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> defaultFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[defaultFontIndex], false);
        const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> buttonFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[buttonFontIndex], false);
        if (!defaultFontCapsule.has_value()) {
            PRETTY_DEBUG << "No default font found, aborting program" << std::endl;
            throw CustomExceptions::NoFont("<Default font not found>");
        }
        defaultFont.emplace(defaultFontCapsule.value());
        titleFont.emplace(defaultFontCapsule.value());
        bodyFont.emplace(defaultFontCapsule.value());
        buttonFont.emplace(defaultFontCapsule.value());
        if (titleFontCapsule.has_value()) {
            PRETTY_SUCCESS << "Title font found, not defaulting to the default font." << std::endl;
            titleFont.emplace(titleFontCapsule.value());
        }
        if (bodyFontCapsule.has_value()) {
            PRETTY_SUCCESS << "Body font found, not defaulting to the default font." << std::endl;
            bodyFont.emplace(bodyFontCapsule.value());
        }
        if (buttonFontCapsule.has_value()) {
            PRETTY_SUCCESS << "Button font found, not defaulting to the default font." << std::endl;
            buttonFont.emplace(buttonFontCapsule.value());
        }
        PRETTY_DEBUG << "Fetched the fonts that will be used in the window" << std::endl;
    }

    PRETTY_DEBUG << "Checking is title text component exists" << std::endl;
    if (!titleTextItem.has_value()) {
        PRETTY_DEBUG << "Title text component does not exist, creating" << std::endl;
        if (!titleFont.has_value()) {
            PRETTY_ERROR << "No font found in title font." << std::endl;
            return;
        }
        PRETTY_DEBUG << "Creating title text component" << std::endl;
        titleTextItem = _createText(
            titleTextKey,
            titleTextKey,
            "Settings",
            *(titleFont.value()),
            titleTextSize,
            titleColour,
            titleColour,
            titleColour
        );
        PRETTY_DEBUG << "Created title text component" << std::endl;
    }
    PRETTY_DEBUG << "Checked if title text component existed" << std::endl;

    PRETTY_DEBUG << "Checking is body text component exists" << std::endl;
    if (!bodyTextItem.has_value()) {
        PRETTY_DEBUG << "Body text component does not exist, creating" << std::endl;
        if (!bodyFont.has_value()) {
            PRETTY_ERROR << "No font found in body font." << std::endl;
            return;
        }
        PRETTY_DEBUG << "Creating body text component" << std::endl;
        bodyTextItem = _createText(
            bodyTextKey,
            bodyTextKey,
            "Comme and customise your user experience!",
            *(bodyFont.value()),
            bodyTextSize,
            bodyColour,
            bodyColour,
            bodyColour
        );
        PRETTY_DEBUG << "Created body text component" << std::endl;
    }
    PRETTY_DEBUG << "Checked if body text component existed" << std::endl;

    PRETTY_DEBUG << "Checking is sound text component exists" << std::endl;
    if (!soundTextItem.has_value()) {
        PRETTY_DEBUG << "Sound text component does not exist, creating" << std::endl;
        if (!defaultFont.has_value()) {
            PRETTY_ERROR << "No font found in body font." << std::endl;
            return;
        }
        PRETTY_DEBUG << "Creating sound text component" << std::endl;
        soundTextItem = _createText(
            soundTextKey,
            soundTextKey,
            "Sound effects: ",
            *(defaultFont.value()),
            soundTextSize,
            soundColour,
            soundColour,
            soundColour
        );
        PRETTY_DEBUG << "Created sound text component" << std::endl;
    }
    PRETTY_DEBUG << "Checked if sound text component existed" << std::endl;

    PRETTY_DEBUG << "Checking is music text component exists" << std::endl;
    if (!musicTextItem.has_value()) {
        PRETTY_DEBUG << "Music text component does not exist, creating" << std::endl;
        if (!defaultFont.has_value()) {
            PRETTY_ERROR << "No font found in body font." << std::endl;
            return;
        }
        PRETTY_DEBUG << "Creating music text component" << std::endl;
        musicTextItem = _createText(
            musicTextKey,
            musicTextKey,
            "Music: ",
            *(defaultFont.value()),
            musicTextSize,
            musicColour,
            musicColour,
            musicColour
        );
        PRETTY_DEBUG << "Created music text component" << std::endl;
    }
    PRETTY_DEBUG << "Checked if music text component existed" << std::endl;

    PRETTY_DEBUG << "Checking if the sound button is created" << std::endl;
    if (!soundButtonItem.has_value()) {
        PRETTY_DEBUG << "Sound button component does not exist, creating" << std::endl;
        if (!defaultFont.has_value()) {
            PRETTY_ERROR << "No font found in default font." << std::endl;
            return;
        }
        std::string soundStatus = "OFF";
        GUI::ECS::Systems::Colour soundButtonBackgroundColour = stoppedSoundButtonBackgroundColour;
        GUI::ECS::Systems::Colour soundButtonNormalColour = stoppedSoundButtonNormalColour;
        GUI::ECS::Systems::Colour soundButtonHoverColour = stoppedSoundButtonHoverColour;
        GUI::ECS::Systems::Colour soundButtonClickedColour = stoppedSoundButtonClickedColour;
        if (soundLib.has_value() && soundLib.value()->isEnabled()) {
            soundStatus = "ON";
            soundButtonBackgroundColour = playingSoundButtonBackgroundColour;
            soundButtonNormalColour = playingSoundButtonNormalColour;
            soundButtonHoverColour = playingSoundButtonHoverColour;
            soundButtonClickedColour = playingSoundButtonClickedColour;
        }
        PRETTY_DEBUG << "Creating sound button component" << std::endl;
        soundButtonItem = _createButton(
            soundButtonKey,
            soundStatus,
            std::bind(&Main::_toggleSound, this),
            "_toggleSound",
            soundButtonWidth,
            soundButtonHeight,
            soundButtonTextSize,
            soundButtonBackgroundColour,
            soundButtonNormalColour,
            soundButtonHoverColour,
            soundButtonClickedColour,
            defaultFont.value()
        );
        PRETTY_DEBUG << "sound button component created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the sound button was created" << std::endl;

    PRETTY_DEBUG << "Checking if the music button is created" << std::endl;
    if (!musicButtonItem.has_value()) {
        PRETTY_DEBUG << "Sound button component does not exist, creating" << std::endl;
        if (!defaultFont.has_value()) {
            PRETTY_ERROR << "No font found in default font." << std::endl;
            return;
        }
        std::string musicStatus = "OFF";
        GUI::ECS::Systems::Colour musicButtonBackgroundColour = playingMusicButtonBackgroundColour;
        GUI::ECS::Systems::Colour musicButtonNormalColour = playingMusicButtonNormalColour;
        GUI::ECS::Systems::Colour musicButtonHoverColour = playingMusicButtonHoverColour;
        GUI::ECS::Systems::Colour musicButtonClickedColour = playingMusicButtonClickedColour;
        if (_playMusic) {
            musicStatus = "ON";
            musicButtonBackgroundColour = stoppedMusicButtonBackgroundColour;
            musicButtonNormalColour = stoppedMusicButtonNormalColour;
            musicButtonHoverColour = stoppedMusicButtonHoverColour;
            musicButtonClickedColour = stoppedMusicButtonClickedColour;
        }
        PRETTY_DEBUG << "Creating music button component" << std::endl;
        musicButtonItem = _createButton(
            musicButtonKey,
            musicStatus,
            std::bind(&Main::_toggleMusic, this),
            "_toggleMusic",
            musicButtonWidth,
            musicButtonHeight,
            musicButtonTextSize,
            musicButtonBackgroundColour,
            musicButtonNormalColour,
            musicButtonHoverColour,
            musicButtonClickedColour,
            defaultFont.value()
        );
        PRETTY_DEBUG << "music button component created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the music button was created" << std::endl;

    PRETTY_DEBUG << "Checking if the home button exists" << std::endl;
    if (!mainMenuButtonItem.has_value()) {
        PRETTY_WARNING << "Home button not found, creating" << std::endl;
        mainMenuButtonItem = _createButton(
            _mainMenuKey,
            "Home",
            std::bind(&Main::_goHome, this),
            "_goHome",
            200,
            30,
            20,
            GUI::ECS::Systems::Colour::White,
            GUI::ECS::Systems::Colour::Black,
            GUI::ECS::Systems::Colour::BlueViolet,
            GUI::ECS::Systems::Colour::DeepSkyBlue
        );
        PRETTY_SUCCESS << "Home Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the home button existed" << std::endl;


    PRETTY_DEBUG << "Setting item positions" << std::endl;
    backgroundItem.value()->setDimension(win.value()->getDimensions());
    backgroundItem.value()->setPosition({ 0, 0 });

    float posY = 0;
    float posX = 0;
    const float step = 10;

    titleTextItem.value()->setPosition({ posX, posY });
    posY += step + titleTextSize;
    bodyTextItem.value()->setPosition({ posX, posY });
    posY += step + bodyTextSize;
    soundTextItem.value()->setPosition({ posX, posY });
    posX = _getScreenCenterX();
    soundButtonItem.value()->setPosition({ posX, posY });
    posX = 0;
    posY += step + soundTextSize;
    musicTextItem.value()->setPosition({ posX, posY });
    posX = _getScreenCenterX();
    musicButtonItem.value()->setPosition({ posX, posY });
    posX = 0;
    posY += step + musicTextSize;
    mainMenuButtonItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "Item positions set" << std::endl;

    PRETTY_DEBUG << "Setting the text of the buttons" << std::endl;
    std::string soundStatus = "OFF";
    if (soundLib.has_value() && soundLib.value()->isEnabled()) {
        soundStatus = "ON";
    }
    soundButtonItem.value()->setTextString(soundStatus);
    std::string musicStatus = "OFF";
    if (_playMusic) {
        musicStatus = "ON";
    }
    musicButtonItem.value()->setTextString(musicStatus);
    PRETTY_DEBUG << "The text of the buttons has been set" << std::endl;

    PRETTY_DEBUG << "Setting the colour of the buttons" << std::endl;
    PRETTY_DEBUG << "Colour for the sound" << std::endl;
    if (soundLib.has_value() && soundLib.value()->isEnabled()) {
        soundButtonItem.value()->setNormalColor(playingSoundButtonBackgroundColour);
        soundButtonItem.value()->setHoverColor(playingSoundButtonBackgroundColour);
        soundButtonItem.value()->setClickedColor(playingSoundButtonBackgroundColour);
        soundButtonItem.value()->setTextNormalColor(playingSoundButtonNormalColour);
        soundButtonItem.value()->setTextHoverColor(playingSoundButtonHoverColour);
        soundButtonItem.value()->setTextClickedColor(playingSoundButtonClickedColour);
    } else {
        soundButtonItem.value()->setNormalColor(stoppedSoundButtonBackgroundColour);
        soundButtonItem.value()->setHoverColor(stoppedSoundButtonBackgroundColour);
        soundButtonItem.value()->setClickedColor(stoppedSoundButtonBackgroundColour);
        soundButtonItem.value()->setTextNormalColor(stoppedSoundButtonNormalColour);
        soundButtonItem.value()->setTextHoverColor(stoppedSoundButtonHoverColour);
        soundButtonItem.value()->setTextClickedColor(stoppedSoundButtonClickedColour);
    }
    PRETTY_DEBUG << "Colour for the music" << std::endl;
    if (_playMusic) {
        musicButtonItem.value()->setNormalColor(playingMusicButtonBackgroundColour);
        musicButtonItem.value()->setHoverColor(playingMusicButtonBackgroundColour);
        musicButtonItem.value()->setClickedColor(playingMusicButtonBackgroundColour);
        musicButtonItem.value()->setTextNormalColor(playingMusicButtonNormalColour);
        musicButtonItem.value()->setTextHoverColor(playingMusicButtonHoverColour);
        musicButtonItem.value()->setTextClickedColor(playingMusicButtonClickedColour);
    } else {
        musicButtonItem.value()->setNormalColor(stoppedMusicButtonBackgroundColour);
        musicButtonItem.value()->setHoverColor(stoppedMusicButtonBackgroundColour);
        musicButtonItem.value()->setClickedColor(stoppedMusicButtonBackgroundColour);
        musicButtonItem.value()->setTextNormalColor(stoppedMusicButtonNormalColour);
        musicButtonItem.value()->setTextHoverColor(stoppedMusicButtonHoverColour);
        musicButtonItem.value()->setTextClickedColor(stoppedMusicButtonClickedColour);
    }
    PRETTY_DEBUG << "The colour of the buttons has been set" << std::endl;

    PRETTY_DEBUG << "Displaying elements on the screen" << std::endl;
    win.value()->draw(*(backgroundItem.value()));
    PRETTY_DEBUG << "Background rendered" << std::endl;
    win.value()->draw(*(titleTextItem.value()));
    win.value()->draw(*(bodyTextItem.value()));
    PRETTY_DEBUG << "Title and body text rendered" << std::endl;
    win.value()->draw(*(soundTextItem.value()));
    win.value()->draw(*(soundButtonItem.value()));
    PRETTY_DEBUG << "Sound button and text rendered" << std::endl;
    win.value()->draw(*(musicTextItem.value()));
    win.value()->draw(*(musicButtonItem.value()));
    PRETTY_DEBUG << "Music button and text rendered" << std::endl;
    win.value()->draw(*(mainMenuButtonItem.value()));
    PRETTY_DEBUG << "Home button rendered" << std::endl;
    PRETTY_DEBUG << "Displayed elements on the screen" << std::endl;
}

void Main::_unknownScreen()
{
    bool bodyTextFound = false;
    bool titleTextFound = false;
    bool homeButtonFound = false;

    const std::string titleKey = "unknownScreenTitle";
    const std::string bodyKey = "unknownScreenBody";

    const unsigned int titleTextSize = 40;
    const unsigned int bodyTextSize = 20;

    const GUI::ECS::Systems::Colour textColour = GUI::ECS::Systems::Colour::CadetBlue;

    std::shared_ptr<GUI::ECS::Components::TextComponent> bodyItem;
    std::shared_ptr<GUI::ECS::Components::TextComponent> titleItem;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> homeItem;

    std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }


    for (std::any textCast : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(textCast, false);
        if (textCapsule) {
            if (textCapsule.value()->getApplication() == titleKey) {
                titleTextFound = true;
                titleItem = textCapsule.value();
                titleItem->setSize(titleTextSize);
            } else if (textCapsule.value()->getApplication() == bodyKey) {
                bodyTextFound = true;
                bodyItem = textCapsule.value();
                bodyItem->setSize(bodyTextSize);
            } else {
                continue;
            }
        }
    }

    for (std::any buttonCast : buttons) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> buttonCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttonCast, false);
        if (buttonCapsule) {
            if (buttonCapsule.value()->getApplication() == _mainMenuKey) {
                homeButtonFound = true;
                homeItem = buttonCapsule.value();
            }
        }
    }

    if (!titleTextFound) {
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_titleFontIndex], false);
        if (!titleFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the title text of the unknown screen screen." << std::endl;
            return;
        }
        titleItem = _createText(
            titleKey,
            titleKey,
            "Uh Oh!",
            *(titleFont.value()),
            titleTextSize,
            textColour,
            textColour,
            textColour
        );
    }

    if (!bodyTextFound) {
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], false);
        if (!bodyFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the unknown screen screen." << std::endl;
            return;
        }
        bodyItem = _createText(
            bodyKey,
            bodyKey,
            "It seems like you have landed on an unknown page.",
            *(bodyFont.value()),
            bodyTextSize,
            textColour,
            textColour,
            textColour
        );
    }

    if (!homeButtonFound) {
        PRETTY_WARNING << "Home button not found, creating" << std::endl;
        homeItem = _createButton(
            _mainMenuKey,
            "Home",
            std::bind(&Main::_goHome, this),
            "_goHome",
            200,
            30,
            20,
            GUI::ECS::Systems::Colour::White,
            GUI::ECS::Systems::Colour::Black,
            GUI::ECS::Systems::Colour::BlueViolet,
            GUI::ECS::Systems::Colour::DeepSkyBlue
        );
        PRETTY_SUCCESS << "Home Button created" << std::endl;
    }

    unsigned int posx = _getScreenCenterX();
    unsigned int posy = _getScreenCenterY();

    const unsigned int titleOffest = (2 * titleTextSize);
    const unsigned int titleLength = (titleItem->getSize() + 1) / 2 + titleOffest;
    const unsigned int bodyLength = ((bodyItem->getSize() + 1) / 2) + (17 * bodyTextSize);
    const unsigned int homeItemLength = (homeItem->getTextSize() + 1) / 2 + titleOffest;

    PRETTY_DEBUG << "Lengths:\n- titleLength: '" << titleLength << "'\n- bodyLength: '" << bodyLength << "'\n- homeItemLength: '" << homeItemLength << "'" << std::endl;
    PRETTY_DEBUG << "Positions:\n- posx: '" << posx << "'\n- posy: '" << posy << "'" << std::endl;


    titleItem->setPosition({ posx - titleLength, posy });
    bodyItem->setPosition({ posx - bodyLength, posy + 60 });
    homeItem->setPosition({ posx - homeItemLength, posy + 100 });
    PRETTY_DEBUG << "Component's positions updated for the current screen." << std::endl;
    win.value()->draw(*titleItem);
    win.value()->draw(*bodyItem);
    win.value()->draw(*homeItem);
    PRETTY_SUCCESS << "Component's positions drawn successfully." << std::endl;
}

void Main::_gameOverScreen()
{

    PRETTY_DEBUG << "In the _gameOverScreen function." << std::endl;

    bool bodyTextFound = false;
    bool titleTextFound = false;
    bool homeButtonFound = false;
    bool backgroundFound = false;

    const std::string titleKey = "GameOverScreenTitle";
    const std::string bodyKey = "GameOverScreenBody";
    const std::string backgroundKey = "gameOver";

    const GUI::ECS::Systems::Colour textColour = GUI::ECS::Systems::Colour::Coral4;

    std::shared_ptr<GUI::ECS::Components::TextComponent> bodyItem;
    std::shared_ptr<GUI::ECS::Components::TextComponent> titleItem;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> homeItem;
    std::shared_ptr<GUI::ECS::Components::ImageComponent> backgroundItem;

    std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];
    std::vector<std::any> backgrounds = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];

    PRETTY_DEBUG << "vector texts size: " << texts.size() << std::endl;
    PRETTY_DEBUG << "vector buttons size: " << buttons.size() << std::endl;
    PRETTY_DEBUG << "vector backgrounds size: " << backgrounds.size() << std::endl;

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }

    PRETTY_DEBUG << "Fetching the text components if present." << std::endl;
    for (std::any textCast : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(textCast, false);
        if (textCapsule.has_value()) {
            if (textCapsule.value()->getApplication() == titleKey) {
                titleTextFound = true;
                titleItem = textCapsule.value();
                PRETTY_DEBUG << "Text title found" << std::endl;
            } else if (textCapsule.value()->getApplication() == bodyKey) {
                bodyTextFound = true;
                bodyItem = textCapsule.value();
                PRETTY_DEBUG << "Text body found" << std::endl;
            } else {
                continue;
            }
        }
    }
    PRETTY_DEBUG << "Fetched the text components that were present." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the button." << std::endl;
    for (std::any buttonCast : buttons) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> buttonCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttonCast, false);
        if (buttonCapsule.has_value() && buttonCapsule.value()->getApplication() == _mainMenuKey) {
            homeButtonFound = true;
            homeItem = buttonCapsule.value();
            PRETTY_DEBUG << "Button found" << std::endl;
        }
    }
    PRETTY_DEBUG << "Fetched the button content." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the background." << std::endl;
    for (std::any backgroundCast : backgrounds) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(backgroundCast, false);
        if (backgroundCapsule.has_value() && backgroundCapsule.value()->getApplication() == backgroundKey) {
            backgroundFound = true;
            backgroundItem = backgroundCapsule.value();
            PRETTY_DEBUG << "Background found" << std::endl;
        }
    }
    PRETTY_DEBUG << "Fetched the background content." << std::endl;

    PRETTY_DEBUG << "Values of the checker variables: \n- bodyTextFound: '" << Recoded::myToString(bodyTextFound) << "'\n- titleTextFound: '" << Recoded::myToString(titleTextFound) << "'\n- homeButtonFound: '" << Recoded::myToString(homeButtonFound) << "'" << std::endl;

    PRETTY_DEBUG << "Checking the text for the title." << std::endl;
    if (!titleTextFound) {
        PRETTY_WARNING << "No title text instance found, creating instance." << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_titleFontIndex], false);
        if (!titleFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the title text of the game over screen screen." << std::endl;
            return;
        }
        titleItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(titleFont.value()), "Game Over!");
        titleItem->setApplication(titleKey);
        titleItem->setNormalColor(textColour);
        titleItem->setHoverColor(textColour);
        titleItem->setClickedColor(textColour);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(titleItem);
        _baseId += 1;
    }
    PRETTY_DEBUG << "Checked the text for the title." << std::endl;

    PRETTY_DEBUG << "Checking text content for the body." << std::endl;
    if (!bodyTextFound) {
        PRETTY_WARNING << "No body text instance found, creating instance." << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], false);
        if (!bodyFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the game over screen screen." << std::endl;
            return;
        }
        bodyItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(bodyFont.value()), "You have died!", 20);
        bodyItem->setApplication(bodyKey);
        bodyItem->setNormalColor(textColour);
        bodyItem->setHoverColor(textColour);
        bodyItem->setClickedColor(textColour);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(bodyItem);
        _baseId += 1;
    }
    PRETTY_DEBUG << "Checked the text content for the body." << std::endl;

    PRETTY_DEBUG << "Checking if the Home button exists." << std::endl;
    if (!homeButtonFound) {
        PRETTY_WARNING << "Home button not found, creating" << std::endl;
        homeItem = _createButton(
            _mainMenuKey,
            "Home",
            std::bind(&Main::_goHome, this),
            "_goHome",
            200,
            30,
            20,
            GUI::ECS::Systems::Colour::White,
            GUI::ECS::Systems::Colour::Black,
            GUI::ECS::Systems::Colour::BlueViolet,
            GUI::ECS::Systems::Colour::DeepSkyBlue
        );
        PRETTY_SUCCESS << "Home Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the home button existed." << std::endl;

    if (!backgroundFound) {
        PRETTY_WARNING << "Background not found, changing the text components" << std::endl;
        const GUI::ECS::Systems::Colour defaultColourForNoBackground = GUI::ECS::Systems::Colour::Red;
        titleItem->setNormalColor(defaultColourForNoBackground);
        titleItem->setHoverColor(defaultColourForNoBackground);
        titleItem->setClickedColor(defaultColourForNoBackground);
        bodyItem->setNormalColor(defaultColourForNoBackground);
        bodyItem->setHoverColor(defaultColourForNoBackground);
        bodyItem->setClickedColor(defaultColourForNoBackground);
    }

    PRETTY_DEBUG << "Checking the coordinates for the center of the x and y axis." << std::endl;
    unsigned int posx = _getScreenCenterX();
    unsigned int posy = _getScreenCenterY();
    PRETTY_DEBUG << "Center of the screen is at (" << posx << ", " << posy << ")" << std::endl;

    PRETTY_DEBUG << "The items that are currently loaded, are:\n- " << *titleItem << "\n- " << *bodyItem << "\n- " << *homeItem << std::endl;

    PRETTY_DEBUG << "Setting the position of the components." << std::endl;
    titleItem->setPosition({ posx, posy });
    PRETTY_DEBUG << "Position for the title item is set." << std::endl;
    bodyItem->setPosition({ posx, posy + 40 });
    PRETTY_DEBUG << "Position for the body item is set." << std::endl;
    homeItem->setPosition({ posx, posy + 100 });
    PRETTY_DEBUG << "Position for the home item is set." << std::endl;
    if (backgroundFound) {
        backgroundItem->setDimension({ _windowWidth, _windowHeight });
        win.value()->draw(*backgroundItem);
    }
    PRETTY_DEBUG << "Component's positions updated for the current screen." << std::endl;
    win.value()->draw(*titleItem);
    PRETTY_DEBUG << "Title Item drawn." << std::endl;
    win.value()->draw(*bodyItem);
    PRETTY_DEBUG << "Body Item drawn." << std::endl;
    win.value()->draw(*homeItem);
    PRETTY_DEBUG << "Home Item drawn." << std::endl;
    PRETTY_SUCCESS << "Component's positions drawn successfully." << std::endl;
}

void Main::_gameWonScreen()
{

    PRETTY_DEBUG << "In the _gameWonScreen function." << std::endl;

    bool bodyTextFound = false;
    bool titleTextFound = false;
    bool homeButtonFound = false;
    bool backgroundFound = false;

    const std::string titleKey = "GameWonScreenTitle";
    const std::string bodyKey = "GameWonScreenBody";
    const std::string backgroundKey = "gameWon";

    const GUI::ECS::Systems::Colour textColour = GUI::ECS::Systems::Colour::Chartreuse;

    std::shared_ptr<GUI::ECS::Components::TextComponent> bodyItem;
    std::shared_ptr<GUI::ECS::Components::TextComponent> titleItem;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> homeItem;
    std::shared_ptr<GUI::ECS::Components::ImageComponent> backgroundItem;

    std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];
    std::vector<std::any> backgrounds = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];

    PRETTY_DEBUG << "vector texts size: " << texts.size() << std::endl;
    PRETTY_DEBUG << "vector buttons size: " << buttons.size() << std::endl;
    PRETTY_DEBUG << "vector backgrounds size: " << backgrounds.size() << std::endl;

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }

    PRETTY_DEBUG << "Fetching the text components if present." << std::endl;
    for (std::any textCast : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(textCast, false);
        if (textCapsule.has_value()) {
            if (textCapsule.value()->getApplication() == titleKey) {
                titleTextFound = true;
                titleItem = textCapsule.value();
                PRETTY_DEBUG << "Text title found" << std::endl;
            } else if (textCapsule.value()->getApplication() == bodyKey) {
                bodyTextFound = true;
                bodyItem = textCapsule.value();
                PRETTY_DEBUG << "Text body found" << std::endl;
            } else {
                continue;
            }
        }
    }
    PRETTY_DEBUG << "Fetched the text components that were present." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the button." << std::endl;
    for (std::any buttonCast : buttons) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> buttonCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttonCast, false);
        if (buttonCapsule.has_value() && buttonCapsule.value()->getApplication() == _mainMenuKey) {
            homeButtonFound = true;
            homeItem = buttonCapsule.value();
            PRETTY_DEBUG << "Button found" << std::endl;
        }
    }
    PRETTY_DEBUG << "Fetched the button content." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the background." << std::endl;
    for (std::any backgroundCast : backgrounds) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(backgroundCast, false);
        if (backgroundCapsule.has_value() && backgroundCapsule.value()->getApplication() == backgroundKey) {
            backgroundFound = true;
            backgroundItem = backgroundCapsule.value();
            PRETTY_DEBUG << "Background found" << std::endl;
        }
    }
    PRETTY_DEBUG << "Fetched the background content." << std::endl;

    PRETTY_DEBUG << "Values of the checker variables: \n- bodyTextFound: '" << Recoded::myToString(bodyTextFound) << "'\n- titleTextFound: '" << Recoded::myToString(titleTextFound) << "'\n- homeButtonFound: '" << Recoded::myToString(homeButtonFound) << "'" << std::endl;

    PRETTY_DEBUG << "Checking the text for the title." << std::endl;
    if (!titleTextFound) {
        PRETTY_WARNING << "No title text instance found, creating instance." << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_titleFontIndex], false);
        if (!titleFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the title text of the game won screen screen." << std::endl;
            return;
        }
        titleItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(titleFont.value()), "Game Won!");
        titleItem->setApplication(titleKey);
        titleItem->setNormalColor(textColour);
        titleItem->setHoverColor(textColour);
        titleItem->setClickedColor(textColour);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(titleItem);
        _baseId += 1;
    }
    PRETTY_DEBUG << "Checked the text for the title." << std::endl;

    PRETTY_DEBUG << "Checking text content for the body." << std::endl;
    if (!bodyTextFound) {
        PRETTY_WARNING << "No body text instance found, creating instance." << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], false);
        if (!bodyFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the game won screen screen." << std::endl;
            return;
        }
        bodyItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(bodyFont.value()), "You have won!", 20);
        bodyItem->setApplication(bodyKey);
        bodyItem->setNormalColor(textColour);
        bodyItem->setHoverColor(textColour);
        bodyItem->setClickedColor(textColour);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(bodyItem);
        _baseId += 1;
    }
    PRETTY_DEBUG << "Checked the text content for the body." << std::endl;

    PRETTY_DEBUG << "Checking if the Home button exists." << std::endl;
    if (!homeButtonFound) {
        PRETTY_WARNING << "Home button not found, creating" << std::endl;
        homeItem = _createButton(
            _mainMenuKey,
            "Home",
            std::bind(&Main::_goHome, this),
            "_goHome",
            200,
            30,
            20,
            GUI::ECS::Systems::Colour::White,
            GUI::ECS::Systems::Colour::Black,
            GUI::ECS::Systems::Colour::BlueViolet,
            GUI::ECS::Systems::Colour::DeepSkyBlue
        );
        PRETTY_SUCCESS << "Home Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the home button existed." << std::endl;

    if (!backgroundFound) {
        PRETTY_WARNING << "Background not found, changing the text components" << std::endl;
        const GUI::ECS::Systems::Colour defaultColourForNoBackground = GUI::ECS::Systems::Colour::GreenYellow;
        titleItem->setNormalColor(defaultColourForNoBackground);
        titleItem->setHoverColor(defaultColourForNoBackground);
        titleItem->setClickedColor(defaultColourForNoBackground);
        titleItem->setNormalColor(defaultColourForNoBackground);
        titleItem->setHoverColor(defaultColourForNoBackground);
        titleItem->setClickedColor(defaultColourForNoBackground);
    }

    PRETTY_DEBUG << "Checking the coordinates for the center of the x and y axis." << std::endl;
    unsigned int posx = _getScreenCenterX();
    unsigned int posy = _getScreenCenterY();
    PRETTY_DEBUG << "Center of the screen is at (" << posx << ", " << posy << ")" << std::endl;

    PRETTY_DEBUG << "The items that are currently loaded, are:\n- " << *titleItem << "\n- " << *bodyItem << "\n- " << *homeItem << std::endl;

    PRETTY_DEBUG << "Setting the position of the components." << std::endl;
    titleItem->setPosition({ posx, posy });
    PRETTY_DEBUG << "Position for the title item is set." << std::endl;
    bodyItem->setPosition({ posx, posy + 40 });
    PRETTY_DEBUG << "Position for the body item is set." << std::endl;
    homeItem->setPosition({ posx, posy + 100 });
    PRETTY_DEBUG << "Position for the home item is set." << std::endl;
    if (backgroundFound) {
        backgroundItem->setDimension({ _windowWidth, _windowHeight });
        win.value()->draw(*backgroundItem);
    }
    PRETTY_DEBUG << "Component's positions updated for the current screen." << std::endl;
    win.value()->draw(*titleItem);
    PRETTY_DEBUG << "Title Item drawn." << std::endl;
    win.value()->draw(*bodyItem);
    PRETTY_DEBUG << "Body Item drawn." << std::endl;
    win.value()->draw(*homeItem);
    PRETTY_DEBUG << "Home Item drawn." << std::endl;
    PRETTY_SUCCESS << "Component's positions drawn successfully." << std::endl;
}

void Main::_mainMenuScreen()
{
    const std::string startGameKey = "MainMenuStartGame";
    const std::string onlineGameKey = "MainMenuOnlineGame";
    const std::string settingsKey = "MainMenuSettings";
    const std::string exitMenuKey = "MainMenuexitMenu";

    const unsigned int textSize = 20;
    const unsigned int buttonWidth = 200;
    const unsigned int buttonHeight = 30;
    const GUI::ECS::Systems::Colour &normal = GUI::ECS::Systems::Colour::Black;
    const GUI::ECS::Systems::Colour &hover = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour &clicked = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour &bg = GUI::ECS::Systems::Colour::White;

    const std::vector<std::any> images = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];

    const std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];

    std::shared_ptr<GUI::ECS::Components::ImageComponent> background;
    std::shared_ptr<GUI::ECS::Components::ImageComponent> icon;

    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> startGame;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> onlineGame;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> settings;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> exitWindow;

    unsigned int heightPos = 0;
    const unsigned int heightStep = 40;


    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goExit();
    }

    for (const std::any node : images) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> nodeCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(node, false);
        if (!nodeCapsule.has_value()) {
            PRETTY_WARNING << "The uncasting of an image component has failed." << std::endl;
            continue;
        }
        if (
            nodeCapsule.value()->getName() == "mainMenu" ||
            nodeCapsule.value()->getApplication() == "mainMenu" ||
            nodeCapsule.value()->getName() == "Main Menu" ||
            nodeCapsule.value()->getApplication() == "Main Menu"
            ) {
            PRETTY_INFO << "Background found, assinning to variable" << std::endl;
            background = nodeCapsule.value();
        } else if (
            nodeCapsule.value()->getName() == "icon" ||
            nodeCapsule.value()->getApplication() == "icon" ||
            nodeCapsule.value()->getName() == "Main Icon" ||
            nodeCapsule.value()->getApplication() == "Main Icon" ||
            nodeCapsule.value()->getName() == "R-type" ||
            nodeCapsule.value()->getApplication() == "R-type"
            ) {
            PRETTY_INFO << "Icon found, assinning to variable" << std::endl;
            icon = nodeCapsule.value();
        }
    }

    for (const std::any node : buttons) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> nodeCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(node, false);
        if (!nodeCapsule.has_value()) {
            PRETTY_WARNING << "The uncasting of a button component has failed." << std::endl;
            continue;
        }
        if (
            nodeCapsule.value()->getName() == startGameKey ||
            nodeCapsule.value()->getApplication() == startGameKey
            ) {
            PRETTY_INFO << "Start Game found, assinning to variable" << std::endl;
            startGame.emplace(nodeCapsule.value());
        } else if (
            nodeCapsule.value()->getName() == onlineGameKey ||
            nodeCapsule.value()->getApplication() == onlineGameKey
            ) {
            PRETTY_INFO << "Online Game found, assinning to variable" << std::endl;
            onlineGame.emplace(nodeCapsule.value());
        } else if (
            nodeCapsule.value()->getName() == settingsKey ||
            nodeCapsule.value()->getApplication() == settingsKey
            ) {
            PRETTY_INFO << "Settings found, assinning to variable" << std::endl;
            settings.emplace(nodeCapsule.value());
        } else if (
            nodeCapsule.value()->getName() == exitMenuKey ||
            nodeCapsule.value()->getApplication() == exitMenuKey
            ) {
            PRETTY_INFO << "Exit Menu found, assinning to variable" << std::endl;
            exitWindow.emplace(nodeCapsule.value());
        }
    }


    PRETTY_DEBUG << "Setting the icon at the top center of the main menu." << std::endl;
    const std::pair<int, int> windowDimensions = win.value()->getDimensions();
    PRETTY_DEBUG << "The window dimensions are: " << windowDimensions << std::endl;
    if (windowDimensions.first == 0.0 || windowDimensions.second == 0.0) {
        PRETTY_CRITICAL << "Skipping calculations and rendering because the window is smaller or equal to 0." << std::endl;
        throw CustomExceptions::NoWindow("<There is no window or it's size is smaller than 1>");
    }

    PRETTY_DEBUG << "Getting the icon dimensions" << std::endl;
    const std::pair<float, float> iconDimensions = icon->getDimension();
    PRETTY_DEBUG << "The icon dimensions are : " << iconDimensions << std::endl;
    if (iconDimensions.first <= 0 || iconDimensions.second <= 0) {
        PRETTY_WARNING << "Icon dimensions are zero, skipping position adjustment." << std::endl;
        throw CustomExceptions::NoIcon("<Invalid icon dimensions>");
    }

    PRETTY_DEBUG << "Calculating the center of the window based on the image and the window dimensions." << std::endl;
    const float xCenter = windowDimensions.first / 2.0f;
    const int x = xCenter - (iconDimensions.first / 2);

    PRETTY_DEBUG << "Calculating the y-coordinate (for the top position)." << std::endl;
    const int y = (windowDimensions.second / 10);
    PRETTY_DEBUG << "The adjusted coordinates for the icon are: " << std::pair<int, int>(x, y) << std::endl;
    PRETTY_DEBUG << "The coordinates are: " << std::pair<int, int>(x, y) << std::endl;
    icon->setPosition({ x, y });
    PRETTY_DEBUG << "Icon position set" << std::endl;
    PRETTY_DEBUG << "Setting the size of the background to that of the window" << std::endl;
    background->setPosition({ 0, 0 });
    background->setDimension({ windowDimensions.first, windowDimensions.second });
    PRETTY_DEBUG << "Background position set" << std::endl;

    int verticalIconHeight = 0;
    if (iconDimensions.second < 1) {
        verticalIconHeight = static_cast<int>(std::round(iconDimensions.second * 1000)) + 100;
        PRETTY_DEBUG << "Calculated converted icon height's value is: " << verticalIconHeight << std::endl;
    } else {
        verticalIconHeight = iconDimensions.second;
    }
    heightPos = y + verticalIconHeight;

    PRETTY_DEBUG << "Checking if the Start game button exists." << std::endl;
    if (!startGame.has_value()) {
        PRETTY_WARNING << "Start Game button not found, creating" << std::endl;
        startGame.emplace(
            _createButton(
                startGameKey, "Start Game", std::bind(&Main::_goDemo, this), "_goDemo", buttonWidth, buttonHeight, textSize, bg, normal, hover, clicked
            )
        );
        PRETTY_SUCCESS << "Start Button created" << std::endl;
    }
    startGame.value()->setPosition({ x, heightPos });
    heightPos += heightStep;

    PRETTY_DEBUG << "Checking if the Online game button exists." << std::endl;
    if (!onlineGame.has_value()) {
        PRETTY_WARNING << "Online Game button not found, creating" << std::endl;
        onlineGame.emplace(
            _createButton(
                onlineGameKey, "Online Game", std::bind(&Main::_goConnectionAddress, this), "_goConnectionAddress", buttonWidth, buttonHeight, textSize, bg, normal, hover, clicked
            )
        );
        PRETTY_SUCCESS << "Start Button created" << std::endl;
    }
    onlineGame.value()->setPosition({ x, heightPos });
    heightPos += heightStep;

    PRETTY_DEBUG << "Checking if the settings button exists." << std::endl;
    if (!settings.has_value()) {
        PRETTY_WARNING << "Settings button not found, creating" << std::endl;
        settings.emplace(
            _createButton(
                settingsKey, "Settings", std::bind(&Main::_goSettings, this), "_goSettings", buttonWidth, buttonHeight, textSize, bg, normal, hover, clicked
            )
        );
        PRETTY_SUCCESS << "Settings Button created" << std::endl;
    }
    settings.value()->setPosition({ x, heightPos });
    heightPos += heightStep;

    PRETTY_DEBUG << "Checking if the exit window game button exists." << std::endl;
    if (!exitWindow.has_value()) {
        PRETTY_WARNING << "Exit Window button not found, creating" << std::endl;
        exitWindow.emplace(
            _createButton(
                exitMenuKey, "Exit Window", std::bind(&Main::_goExit, this), "_goExit", buttonWidth, buttonHeight, textSize, bg, normal, hover, clicked
            )
        );
        PRETTY_SUCCESS << "exit window Button created" << std::endl;
    }
    exitWindow.value()->setPosition({ x, heightPos });
    heightPos += heightStep;

    PRETTY_DEBUG << "Drawing the elements required for the main menu to be displayed." << std::endl;
    win.value()->draw(*background);
    PRETTY_SUCCESS << "Main menu background drawn" << std::endl;
    win.value()->draw(*icon);
    PRETTY_SUCCESS << "Icon drawn" << std::endl;
    win.value()->draw(*(startGame.value()));
    PRETTY_SUCCESS << "Start game button drawn" << std::endl;
    win.value()->draw(*(onlineGame.value()));
    PRETTY_SUCCESS << "Online game button drawn" << std::endl;
    win.value()->draw(*(settings.value()));
    PRETTY_SUCCESS << "Settings button drawn" << std::endl;
    win.value()->draw(*(exitWindow.value()));
    PRETTY_SUCCESS << "Exit window button drawn" << std::endl;
}

void Main::_bossFightScreen()
{

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }
}

void Main::_connectionFailedScreen()
{

    PRETTY_DEBUG << "In the _connectionFailedScreen function." << std::endl;

    bool bodyTextFound = false;
    bool titleTextFound = false;
    bool homeButtonFound = false;
    bool backgroundFound = false;
    bool connectButtonFound = false;

    const std::string bodyKey = "ConnectionFailedScreenBody";
    const std::string titleKey = "ConnectionFailedScreenTitle";
    const std::string backgroundKey = "connectionFailed";
    const std::string connectionButtonKey = "ConnectionFailedScreenConnectButton";

    const GUI::ECS::Systems::Colour textColour = GUI::ECS::Systems::Colour::Firebrick;

    std::shared_ptr<GUI::ECS::Components::TextComponent> bodyItem;
    std::shared_ptr<GUI::ECS::Components::TextComponent> titleItem;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> homeItem;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> connectItem;
    std::shared_ptr<GUI::ECS::Components::ImageComponent> backgroundItem;

    const std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    const std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];
    const std::vector<std::any> backgrounds = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];

    PRETTY_DEBUG << "vector texts size: " << texts.size() << std::endl;
    PRETTY_DEBUG << "vector buttons size: " << buttons.size() << std::endl;
    PRETTY_DEBUG << "vector backgrounds size: " << backgrounds.size() << std::endl;

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }

    PRETTY_DEBUG << "Fetching the text components if present." << std::endl;
    for (std::any textCast : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(textCast, false);
        if (textCapsule.has_value()) {
            if (textCapsule.value()->getApplication() == titleKey) {
                titleTextFound = true;
                titleItem = textCapsule.value();
                PRETTY_DEBUG << "Text title found" << std::endl;
            } else if (textCapsule.value()->getApplication() == bodyKey) {
                bodyTextFound = true;
                bodyItem = textCapsule.value();
                PRETTY_DEBUG << "Text body found" << std::endl;
            } else {
                continue;
            }
        }
    }
    PRETTY_DEBUG << "Fetched the text components that were present." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the button." << std::endl;
    for (std::any buttonCast : buttons) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> buttonCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttonCast, false);
        if (buttonCapsule.has_value()) {
            if (buttonCapsule.value()->getApplication() == _mainMenuKey) {
                homeButtonFound = true;
                homeItem = buttonCapsule.value();
                PRETTY_DEBUG << "Home button found" << std::endl;
            } else if (buttonCapsule.value()->getApplication() == connectionButtonKey) {
                connectButtonFound = true;
                connectItem = buttonCapsule.value();
                PRETTY_DEBUG << "Connection button found" << std::endl;
            }
        }
    }
    PRETTY_DEBUG << "Fetched the button content." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the background." << std::endl;
    for (std::any backgroundCast : backgrounds) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(backgroundCast, false);
        if (backgroundCapsule.has_value() && backgroundCapsule.value()->getApplication() == backgroundKey) {
            backgroundFound = true;
            backgroundItem = backgroundCapsule.value();
            PRETTY_DEBUG << "Background found" << std::endl;
        }
    }
    PRETTY_DEBUG << "Fetched the background content." << std::endl;

    PRETTY_DEBUG << "Values of the checker variables: \n- bodyTextFound: '" << Recoded::myToString(bodyTextFound) << "'\n- titleTextFound: '" << Recoded::myToString(titleTextFound) << "'\n- homeButtonFound: '" << Recoded::myToString(homeButtonFound) << "'\n- backgroundFound: '" << Recoded::myToString(backgroundFound) << "'\n- connectButtonFound: '" << Recoded::myToString(connectButtonFound) << "'" << std::endl;

    PRETTY_DEBUG << "Checking the text for the title." << std::endl;
    if (!titleTextFound) {
        PRETTY_WARNING << "No title text instance found, creating instance." << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_titleFontIndex], false);
        if (!titleFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the title text of the game won screen screen." << std::endl;
            return;
        }
        titleItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(titleFont.value()), "Connection failed!");
        titleItem->setApplication(titleKey);
        titleItem->setNormalColor(textColour);
        titleItem->setHoverColor(textColour);
        titleItem->setClickedColor(textColour);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(titleItem);
        _baseId += 1;
    }
    PRETTY_DEBUG << "Checked the text for the title." << std::endl;

    PRETTY_DEBUG << "Checking text content for the body." << std::endl;
    if (!bodyTextFound) {
        PRETTY_WARNING << "No body text instance found, creating instance." << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], false);
        if (!bodyFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the game won screen screen." << std::endl;
            return;
        }
        bodyItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(bodyFont.value()), "You are not connected to the server!", 20);
        bodyItem->setApplication(bodyKey);
        bodyItem->setNormalColor(textColour);
        bodyItem->setHoverColor(textColour);
        bodyItem->setClickedColor(textColour);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(bodyItem);
        _baseId += 1;
    }
    PRETTY_DEBUG << "Checked the text content for the body." << std::endl;

    PRETTY_DEBUG << "Checking if the Home button exists." << std::endl;
    if (!homeButtonFound) {
        PRETTY_WARNING << "Home button not found, creating" << std::endl;
        homeItem = _createButton(
            _mainMenuKey,
            "Home",
            std::bind(&Main::_goHome, this),
            "_goHome",
            200,
            30,
            20,
            GUI::ECS::Systems::Colour::White,
            GUI::ECS::Systems::Colour::Black,
            GUI::ECS::Systems::Colour::BlueViolet,
            GUI::ECS::Systems::Colour::DeepSkyBlue
        );
        PRETTY_SUCCESS << "Home Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the home button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the Connect button exists." << std::endl;
    if (!connectButtonFound) {
        PRETTY_WARNING << "Connect button not found, creating" << std::endl;
        connectItem = _createButton(
            connectionButtonKey,
            "Connection address",
            std::bind(&Main::_goConnectionAddress, this),
            "_goConnectionAddress",
            300,
            30,
            20,
            GUI::ECS::Systems::Colour::White,
            GUI::ECS::Systems::Colour::Black,
            GUI::ECS::Systems::Colour::BlueViolet,
            GUI::ECS::Systems::Colour::DeepSkyBlue
        );
        PRETTY_SUCCESS << "connect Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the home button existed." << std::endl;

    if (!backgroundFound) {
        PRETTY_WARNING << "Background not found, changing the text components" << std::endl;
        const GUI::ECS::Systems::Colour defaultColourForNoBackground = GUI::ECS::Systems::Colour::OrangeRed;
        titleItem->setNormalColor(defaultColourForNoBackground);
        titleItem->setHoverColor(defaultColourForNoBackground);
        titleItem->setClickedColor(defaultColourForNoBackground);
        bodyItem->setNormalColor(defaultColourForNoBackground);
        bodyItem->setHoverColor(defaultColourForNoBackground);
        bodyItem->setClickedColor(defaultColourForNoBackground);
    }

    PRETTY_DEBUG << "Checking the coordinates for the center of the x and y axis." << std::endl;
    unsigned int posx = 40;
    unsigned int posy = 30;
    PRETTY_DEBUG << "Center of the screen is at (" << posx << ", " << posy << ")" << std::endl;

    PRETTY_DEBUG << "The items that are currently loaded, are:\n- " << *titleItem << "\n- " << *bodyItem << "\n- " << *homeItem << std::endl;

    PRETTY_DEBUG << "Setting the position of the components." << std::endl;
    titleItem->setPosition({ posx, posy });
    PRETTY_DEBUG << "Position for the title item is set." << std::endl;
    bodyItem->setPosition({ posx, posy + 40 });
    PRETTY_DEBUG << "Position for the body item is set." << std::endl;
    homeItem->setPosition({ posx, posy + 100 });
    PRETTY_DEBUG << "Position for the home item is set." << std::endl;
    connectItem->setPosition({ posx, posy + 160 });
    PRETTY_DEBUG << "Position for the connect item is set." << std::endl;
    if (backgroundFound) {
        backgroundItem->setDimension({ _windowWidth, _windowHeight });
        win.value()->draw(*backgroundItem);
    }
    PRETTY_DEBUG << "Component's positions updated for the current screen." << std::endl;
    win.value()->draw(*titleItem);
    PRETTY_DEBUG << "Title Item drawn." << std::endl;
    win.value()->draw(*bodyItem);
    PRETTY_DEBUG << "Body Item drawn." << std::endl;
    win.value()->draw(*homeItem);
    PRETTY_DEBUG << "Home Item drawn." << std::endl;
    win.value()->draw(*connectItem);
    PRETTY_DEBUG << "Connect Item drawn." << std::endl;
    PRETTY_SUCCESS << "Component's positions drawn successfully." << std::endl;
}

void Main::_connectionAddressScreen()
{

    PRETTY_DEBUG << "Base id: " << Recoded::myToString(_baseId) << std::endl;

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }
    PRETTY_SUCCESS << "Escape key wasn't pressed" << std::endl;

    PRETTY_DEBUG << "In the _connectionAddressScreen" << std::endl;
    PRETTY_DEBUG << "Initialising keys" << std::endl;
    // navigation and info tokens
    const std::string homeKey = "connectionAddressScreenHome";
    const std::string bodyKey = "connectionAddressScreenBody";
    const std::string titleKey = "connectionAddressScreenTitle";
    const std::string connectKey = "connectionAddressScreenConnect";
    // decoration token
    const std::string backgroundKey = "connectionAddress";
    // ip tokens
    const std::string ipV4FirstDotKey = "connectionAddressScreenIpV4FirstDot";
    const std::string ipV4SecondDotKey = "connectionAddressScreenIpV4SecondDot";
    const std::string ipV4ThirdDotKey = "connectionAddressScreenIpV4ThirdDot";
    // port tokens
    const std::string portV4ColumnKey = "connectionAddressScreenPortV4ColumnKey";
    // ip toggler tokens
    const std::string ipChunkOneUpKey = "connectionAddressScreenIpChunkOneUp";
    const std::string ipChunkOneDownKey = "connectionAddressScreenIpChunkOneDown";
    const std::string ipChunkTwoUpKey = "connectionAddressScreenIpChunkTwoUp";
    const std::string ipChunkTwoDownKey = "connectionAddressScreenIpChunkTwoDown";
    const std::string ipChunkThreeUpKey = "connectionAddressScreenIpChunkThreeUp";
    const std::string ipChunkThreeDownKey = "connectionAddressScreenIpChunkThreeDown";
    const std::string ipChunkFourUpKey = "connectionAddressScreenIpChunkFourUp";
    const std::string ipChunkFourDownKey = "connectionAddressScreenIpChunkFourDown";
    // port toggler tokens
    const std::string portChunkUpKey = "connectionAddressScreenPortChunkUpKey";
    const std::string portChunkDownKey = "connectionAddressScreenPortChunkDownKey";
    PRETTY_DEBUG << "Keys initialised" << std::endl;

    PRETTY_DEBUG << "Fetching component lists from the entity list" << std::endl;
    const std::vector<std::any> fonts = _ecsEntities[typeid(GUI::ECS::Systems::Font)];
    const std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    const std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];
    const std::vector<std::any> backgrounds = _ecsEntities[typeid(GUI::ECS::Components::ImageComponent)];
    PRETTY_DEBUG << "Fetched component lists from the entity list" << std::endl;

    PRETTY_DEBUG << "Setting the default colour for the text that will displayed" << std::endl;
    const GUI::ECS::Systems::Colour textColour = GUI::ECS::Systems::Colour::Wheat;
    PRETTY_DEBUG << "Default colour set" << std::endl;

    PRETTY_DEBUG << "Setting the ip colour for the text that will displayed" << std::endl;
    const GUI::ECS::Systems::Colour textColourIp = GUI::ECS::Systems::Colour::Gold;
    const GUI::ECS::Systems::Colour textColourIpDot = GUI::ECS::Systems::Colour::Chartreuse;
    const GUI::ECS::Systems::Colour textColourPort = GUI::ECS::Systems::Colour::Pink;
    const GUI::ECS::Systems::Colour textColourPortColumn = GUI::ECS::Systems::Colour::MediumAquamarine;
    PRETTY_DEBUG << "Ip text colour set" << std::endl;

    PRETTY_DEBUG << "Setting the size of the title" << std::endl;
    const unsigned int titleSize = 40;
    PRETTY_DEBUG << "Title size set" << std::endl;

    PRETTY_DEBUG << "Setting the size of the body text" << std::endl;
    const unsigned int bodySize = 20;
    PRETTY_DEBUG << "Body text size set" << std::endl;

    PRETTY_DEBUG << "Setting the size for the text that will manage the ip and port display" << std::endl;
    const unsigned int ipTextSize = 20;
    const unsigned int portTextSize = 20;
    const unsigned int ipTextDotSize = ipTextSize;
    const unsigned int portTextColumnSize = portTextSize;
    const unsigned int buttonUpSize = 40;
    const unsigned int buttonUpBoxWidth = 30;
    const unsigned int buttonUpBoxHeight = 30;
    const unsigned int buttonDownSize = 40;
    const unsigned int buttonDownBoxWidth = 30;
    const unsigned int buttonDownBoxHeight = 30;
    PRETTY_DEBUG << "Text size set for ip and port display" << std::endl;

    PRETTY_DEBUG << "Setting the ip and port colour for the buttons that will displayed" << std::endl;
    const GUI::ECS::Systems::Colour buttonUpColourIpNormal = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour buttonUpColourIpHover = GUI::ECS::Systems::Colour::Chartreuse;
    const GUI::ECS::Systems::Colour buttonUpColourIpClicked = GUI::ECS::Systems::Colour::YellowGreen;
    const GUI::ECS::Systems::Colour buttonUpColourIpBackground = GUI::ECS::Systems::Colour::Transparent;

    const GUI::ECS::Systems::Colour buttonUpColourPortNormal = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour buttonUpColourPortHover = GUI::ECS::Systems::Colour::Chartreuse;
    const GUI::ECS::Systems::Colour buttonUpColourPortClicked = GUI::ECS::Systems::Colour::YellowGreen;
    const GUI::ECS::Systems::Colour buttonUpColourPortBackground = GUI::ECS::Systems::Colour::Transparent;

    const GUI::ECS::Systems::Colour buttonDownColourIpNormal = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour buttonDownColourIpHover = GUI::ECS::Systems::Colour::Chartreuse;
    const GUI::ECS::Systems::Colour buttonDownColourIpClicked = GUI::ECS::Systems::Colour::YellowGreen;
    const GUI::ECS::Systems::Colour buttonDownColourIpBackground = GUI::ECS::Systems::Colour::Transparent;

    const GUI::ECS::Systems::Colour buttonDownColourPortNormal = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour buttonDownColourPortHover = GUI::ECS::Systems::Colour::Chartreuse;
    const GUI::ECS::Systems::Colour buttonDownColourPortClicked = GUI::ECS::Systems::Colour::YellowGreen;
    const GUI::ECS::Systems::Colour buttonDownColourPortBackground = GUI::ECS::Systems::Colour::Transparent;
    PRETTY_DEBUG << "Ip and port button colour set" << std::endl;

    PRETTY_DEBUG << "Setting the customisation information for the general buttons" << std::endl;
    const GUI::ECS::Systems::Colour buttonGeneralColourBackground = GUI::ECS::Systems::Colour::White;
    const GUI::ECS::Systems::Colour buttonGeneralColourNormal = GUI::ECS::Systems::Colour::Black;
    const GUI::ECS::Systems::Colour buttonGeneralColourHover = GUI::ECS::Systems::Colour::BlueViolet;
    const GUI::ECS::Systems::Colour buttonGeneralColourClicked = GUI::ECS::Systems::Colour::DeepSkyBlue;
    PRETTY_DEBUG << "General button customisation set" << std::endl;

    PRETTY_DEBUG << "Fetching the fonts that will be used in the window" << std::endl;
    unsigned int index = 0;
    unsigned int titleFontIndex = 0;
    unsigned int bodyFontIndex = 0;
    unsigned int defaultFontIndex = 0;
    unsigned int buttonFontIndex = 0;
    for (std::any fontCast : fonts) {
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> fontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fontCast, false);
        if (!fontCapsule.has_value()) {
            continue;
        }
        std::string applicationContext = fontCapsule.value()->getApplication();
        if (applicationContext == "title") {
            titleFontIndex = index;
        } else if (applicationContext == "body") {
            bodyFontIndex = index;
        } else if (applicationContext == "default") {
            defaultFontIndex = index;
        } else if (applicationContext == "button") {
            buttonFontIndex = index;
        } else {
            index++;
            continue;
        }
        index++;
    }
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> titleFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[titleFontIndex], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[bodyFontIndex], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> defaultFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[defaultFontIndex], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> buttonFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(fonts[buttonFontIndex], false);
    if (!defaultFontCapsule.has_value()) {
        PRETTY_DEBUG << "No default font found, aborting program" << std::endl;
        throw CustomExceptions::NoFont("<Default font not found>");
    }
    const std::shared_ptr<GUI::ECS::Systems::Font> defaultFont = defaultFontCapsule.value();
    std::shared_ptr<GUI::ECS::Systems::Font> titleFont = defaultFontCapsule.value();
    std::shared_ptr<GUI::ECS::Systems::Font> bodyFont = defaultFontCapsule.value();
    std::shared_ptr<GUI::ECS::Systems::Font> buttonFont = defaultFontCapsule.value();
    if (titleFontCapsule.has_value()) {
        PRETTY_SUCCESS << "Title font found, not defaulting to the default font." << std::endl;
        titleFont = titleFontCapsule.value();
    }
    if (bodyFontCapsule.has_value()) {
        PRETTY_SUCCESS << "Body font found, not defaulting to the default font." << std::endl;
        bodyFont = bodyFontCapsule.value();
    }
    if (buttonFontCapsule.has_value()) {
        PRETTY_SUCCESS << "Button font found, not defaulting to the default font." << std::endl;
        buttonFont = buttonFontCapsule.value();
    }
    PRETTY_DEBUG << "Fetched the fonts that will be used in the window" << std::endl;

    PRETTY_DEBUG << "Holder for the background initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundItem;
    PRETTY_DEBUG << "Background holder initialised" << std::endl;

    PRETTY_DEBUG << "Holders for the title and body initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> titleItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> bodyItem;
    PRETTY_DEBUG << "Holders for the title and body initialised" << std::endl;

    PRETTY_DEBUG << "Holders for the home and connect buttons initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> homeItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> connectItem;
    PRETTY_DEBUG << "Holders for the home and connect buttons initialised" << std::endl;

    PRETTY_DEBUG << "Holders for the ip text chunks initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4FirstChunkItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4FirstDotItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4SecondChunkItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4SecondDotItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4ThirdChunkItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4ThirdDotItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> ipV4FourthChunkItem;
    PRETTY_DEBUG << "Holders for the ip text chunks initialised" << std::endl;

    PRETTY_DEBUG << "Holders for the port text chunks initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> portV4ColumnItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> portV4ChunkItem;
    PRETTY_DEBUG << "Holders for the port text chunks initialised" << std::endl;

    PRETTY_DEBUG << "Holders for the ip button chunks initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkOneUpItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkOneDownItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkTwoUpItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkTwoDownItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkThreeUpItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkThreeDownItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkFourUpItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> ipChunkFourDownItem;
    PRETTY_DEBUG << "Holders for the ip button chunks initialised" << std::endl;

    PRETTY_DEBUG << "Holders for the port button chunks initialising" << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> portChunkUpItem;
    std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> portChunkDownItem;
    PRETTY_DEBUG << "Holders for the port button chunks initialised" << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the background." << std::endl;
    for (std::any backgroundCast : backgrounds) {
        std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> backgroundCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ImageComponent>>(backgroundCast, false);
        if (backgroundCapsule.has_value() && backgroundCapsule.value()->getApplication() == backgroundKey) {
            backgroundItem.emplace(backgroundCapsule.value());
            PRETTY_DEBUG << "Background found" << std::endl;
        }
    }
    PRETTY_DEBUG << "Fetched the background content." << std::endl;


    PRETTY_DEBUG << "Fetching the text components if present." << std::endl;
    unsigned int textIndex = 0;
    for (std::any textCast : texts) {
        textIndex += 1;
        PRETTY_DEBUG << "Text component index: " << Recoded::myToString(textIndex) << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>, CustomExceptions::NoText>(textCast, false, "<No text component found>");
        if (!textCapsule.has_value()) {
            PRETTY_WARNING << "No text component found, index: " << Recoded::myToString(textIndex) << std::endl;
            continue;
        }
        std::string applicationContext = textCapsule.value()->getApplication();
        if (applicationContext == titleKey) {
            PRETTY_DEBUG << "Text Node '"
                << titleKey << "' found and assigned to the correct item."
                << std::endl;
            titleItem.emplace(textCapsule.value());
        } else if (applicationContext == bodyKey) {
            PRETTY_DEBUG << "Text Node '"
                << bodyKey << "' found and assigned to the correct item."
                << std::endl;
            bodyItem.emplace(textCapsule.value());
        } else if (applicationContext == _ipV4FirstChunkKey) {
            PRETTY_DEBUG << "Text Node '"
                << _ipV4FirstChunkKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4FirstChunkItem.emplace(textCapsule.value());
        } else if (applicationContext == _ipV4SecondChunkKey) {
            PRETTY_DEBUG << "Text Node '"
                << _ipV4SecondChunkKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4SecondChunkItem.emplace(textCapsule.value());
        } else if (applicationContext == _ipV4ThirdChunkKey) {
            PRETTY_DEBUG << "Text Node '"
                << _ipV4ThirdChunkKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4ThirdChunkItem.emplace(textCapsule.value());
        } else if (applicationContext == _ipV4FourthChunkKey) {
            PRETTY_DEBUG << "Text Node '"
                << _ipV4FirstChunkKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4FourthChunkItem.emplace(textCapsule.value());
        } else if (applicationContext == _portV4ChunkKey) {
            PRETTY_DEBUG << "Text Node '"
                << _portV4ChunkKey << "' found and assigned to the correct item."
                << std::endl;
            portV4ChunkItem.emplace(textCapsule.value());
        } else if (applicationContext == ipV4FirstDotKey) {
            PRETTY_DEBUG << "Text Node '"
                << ipV4FirstDotKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4FirstDotItem.emplace(textCapsule.value());
        } else if (applicationContext == ipV4SecondDotKey) {
            PRETTY_DEBUG << "Text Node '"
                << ipV4SecondDotKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4SecondDotItem.emplace(textCapsule.value());
        } else if (applicationContext == ipV4ThirdDotKey) {
            PRETTY_DEBUG << "Text Node '"
                << ipV4ThirdDotKey << "' found and assigned to the correct item."
                << std::endl;
            ipV4ThirdDotItem.emplace(textCapsule.value());
        } else if (applicationContext == portV4ColumnKey) {
            PRETTY_DEBUG << "Text Node '"
                << portV4ColumnKey << "' found and assigned to the correct item."
                << std::endl;
            portV4ColumnItem.emplace(textCapsule.value());
        } else {
            PRETTY_DEBUG << "The current text node: " << Recoded::myToString(textIndex) << " does not correspond to the researched contexts" << std::endl;
            PRETTY_DEBUG << "Text application context: " << applicationContext << std::endl;
            continue;
        }
    }
    PRETTY_DEBUG << "Fetched the text components that were present." << std::endl;

    PRETTY_DEBUG << "Attempting to fetch content for the button." << std::endl;
    unsigned int buttonIndex = 0;
    for (std::any buttonCast : buttons) {
        buttonIndex += 1;
        PRETTY_DEBUG << "Button index: " << Recoded::myToString(buttonIndex) << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Components::ButtonComponent>> buttonCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::ButtonComponent>>(buttonCast, false);
        if (!buttonCapsule.has_value()) {
            PRETTY_DEBUG << "The current button (index: " << Recoded::myToString(buttonIndex) << ") does not correspond to a button" << std::endl;
            continue;
        }
        std::string applicationContext = buttonCapsule.value()->getApplication();
        if (applicationContext == _mainMenuKey) {
            homeItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "Main menu button found" << std::endl;
        } else if (applicationContext == connectKey) {
            connectItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "Connect button found" << std::endl;
        } else if (applicationContext == ipChunkOneUpKey) {
            ipChunkOneUpItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk one up button found" << std::endl;
        } else if (applicationContext == ipChunkTwoUpKey) {
            ipChunkTwoUpItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk two up button found" << std::endl;
        } else if (applicationContext == ipChunkThreeUpKey) {
            ipChunkThreeUpItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk three up button found" << std::endl;
        } else if (applicationContext == ipChunkFourUpKey) {
            ipChunkFourUpItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk four up button found" << std::endl;
        } else if (applicationContext == ipChunkOneDownKey) {
            ipChunkOneDownItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk one down button found" << std::endl;
        } else if (applicationContext == ipChunkTwoDownKey) {
            ipChunkTwoDownItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk two down button found" << std::endl;
        } else if (applicationContext == ipChunkThreeDownKey) {
            ipChunkThreeDownItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk three down button found" << std::endl;
        } else if (applicationContext == ipChunkFourDownKey) {
            ipChunkFourDownItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "IP chunk four down button found" << std::endl;
        } else if (applicationContext == portChunkUpKey) {
            portChunkUpItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "Port chunk up button found" << std::endl;
        } else if (applicationContext == portChunkDownKey) {
            portChunkDownItem.emplace(buttonCapsule.value());
            PRETTY_DEBUG << "Port chunk down button found" << std::endl;
        } else {
            PRETTY_DEBUG << "Button Index:" << Recoded::myToString(buttonIndex) << std::endl;
            PRETTY_DEBUG << "Unknown button found with context: " << applicationContext << std::endl;
            continue;
        }
    }
    PRETTY_DEBUG << "Fetched the button content." << std::endl;

    PRETTY_DEBUG << "Checking if the Home button exists." << std::endl;
    if (!homeItem.has_value()) {
        PRETTY_WARNING << "Home button not found, creating" << std::endl;
        homeItem = _createButton(
            _mainMenuKey,
            "Home",
            std::bind(&Main::_goHome, this),
            "_goHome",
            200,
            30,
            20,
            buttonGeneralColourBackground,
            buttonGeneralColourNormal,
            buttonGeneralColourHover,
            buttonGeneralColourClicked
        );
        PRETTY_SUCCESS << "Home Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the home button existed." << std::endl;

    PRETTY_DEBUG << "Checking text content for the body." << std::endl;
    if (!bodyItem.has_value()) {
        PRETTY_WARNING << "No body text instance found, creating instance." << std::endl;
        bodyItem = _createText(
            bodyKey,
            bodyKey,
            "Please set the ip for the server",
            *bodyFont,
            bodySize,
            textColour,
            textColour,
            textColour
        );
    }
    PRETTY_DEBUG << "Checked the text content for the body." << std::endl;

    PRETTY_DEBUG << "Checking if the title item is set" << std::endl;
    if (!titleItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the title component" << std::endl;
        titleItem = _createText(
            titleKey,
            titleKey,
            "Server address",
            *titleFont,
            titleSize,
            textColour,
            textColour,
            textColour
        );
    }
    PRETTY_DEBUG << "Checked if the title item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the Connect button exists." << std::endl;
    if (!connectItem.has_value()) {
        PRETTY_WARNING << "Connect button not found, creating" << std::endl;
        connectItem = _createButton(
            connectKey,
            "Connect",
            std::bind(&Main::_goConnect, this),
            "_goConnect",
            200,
            30,
            20,
            buttonGeneralColourBackground,
            buttonGeneralColourNormal,
            buttonGeneralColourHover,
            buttonGeneralColourClicked
        );
        PRETTY_SUCCESS << "Connect Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the Connect button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4FirstChunk item is set" << std::endl;
    if (!ipV4FirstChunkItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4FirstChunk component" << std::endl;
        ipV4FirstChunkItem = _createText(
            _ipV4FirstChunkKey,
            _ipV4FirstChunkKey,
            _getIpChunk(0, "127"),
            *defaultFont,
            ipTextSize,
            textColourIp,
            textColourIp,
            textColourIp
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4FirstChunk item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4FirstDot item is set" << std::endl;
    if (!ipV4FirstDotItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4FirstDot component" << std::endl;
        ipV4FirstDotItem = _createText(
            ipV4FirstDotKey,
            ipV4FirstDotKey,
            ".",
            *defaultFont,
            ipTextSize,
            textColourIpDot,
            textColourIpDot,
            textColourIpDot
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4FirstDot item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4SecondChunk item is set" << std::endl;
    if (!ipV4SecondChunkItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4SecondChunk component" << std::endl;
        ipV4SecondChunkItem = _createText(
            _ipV4SecondChunkKey,
            _ipV4SecondChunkKey,
            _getIpChunk(1, "0"),
            *defaultFont,
            ipTextSize,
            textColourIp,
            textColourIp,
            textColourIp
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4SecondChunk item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4SecondDot item is set" << std::endl;
    if (!ipV4SecondDotItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4SecondDot component" << std::endl;
        ipV4SecondDotItem = _createText(
            ipV4SecondDotKey,
            ipV4SecondDotKey,
            ".",
            *defaultFont,
            ipTextDotSize,
            textColourIpDot,
            textColourIpDot,
            textColourIpDot
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4SecondDot item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4ThirdChunk item is set" << std::endl;
    if (!ipV4ThirdChunkItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4ThirdChunk component" << std::endl;
        ipV4ThirdChunkItem = _createText(
            _ipV4ThirdChunkKey,
            _ipV4ThirdChunkKey,
            _getIpChunk(2, "0"),
            *defaultFont,
            ipTextSize,
            textColourIp,
            textColourIp,
            textColourIp
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4ThirdChunk item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4ThirdDot item is set" << std::endl;
    if (!ipV4ThirdDotItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4ThirdDot component" << std::endl;
        ipV4ThirdDotItem = _createText(
            ipV4ThirdDotKey,
            ipV4ThirdDotKey,
            ".",
            *defaultFont,
            ipTextDotSize,
            textColourIpDot,
            textColourIpDot,
            textColourIpDot
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4ThirdDot item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipV4FourthChunk item is set" << std::endl;
    if (!ipV4FourthChunkItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the ipV4FourthChunk component" << std::endl;
        ipV4FourthChunkItem = _createText(
            _ipV4FourthChunkKey,
            _ipV4FourthChunkKey,
            _getIpChunk(3, "1"),
            *defaultFont,
            ipTextSize,
            textColourIp,
            textColourIp,
            textColourIp
        );
    }
    PRETTY_DEBUG << "Checked if the ipV4FourthChunk item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the portV4Column item is set" << std::endl;
    if (!portV4ColumnItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the portV4Column component" << std::endl;
        portV4ColumnItem = _createText(
            portV4ColumnKey,
            portV4ColumnKey,
            ":",
            *defaultFont,
            portTextColumnSize,
            textColourPortColumn,
            textColourPortColumn,
            textColourPortColumn
        );
    }
    PRETTY_DEBUG << "Checked if the portV4Column item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the portV4Chunk item is set" << std::endl;
    if (!portV4ChunkItem.has_value()) {
        PRETTY_DEBUG << "Title item is not set, setting the portV4Chunk component" << std::endl;
        portV4ChunkItem = _createText(
            _portV4ChunkKey,
            _portV4ChunkKey,
            std::to_string(_port),
            *defaultFont,
            portTextSize,
            textColourPort,
            textColourPort,
            textColourPort
        );
    }
    PRETTY_DEBUG << "Checked if the portV4Chunk item is set" << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkOneUp button exists." << std::endl;
    if (!ipChunkOneUpItem.has_value()) {
        PRETTY_WARNING << "ipChunkOneUp button not found, creating" << std::endl;
        ipChunkOneUpItem = _createButton(
            ipChunkOneUpKey,
            "x",
            std::bind(&Main::_incrementIpChunkOne, this),
            "_incrementIpChunkOne",
            buttonUpBoxWidth,
            buttonUpBoxHeight,
            buttonUpSize,
            buttonUpColourIpBackground,
            buttonUpColourIpNormal,
            buttonUpColourIpHover,
            buttonUpColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkOneUp Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkOneUp button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkOneDown button exists." << std::endl;
    if (!ipChunkOneDownItem.has_value()) {
        PRETTY_WARNING << "ipChunkOneDown button not found, creating" << std::endl;
        ipChunkOneDownItem = _createButton(
            ipChunkOneDownKey,
            "z",
            std::bind(&Main::_decrementIpChunkOne, this),
            "_decrementIpChunkOne",
            buttonDownBoxWidth,
            buttonDownBoxHeight,
            buttonDownSize,
            buttonDownColourIpBackground,
            buttonDownColourIpNormal,
            buttonDownColourIpHover,
            buttonDownColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkOneDown Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkOneDown button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkTwoUp button exists." << std::endl;
    if (!ipChunkTwoUpItem.has_value()) {
        PRETTY_WARNING << "ipChunkTwoUp button not found, creating" << std::endl;
        ipChunkTwoUpItem = _createButton(
            ipChunkTwoUpKey,
            "x",
            std::bind(&Main::_incrementIpChunkTwo, this),
            "_incrementIpChunkTwo",
            buttonUpBoxWidth,
            buttonUpBoxHeight,
            buttonUpSize,
            buttonUpColourIpBackground,
            buttonUpColourIpNormal,
            buttonUpColourIpHover,
            buttonUpColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkTwoUp Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkTwoUp button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkTwoDown button exists." << std::endl;
    if (!ipChunkTwoDownItem.has_value()) {
        PRETTY_WARNING << "ipChunkTwoDown button not found, creating" << std::endl;
        ipChunkTwoDownItem = _createButton(
            ipChunkTwoDownKey,
            "z",
            std::bind(&Main::_decrementIpChunkTwo, this),
            "_decrementIpChunkTwo",
            buttonDownBoxWidth,
            buttonDownBoxHeight,
            buttonDownSize,
            buttonDownColourIpBackground,
            buttonDownColourIpNormal,
            buttonDownColourIpHover,
            buttonDownColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkTwoDown Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkTwoDown button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkThreeUp button exists." << std::endl;
    if (!ipChunkThreeUpItem.has_value()) {
        PRETTY_WARNING << "ipChunkThreeUp button not found, creating" << std::endl;
        ipChunkThreeUpItem = _createButton(
            ipChunkThreeUpKey,
            "x",
            std::bind(&Main::_incrementIpChunkThree, this),
            "_incrementIpChunkThree",
            buttonUpBoxWidth,
            buttonUpBoxHeight,
            buttonUpSize,
            buttonUpColourIpBackground,
            buttonUpColourIpNormal,
            buttonUpColourIpHover,
            buttonUpColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkThreeUp Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkThreeUp button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkThreeDown button exists." << std::endl;
    if (!ipChunkThreeDownItem.has_value()) {
        PRETTY_WARNING << "ipChunkThreeDown button not found, creating" << std::endl;
        ipChunkThreeDownItem = _createButton(
            ipChunkThreeDownKey,
            "z",
            std::bind(&Main::_decrementIpChunkThree, this),
            "_decrementIpChunkThree",
            buttonDownBoxWidth,
            buttonDownBoxHeight,
            buttonDownSize,
            buttonDownColourIpBackground,
            buttonDownColourIpNormal,
            buttonDownColourIpHover,
            buttonDownColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkThreeDown Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkThreeDown button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkFourUp button exists." << std::endl;
    if (!ipChunkFourUpItem.has_value()) {
        PRETTY_WARNING << "ipChunkFourUp button not found, creating" << std::endl;
        ipChunkFourUpItem = _createButton(
            ipChunkFourUpKey,
            "x",
            std::bind(&Main::_incrementIpChunkFour, this),
            "_incrementIpChunkFour",
            buttonUpBoxWidth,
            buttonUpBoxHeight,
            buttonUpSize,
            buttonUpColourIpBackground,
            buttonUpColourIpNormal,
            buttonUpColourIpHover,
            buttonUpColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkFourUp Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkFourUp button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the ipChunkFourDown button exists." << std::endl;
    if (!ipChunkFourDownItem.has_value()) {
        PRETTY_WARNING << "ipChunkFourDown button not found, creating" << std::endl;
        ipChunkFourDownItem = _createButton(
            ipChunkFourDownKey,
            "z",
            std::bind(&Main::_decrementIpChunkFour, this),
            "_decrementIpChunkFour",
            buttonDownBoxWidth,
            buttonDownBoxHeight,
            buttonDownSize,
            buttonDownColourIpBackground,
            buttonDownColourIpNormal,
            buttonDownColourIpHover,
            buttonDownColourIpClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "ipChunkFourDown Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the ipChunkFourDown button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the portChunkUp button exists." << std::endl;
    if (!portChunkUpItem.has_value()) {
        PRETTY_WARNING << "portChunkUp button not found, creating" << std::endl;
        portChunkUpItem = _createButton(
            portChunkUpKey,
            "x",
            std::bind(&Main::_incrementPortChunk, this),
            "_incrementPortChunk",
            buttonUpBoxWidth,
            buttonUpBoxHeight,
            buttonUpSize,
            buttonUpColourPortBackground,
            buttonUpColourPortNormal,
            buttonUpColourPortHover,
            buttonUpColourPortClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "portChunkUp Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the portChunkUp button existed." << std::endl;

    PRETTY_DEBUG << "Checking if the portChunkDown button exists." << std::endl;
    if (!portChunkDownItem.has_value()) {
        PRETTY_WARNING << "portChunkDown button not found, creating" << std::endl;
        portChunkDownItem = _createButton(
            portChunkDownKey,
            "z",
            std::bind(&Main::_decrementPortChunk, this),
            "_decrementPortChunk",
            buttonDownBoxWidth,
            buttonDownBoxHeight,
            buttonDownSize,
            buttonDownColourPortBackground,
            buttonDownColourPortNormal,
            buttonDownColourPortHover,
            buttonDownColourPortClicked,
            buttonFont
        );
        PRETTY_SUCCESS << "portChunkDown Button created" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the portChunkDown button existed." << std::endl;

    PRETTY_DEBUG << "Checking if background exists" << std::endl;
    if (!backgroundItem.has_value()) {
        PRETTY_WARNING << "Background not found, changing the text components" << std::endl;
        const GUI::ECS::Systems::Colour defaultColourForNoBackground = GUI::ECS::Systems::Colour::White;
        titleItem.value()->setNormalColor(defaultColourForNoBackground);
        titleItem.value()->setHoverColor(defaultColourForNoBackground);
        titleItem.value()->setClickedColor(defaultColourForNoBackground);
        bodyItem.value()->setNormalColor(defaultColourForNoBackground);
        bodyItem.value()->setHoverColor(defaultColourForNoBackground);
        bodyItem.value()->setClickedColor(defaultColourForNoBackground);
        ipV4FirstChunkItem.value()->setNormalColor(defaultColourForNoBackground);
        ipV4FirstChunkItem.value()->setHoverColor(defaultColourForNoBackground);
        ipV4FirstChunkItem.value()->setClickedColor(defaultColourForNoBackground);
        ipV4SecondChunkItem.value()->setNormalColor(defaultColourForNoBackground);
        ipV4SecondChunkItem.value()->setHoverColor(defaultColourForNoBackground);
        ipV4SecondChunkItem.value()->setClickedColor(defaultColourForNoBackground);
        ipV4ThirdChunkItem.value()->setNormalColor(defaultColourForNoBackground);
        ipV4ThirdChunkItem.value()->setHoverColor(defaultColourForNoBackground);
        ipV4ThirdChunkItem.value()->setClickedColor(defaultColourForNoBackground);
        ipV4FourthChunkItem.value()->setNormalColor(defaultColourForNoBackground);
        ipV4FourthChunkItem.value()->setHoverColor(defaultColourForNoBackground);
        ipV4FourthChunkItem.value()->setClickedColor(defaultColourForNoBackground);
        portV4ColumnItem.value()->setNormalColor(defaultColourForNoBackground);
        portV4ColumnItem.value()->setHoverColor(defaultColourForNoBackground);
        portV4ColumnItem.value()->setClickedColor(defaultColourForNoBackground);
    }
    PRETTY_DEBUG << "Checked if the background existed." << std::endl;

    PRETTY_DEBUG << "Getting the center y of the screen" << std::endl;
    const unsigned int centerY = _getScreenCenterY();
    const unsigned int centerX = _getScreenCenterX();
    PRETTY_DEBUG << "Center Y of the screen is " << centerY << std::endl;

    PRETTY_DEBUG << "Setting the X padding" << std::endl;
    const unsigned int padX = 10;
    PRETTY_DEBUG << "Setting the Y padding" << std::endl;
    const unsigned int padY = 10;
    PRETTY_DEBUG << "Setting the X line tracker" << std::endl;
    unsigned int posX = padX;
    PRETTY_DEBUG << "Setting the x step" << std::endl;
    const unsigned int ipXStep = 20;
    PRETTY_DEBUG << "Setting the Y column tracker" << std::endl;
    unsigned int posY = padY;
    PRETTY_DEBUG << "Setting the y step" << std::endl;
    const unsigned int yStep = 40;

    PRETTY_DEBUG << "Setting positions" << std::endl;
    titleItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "titleItem position: " << Recoded::myToString(titleItem.value()->getPosition()) << std::endl;
    posY += yStep + titleSize;
    bodyItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "bodyItem position: " << Recoded::myToString(bodyItem.value()->getPosition()) << std::endl;
    posY += yStep + bodySize;
    PRETTY_DEBUG << "Setting the positions for the increment arrows" << std::endl;
    ipChunkOneUpItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkOneUpItem position: " << Recoded::myToString(ipChunkOneUpItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += ipTextDotSize;
    ipChunkTwoUpItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkTwoUpItem position: " << Recoded::myToString(ipChunkTwoUpItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += ipTextDotSize;
    ipChunkThreeUpItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkThreeUpItem position: " << Recoded::myToString(ipChunkThreeUpItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += ipTextDotSize;
    ipChunkFourUpItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkFourUpItem position: " << Recoded::myToString(ipChunkFourUpItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += portTextColumnSize;
    portChunkUpItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "portChunkUpItem position: " << Recoded::myToString(portChunkUpItem.value()->getPosition()) << std::endl;
    PRETTY_DEBUG << "Setting the positions for the texts representing the address" << std::endl;
    posX = padX;
    posY += yStep + ipTextSize;
    PRETTY_DEBUG << "Current posX: " << Recoded::myToString(posX) << ", posY: " << Recoded::myToString(posY) << std::endl;
    ipV4FirstChunkItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4FirstChunkItem position: " << Recoded::myToString(ipV4FirstChunkItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    ipV4FirstDotItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4FirstDotItem position: " << Recoded::myToString(ipV4FirstDotItem.value()->getPosition()) << std::endl;
    posX += ipTextDotSize;
    ipV4SecondChunkItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4SecondChunkItem position: " << Recoded::myToString(ipV4SecondChunkItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    ipV4SecondDotItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4SecondDotItem position: " << Recoded::myToString(ipV4SecondDotItem.value()->getPosition()) << std::endl;
    posX += ipTextDotSize;
    ipV4ThirdChunkItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4ThirdChunkItem position: " << Recoded::myToString(ipV4ThirdChunkItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    ipV4ThirdDotItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4ThirdDotItem position: " << Recoded::myToString(ipV4ThirdDotItem.value()->getPosition()) << std::endl;
    posX += ipTextDotSize;
    ipV4FourthChunkItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipV4FourthChunkItem position: " << Recoded::myToString(ipV4FourthChunkItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    portV4ColumnItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "portV4ColumnItem position: " << Recoded::myToString(portV4ColumnItem.value()->getPosition()) << std::endl;
    posX += portTextColumnSize;
    portV4ChunkItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "portV4ChunkItem position: " << Recoded::myToString(portV4ChunkItem.value()->getPosition()) << std::endl;
    posX = padX;
    posY += yStep;
    PRETTY_DEBUG << "Current posX: " << Recoded::myToString(posX) << ", posY: " << Recoded::myToString(posY) << std::endl;
    ipChunkOneDownItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkOneDownItem position: " << Recoded::myToString(ipChunkOneDownItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += ipTextDotSize;
    ipChunkTwoDownItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkTwoDownItem position: " << Recoded::myToString(ipChunkTwoDownItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += ipTextDotSize;
    ipChunkThreeDownItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkThreeDownItem position: " << Recoded::myToString(ipChunkThreeDownItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += ipTextDotSize;
    ipChunkFourDownItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "ipChunkFourDownItem position: " << Recoded::myToString(ipChunkFourDownItem.value()->getPosition()) << std::endl;
    posX += ipXStep + ipTextSize;
    posX += portTextColumnSize;
    portChunkDownItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "portChunkDownItem position: " << Recoded::myToString(portChunkDownItem.value()->getPosition()) << std::endl;
    posX = padX;
    posY += yStep * 2;
    PRETTY_DEBUG << "Current posX: " << Recoded::myToString(posX) << ", posY: " << Recoded::myToString(posY) << std::endl;
    PRETTY_DEBUG << "Setting the position of the connect button" << std::endl;
    connectItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "connectItem position: " << Recoded::myToString(connectItem.value()->getPosition()) << std::endl;
    posX += ipXStep * 10;
    PRETTY_DEBUG << "Current posX: " << Recoded::myToString(posX) << ", posY: " << Recoded::myToString(posY) << std::endl;
    PRETTY_DEBUG << "Setting the position of the home button" << std::endl;
    homeItem.value()->setPosition({ posX, posY });
    PRETTY_DEBUG << "homeItem position: " << Recoded::myToString(homeItem.value()->getPosition()) << std::endl;
    PRETTY_DEBUG << "Postions set" << std::endl;

    PRETTY_DEBUG << "Rendering the content" << std::endl;
    if (backgroundItem.has_value()) {
        win.value()->draw(*(backgroundItem.value()));
    }
    PRETTY_DEBUG << "Rendered background" << std::endl;
    win.value()->draw(*(titleItem.value()));
    PRETTY_DEBUG << "Rendered title item" << std::endl;
    win.value()->draw(*(bodyItem.value()));
    PRETTY_DEBUG << "Rendered body item" << std::endl;
    win.value()->draw(*(homeItem.value()));
    PRETTY_DEBUG << "Rendered home item" << std::endl;
    win.value()->draw(*(connectItem.value()));
    PRETTY_DEBUG << "Rendered connect item" << std::endl;
    win.value()->draw(*(ipV4FirstChunkItem.value()));
    PRETTY_DEBUG << "Rendered ipV4FirstChunk item" << std::endl;
    win.value()->draw(*(ipV4FirstDotItem.value()));
    PRETTY_DEBUG << "Rendered ipV4FirstDot item" << std::endl;
    win.value()->draw(*(ipV4SecondChunkItem.value()));
    PRETTY_DEBUG << "Rendered ipV4SecondChunk item" << std::endl;
    win.value()->draw(*(ipV4SecondDotItem.value()));
    PRETTY_DEBUG << "Rendered ipV4SecondDotItem" << std::endl;
    win.value()->draw(*(ipV4ThirdChunkItem.value()));
    PRETTY_DEBUG << "Rendered ipV4ThirdChunk item" << std::endl;
    win.value()->draw(*(ipV4ThirdDotItem.value()));
    PRETTY_DEBUG << "Rendered ipV4ThirdDot item" << std::endl;
    win.value()->draw(*(ipV4FourthChunkItem.value()));
    PRETTY_DEBUG << "Rendered ipV4FourthChunk item" << std::endl;
    win.value()->draw(*(portV4ColumnItem.value()));
    PRETTY_DEBUG << "Rendered portV4Column item" << std::endl;
    win.value()->draw(*(portV4ChunkItem.value()));
    PRETTY_DEBUG << "Rendered portV4Chunk item" << std::endl;
    win.value()->draw(*(ipChunkOneUpItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkOneUp item" << std::endl;
    win.value()->draw(*(ipChunkOneDownItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkOneDown item" << std::endl;
    win.value()->draw(*(ipChunkTwoUpItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkTwoUp item" << std::endl;
    win.value()->draw(*(ipChunkTwoDownItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkTwoDown item" << std::endl;
    win.value()->draw(*(ipChunkThreeUpItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkThreeUp item" << std::endl;
    win.value()->draw(*(ipChunkThreeDownItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkThreeDown item" << std::endl;
    win.value()->draw(*(ipChunkFourUpItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkFourUp item" << std::endl;
    win.value()->draw(*(ipChunkFourDownItem.value()));
    PRETTY_DEBUG << "Rendered ipChunkFourDown item" << std::endl;
    win.value()->draw(*(portChunkUpItem.value()));
    PRETTY_DEBUG << "Rendered portChunkUp item" << std::endl;
    win.value()->draw(*(portChunkDownItem.value()));
    PRETTY_DEBUG << "Rendered portChunkDown item" << std::endl;
    PRETTY_DEBUG << "Content rendered" << std::endl;
    PRETTY_DEBUG << "Base id: " << Recoded::myToString(_baseId) << std::endl;
}

void Main::_lobbyList()
{

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }
}

void Main::_lobbyRoom()
{

    PRETTY_DEBUG << "Getting the window manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }
    PRETTY_SUCCESS << "Window manager component found" << std::endl;

    std::shared_ptr<GUI::ECS::Systems::EventManager> events = _getEventManager();
    PRETTY_DEBUG << "Checking if the escape key was pressed" << std::endl;
    if (events->isKeyPressed(GUI::ECS::Systems::Key::Escape)) {
        PRETTY_DEBUG << "Escape key pressed, returning to the home screen" << std::endl;
        _goHome();
    }
}

/**
 * @brief Switches the active screen to the game screen for the online game version.
 *
 * Sets the active screen to @c ActiveScreen::GAME, indicating that
 * the main gameplay screen should be displayed.
 */
void Main::_goPlay()
{
    setActiveScreen(ActiveScreen::GAME);
};

/**
 * @brief Sets the player's name.
 *
 * This function assigns a name to the player. If the provided name is empty,
 * it defaults the player's name to "Player" and logs a warning message.
 *
 * @param player The name of the player to set. If empty, the default name "Player" is used.
 */
void Main::setPlayer(const std::string &player)
{
    if (player == "") {
        PRETTY_WARNING << "Player name is empty, defaulting to 'Player'" << std::endl;
        _player = "Player";
    }
    if (player.length() > 9) {
        PRETTY_WARNING << "The player name is to long, defaulting to 'Player'" << std::endl;
        _player = "Player";
    }
    _player = player;
    _networkManager->setPlayerName(_player);
}

/**
 * @brief Switches the active screen to the local game screen for the offline game version.
 *
 * Sets the active screen to @c ActiveScreen::DEMO, which displays a demo of the game.
 */
void Main::_goDemo()
{
    setActiveScreen(ActiveScreen::DEMO);
};

/**
 * @brief Switches the active screen to the home screen (main menu).
 *
 * Sets the active screen to @c ActiveScreen::MENU, directing the user to the main menu.
 */
void Main::_goHome()
{
    setActiveScreen(ActiveScreen::MENU);
};

/**
 * @brief Exits the application or transitions to an exit screen (closes the window).
 *
 * Sets the active screen to @c ActiveScreen::EXIT, initiating the exit sequence.
 */
void Main::_goExit()
{
    setActiveScreen(ActiveScreen::EXIT);
};

/**
 * @brief Switches the active screen to the settings menu.
 *
 * Sets the active screen to @c ActiveScreen::SETTINGS, where users can adjust game or application settings.
 */
void Main::_goSettings()
{
    setActiveScreen(ActiveScreen::SETTINGS);
};

/**
 * @brief Switches the active screen to the game over screen.
 *
 * Sets the active screen to @c ActiveScreen::GAME_OVER, displayed when the game ends unsuccessfully.
 */
void Main::_goGameOver()
{
    setActiveScreen(ActiveScreen::GAME_OVER);
};

/**
 * @brief Switches the active screen to the game won screen.
 *
 * Sets the active screen to @c ActiveScreen::GAME_WON, shown when the game ends successfully.
 */
void Main::_goGameWon()
{
    setActiveScreen(ActiveScreen::GAME_WON);
};

/**
 * @brief Switches the active screen to the boss fight screen.
 *
 * Sets the active screen to @c ActiveScreen::BOSS_FIGHT, transitioning to the boss battle section of the game.
 */
void Main::_goBossFight()
{
    setActiveScreen(ActiveScreen::BOSS_FIGHT);
};

/**
 * @brief Switches the active screen to the unknown screen (this is when the screen that is supposed to be displayed could not be found).
 *
 * Sets the active screen to @c ActiveScreen::UNKNOWN. This is used when the screen state is undefined.
 */
void Main::_goUnknown()
{
    setActiveScreen(ActiveScreen::UNKNOWN);
};

/**
 * @brief Switches the active screen to a connection failed screen.
 *
 * Sets the active screen to @c ActiveScreen::CONNECTION_FAILED, displayed when a connection attempt fails.
 */
void Main::_goConnectionFailed()
{
    setActiveScreen(ActiveScreen::CONNECTION_FAILED);
};

/**
 * @brief Attempts to establish a connection and updates the active screen based on the connection status.
 *
 * This function initializes the connection process by calling `_initialiseConnection()`. After attempting
 * to connect, it checks the `_connected` flag to determine if the connection was successful. Based on the
 * connection status, the active screen is updated:
 * - If the connection fails, the active screen is set to `ActiveScreen::CONNECTION_FAILED`.
 * - If the connection is successful, the active screen is set to `ActiveScreen::GAME`.
 *
 * @note Logs debug messages throughout the process for diagnostic purposes.
 */
void Main::_goConnect()
{
    PRETTY_DEBUG << "Reconstructing ip" << std::endl;
    PRETTY_DEBUG << "Getting the chunk 1" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> chunkOne = _getTextComponent(_ipV4FirstChunkKey);
    if (!chunkOne.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the first IP chunk." << std::endl;
        _goConnectionFailed();
        return;
    }
    PRETTY_DEBUG << "Got the chunk 1" << std::endl;
    PRETTY_DEBUG << "Getting the chunk 2" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> chunkTwo = _getTextComponent(_ipV4SecondChunkKey);
    if (!chunkTwo.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the second IP chunk." << std::endl;
        _goConnectionFailed();
        return;
    }
    PRETTY_DEBUG << "Got the chunk 2" << std::endl;
    PRETTY_DEBUG << "Getting the chunk 3" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> chunkThree = _getTextComponent(_ipV4ThirdChunkKey);
    if (!chunkThree.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the first IP chunk." << std::endl;
        _goConnectionFailed();
        return;
    }
    PRETTY_DEBUG << "Got the chunk 3" << std::endl;
    PRETTY_DEBUG << "Getting the chunk 4" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> chunkFour = _getTextComponent(_ipV4FourthChunkKey);
    if (!chunkFour.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the first IP chunk." << std::endl;
        _goConnectionFailed();
        return;
    }
    PRETTY_DEBUG << "Got the chunk 4" << std::endl;
    _ip = chunkOne.value()->getText() + ".";
    _ip += chunkTwo.value()->getText() + ".";
    _ip += chunkThree.value()->getText() + ".";
    _ip += chunkFour.value()->getText();
    PRETTY_DEBUG << "Reconstructing port" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> port = _getTextComponent(_portV4ChunkKey);
    if (!port.has_value()) {
        PRETTY_ERROR << "Could not find the text component for the port chunk." << std::endl;
        _goConnectionFailed();
        return;
    }
    try {
        PRETTY_DEBUG << "The text port is: " << port.value()->getText() << std::endl;
        _port = std::stoi(port.value()->getText());
        PRETTY_DEBUG << "The port is" << Recoded::myToString(_port) << std::endl;
    }
    catch (std::invalid_argument &e) {
        PRETTY_ERROR << "Could not convert the port to an integer." << std::endl;
        _goConnectionFailed();
        return;
    }
    PRETTY_DEBUG << "Current address: " << _ip << ":" << Recoded::myToString(_port) << std::endl;
    PRETTY_DEBUG << "Attempting to connect" << std::endl;
    _initialiseConnection();
    PRETTY_DEBUG << "Checking if we are connected" << std::endl;
    if (/*!_networkManager->isConnected()*/false) {
        PRETTY_DEBUG << "We are not connected" << std::endl;
        _goConnectionFailed();
    } else {
        PRETTY_DEBUG << "We are connected" << std::endl;
        _goPlay();
    }
};

/**
 * @brief Switches the active screen to a connection address input screen.
 *
 * Sets the active screen to @c ActiveScreen::CONNECTION_ADDRESS, allowing the user to input a connection address.
 */
void Main::_goConnectionAddress()
{
    setActiveScreen(ActiveScreen::CONNECTION_ADDRESS);
};

/**
 * @brief Switches the active screen to a lobby list  screen.
 *
 * Sets the active screen to @c ActiveScreen::LOBBY_LIST, allowing the user to choose the game they want to play.
 */
void Main::_goLobbyList()
{
    setActiveScreen(ActiveScreen::LOBBY_LIST);
}

/**
 * @brief Switches the active screen to a lobby room input screen.
 *
 * Sets the active screen to @c ActiveScreen::LOBBY_ROOM, allowing the user to wait for other user's to connect.
 */
void Main::_goLobbyRoom()
{
    setActiveScreen(ActiveScreen::LOBBY_ROOM);
}

/**
 * @brief Switches between an active and disabled music playing
 */
void Main::_toggleMusic()
{
    PRETTY_DEBUG << "Getting the event manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(_ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0], false);
    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<std::any un-casting failed>");
    }
    PRETTY_SUCCESS << "Event manager component found" << std::endl;
    PRETTY_DEBUG << "Flushing stored events" << std::endl;
    event_ptr.value()->flushEvents();
    PRETTY_SUCCESS << "Events flushed" << std::endl;


    if (_playMusic) {
        _playMusic = false;
        _updateMusicStatus();
        return;
    }
    _updateMusicStatus();
    _playMusic = true;
}

/**
 * @brief Switches between an active and disabled sound playing
 */
void Main::_toggleSound()
{
    PRETTY_DEBUG << "Getting the event manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(_ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0], false);
    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<std::any un-casting failed>");
    }
    PRETTY_SUCCESS << "Event manager component found" << std::endl;
    PRETTY_DEBUG << "Flushing stored events" << std::endl;
    event_ptr.value()->flushEvents();
    PRETTY_SUCCESS << "Events flushed" << std::endl;


    PRETTY_DEBUG << "Getting the sound library if present" << std::endl;
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    PRETTY_DEBUG << "Fetched the sound library" << std::endl;


    if (soundLib.has_value() && soundLib.value()->isEnabled()) {
        soundLib.value()->setPlay(false);
        return;
    }
    if (soundLib.has_value()) {
        soundLib.value()->setPlay(true);
    }
}

void Main::_updateMusicStatus()
{
    if (!_playMusic) {
        PRETTY_WARNING << "No music is supposed to play, not playing any" << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
        return;
    }
    PRETTY_DEBUG << "Updating the current music that is supposed to play." << std::endl;
    if (_activeScreen == ActiveScreen::MENU || _activeScreen == ActiveScreen::SETTINGS || _activeScreen == ActiveScreen::CONNECTION_ADDRESS || _activeScreen == ActiveScreen::LOBBY_LIST || _activeScreen == ActiveScreen::LOBBY_ROOM) {
        PRETTY_DEBUG << "We're not in game nor in a boss fight, switching to menu music." << std::endl;
        _startMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
    } else if (_activeScreen == ActiveScreen::GAME || _activeScreen == ActiveScreen::DEMO) {
        PRETTY_DEBUG << "Were gaming, swithing to game music." << std::endl;
        _stopMainMenuMusic();
        _startGameLoopMusic();
        _stopBossFightMusic();
    } else if (_activeScreen == ActiveScreen::BOSS_FIGHT) {
        PRETTY_DEBUG << "Boss fight!, switching to boss fight music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _startBossFightMusic();
    } else if (_activeScreen == ActiveScreen::GAME_WON) {
        PRETTY_DEBUG << "Game won!, switching to game won music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
        _winSound();
    } else if (_activeScreen == ActiveScreen::GAME_OVER) {
        PRETTY_DEBUG << "Game won!, switching to game won music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
        _deadSound();
        _gameOverSound();
    } else if (_activeScreen == ActiveScreen::CONNECTION_FAILED) {
        PRETTY_DEBUG << "Game won!, switching to game won music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
        _deadSound();
    } else {
        PRETTY_DEBUG << "No specific music rules, defaulting to no music" << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
    }
    PRETTY_DEBUG << "Updated the current music that is supposed to play." << std::endl;
}

/**
 * @brief Starts the main menu music if it has not already started.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the music associated with the main menu, sets it to loop, and plays it.
 * Ensures that the main menu music is started only once.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_startMainMenuMusic()
{
    if (_mainMenuMusicStarted) {
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (node.value()->getApplication() == "mainMenu" || node.value()->getMusicName() == "mainMenu") {
            node.value()->setLoopMusic(true);
            node.value()->play();
            _mainMenuMusicStarted = true;
        }
    }
}

/**
 * @brief Stops the main menu music if it is currently playing.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the music associated with the main menu, and stops it.
 * Ensures that the main menu music is stopped only when it is playing.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_stopMainMenuMusic()
{
    if (!_mainMenuMusicStarted) {
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "mainMenu" ||
            node.value()->getMusicName() == "mainMenu" ||
            node.value()->getApplication() == "Main Menu" ||
            node.value()->getMusicName() == "Main Menu"
            ) {
            node.value()->stop();
            _mainMenuMusicStarted = false;
        }
    }
}

/**
 * @brief Starts the game loop music if it has not already started.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the music associated with the game loop, sets it to loop, and plays it.
 * Ensures that the game loop music is started only once.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_startGameLoopMusic()
{
    if (_gameMusicStarted) {
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "gameLoop" ||
            node.value()->getMusicName() == "gameLoop" ||
            node.value()->getApplication() == "Game Loop" ||
            node.value()->getMusicName() == "Game Loop"
            ) {
            node.value()->setLoopMusic(true);
            node.value()->play();
            _gameMusicStarted = true;
        }
    }
}


/**
 * @brief Stops the game loop music if it is currently playing.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the music associated with the game loop, and stops it.
 * Ensures that the game loop music is stopped only when it is playing.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_stopGameLoopMusic()
{
    if (!_gameMusicStarted) {
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "gameLoop" ||
            node.value()->getMusicName() == "gameLoop" ||
            node.value()->getApplication() == "Game Loop" ||
            node.value()->getMusicName() == "Game Loop"
            ) {
            node.value()->stop();
            _gameMusicStarted = false;
        }
    }
}

/**
 * @brief Starts the boss fight music if it has not already started.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the music associated with the boss fight, sets it to loop, and plays it.
 * Ensures that the boss fight music is started only once.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_startBossFightMusic()
{
    if (_bossFightMusicStarted) {
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "bossFight" ||
            node.value()->getMusicName() == "bossFight" ||
            node.value()->getApplication() == "Boss Fight" ||
            node.value()->getMusicName() == "Boss Fight"
            ) {
            node.value()->setLoopMusic(true);
            node.value()->play();
            _bossFightMusicStarted = true;
        }
    }
}

/**
 * @brief Stops the boss fight music if it is currently playing.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the music associated with the boss fight, and stops it.
 * Ensures that the boss fight music is stopped only when it is playing.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_stopBossFightMusic()
{
    if (!_bossFightMusicStarted) {
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "bossFight" ||
            node.value()->getMusicName() == "bossFight" ||
            node.value()->getApplication() == "Boss Fight" ||
            node.value()->getMusicName() == "Boss Fight"
            ) {
            node.value()->stop();
            _bossFightMusicStarted = false;
        }
    }
}

/**
 * @brief Plays the shooting sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with shooting, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_shootSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->shootSound();
}

/**
 * @brief Plays the damage sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with damage, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_damageSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->damageSound();
}

/**
 * @brief Plays the death sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with the player or entity death, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_deadSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->deadSound();
}

/**
 * @brief Plays the button click sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with button interactions, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_buttonSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->buttonSound();
}

/**
 * @brief Plays the game over sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with the game over event, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_gameOverSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->gameOverSound();
}

/**
 * @brief Plays the win sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with success or game completion, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void Main::_winSound()
{
    if (_ecsEntities[typeid(SoundLib)].size() == 0) {
        PRETTY_WARNING << "Skipping audio playing because the sound library is missing" << std::endl;
        return;
    }
    std::optional<std::shared_ptr<SoundLib>> soundLib = Utilities::unCast<std::shared_ptr<SoundLib>>(_ecsEntities[typeid(SoundLib)][0], false);
    if (!soundLib.has_value()) {
        PRETTY_WARNING << "The library to find the found player is missing, skipping sound" << std::endl;
        return;
    }
    soundLib.value()->winSound();
}

/**
 * @brief Small function in charge of launching all the loaded musics.
*
*/
void Main::_testContent()
{
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];

    for (unsigned int index = 0; index < musics.size(); index++) {
        try {
            std::shared_ptr<GUI::ECS::Components::MusicComponent> music_ptr = std::any_cast<std::shared_ptr<GUI::ECS::Components::MusicComponent>>(musics[index]);
            PRETTY_INFO << "Playing " << music_ptr->getMusicName() << " audio." << std::endl;
            music_ptr->play();
        }
        catch (std::bad_any_cast &e) {
            PRETTY_ERROR << "Error casting music component, system error: " + std::string(e.what()) << std::endl;
        }
    }
}



/**
 * @brief This is the function in charge of running the program's graphic logic.
 *
 * @return int The status of the overall execution of that section of the program.
 */
void Main::_mainLoop()
{
    // Create the clock component for the ecs function.
    std::int64_t elapsedTime = 0;
    std::shared_ptr<GUI::ECS::Systems::Clock> ECSClock = std::make_shared<GUI::ECS::Systems::Clock>(_baseId);
    _ecsEntities[typeid(GUI::ECS::Systems::Clock)].push_back(ECSClock);

    // Get the window and event
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> window_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][0], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(_ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0], false);

    if (!window_ptr.has_value()) {
        throw CustomExceptions::NoWindow("<std::any un-casting failed>");
    }
    std::shared_ptr<GUI::ECS::Systems::Window> window = window_ptr.value();

    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<std::any un-casting failed>");
    }
    std::shared_ptr<GUI::ECS::Systems::EventManager> event = event_ptr.value();

    // Get the fonts
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_title_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][0], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_body_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][1], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_default_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][2], false);
    const std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_button_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][3], false);

    if (!font_title_ptr.has_value()) {
        throw CustomExceptions::NoFont("Title font", "<std::any un-casting failed>");
    }
    if (!font_body_ptr.has_value()) {
        throw CustomExceptions::NoFont("Body font", "<std::any un-casting failed>");
    }
    if (!font_default_ptr.has_value()) {
        throw CustomExceptions::NoFont("Default font", "<std::any un-casting failed>");
    }
    if (!font_button_ptr.has_value()) {
        throw CustomExceptions::NoFont("Button font", "<std::any un-casting failed>");
    }

    const std::shared_ptr<GUI::ECS::Systems::Font> font_title = font_title_ptr.value();
    const std::shared_ptr<GUI::ECS::Systems::Font> font_body = font_body_ptr.value();
    const std::shared_ptr<GUI::ECS::Systems::Font> font_default = font_default_ptr.value();
    const std::shared_ptr<GUI::ECS::Systems::Font> font_button = font_button_ptr.value();

    // Update the loading text a final time to say that everything has been loaded (yes, even if it will only appear for a fraction of a second).
    PRETTY_INFO << "Updating loading text to 'All the ressources have been loaded'." << std::endl;
    _updateLoadingText("All the ressources have been loaded.");
    PRETTY_INFO << "Updated loading text to 'All the ressources have been loaded'." << std::endl;

    PRETTY_DEBUG << "Checking if the network thread is initialised" << std::endl;
    if (!_networkManager->isThreadAlive()) {
        PRETTY_DEBUG << "Initialising network thread" << std::endl;
        _networkManager->initialize();
        PRETTY_DEBUG << "Initialised network thread" << std::endl;
    }
    PRETTY_DEBUG << "Checked if the network thread is initialised" << std::endl;

    setActiveScreen(ActiveScreen::MENU);

    PRETTY_DEBUG << "Going to start the mainloop." << std::endl;
    while (window->isOpen()) {
        PRETTY_DEBUG << "The active screen is: '" << _activeScreen << "'" << std::endl;
        elapsedTime = ECSClock->reset();
        PRETTY_DEBUG << "Since the last clock reset, the time that has elapsed is: '" << elapsedTime << "'" << std::endl;
        PRETTY_INFO << "Sending all the packets" << std::endl;
        _sendAllPackets();
        PRETTY_INFO << "All the packets have been sent" << std::endl;
        PRETTY_INFO << "Processing incoming packets" << std::endl;
        _processIncommingPackets();
        PRETTY_SUCCESS << "Processed incoming packets" << std::endl;
        event->processEvents(*window, getActiveScreen());
        PRETTY_SUCCESS << "Processed window events (user input basically)" << std::endl;
        _updateMouseForAllRendererables(event->getMouseInfo());
        PRETTY_SUCCESS << "Updated mouse position for all rendererables" << std::endl;
        if (event->isKeyPressed(GUI::ECS::Systems::Key::End)) {
            PRETTY_INFO << "Caps lock is pressed, switching to debug mode" << std::endl;
            _testContent();
        }
        PRETTY_INFO << "Mouse position: " << Recoded::myToString(event->getMousePosition()) << std::endl;
        if (_activeScreen == ActiveScreen::MENU) {
            PRETTY_DEBUG << "Menu screen components are going to be set to be displayed" << std::endl;
            _mainMenuScreen();
            PRETTY_SUCCESS << "Menu screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::GAME) {
            PRETTY_DEBUG << "Game screen components are going to be set to be displayed" << std::endl;
            _gameScreen();
            PRETTY_SUCCESS << "Game screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::DEMO) {
            PRETTY_DEBUG << "Demo screen components are going to be set to be displayed" << std::endl;
            _demoScreen();
            PRETTY_SUCCESS << "Demo screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::SETTINGS) {
            PRETTY_DEBUG << "Settings screen components are going to be set to be displayed" << std::endl;
            _settingsMenu();
            PRETTY_SUCCESS << "Settings screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::GAME_OVER) {
            PRETTY_DEBUG << "Game Over screen components are going to be set to be displayed" << std::endl;
            _gameOverScreen();
            PRETTY_SUCCESS << "Game Over screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::GAME_WON) {
            PRETTY_DEBUG << "Game Won screen components are going to be set to be displayed" << std::endl;
            _gameWonScreen();
            PRETTY_SUCCESS << "Game Won screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::BOSS_FIGHT) {
            PRETTY_DEBUG << "Boss Fight screen components are going to be set to be displayed" << std::endl;
            _bossFightScreen();
            PRETTY_SUCCESS << "Boss Fight screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::CONNECTION_FAILED) {
            PRETTY_DEBUG << "Connection Failed screen components are going to be set to be displayed" << std::endl;
            _connectionFailedScreen();
            PRETTY_SUCCESS << "Connection Failed screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::CONNECTION_ADDRESS) {
            PRETTY_DEBUG << "Connection Address screen components are going to be set to be displayed" << std::endl;
            _connectionAddressScreen();
            PRETTY_SUCCESS << "Connection Address screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::LOBBY_LIST) {
            PRETTY_DEBUG << "Lobby list screen components are going to be set to be displayed" << std::endl;
            _lobbyList();
            PRETTY_SUCCESS << "Lobby list screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::LOBBY_ROOM) {
            PRETTY_DEBUG << "Lobby room screen components are going to be set to be displayed" << std::endl;
            _lobbyRoom();
            PRETTY_SUCCESS << "Lobby room screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::LOADING) {
            PRETTY_DEBUG << "Update loading text screen components are going to be set to be displayed" << std::endl;
            _updateLoadingText("Apparently we are loading something...");
            PRETTY_SUCCESS << "Update loading text screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::EXIT) {
            PRETTY_INFO << "Exit choice detected, stopping" << std::endl;
            window->close();
            _closeConnection();
            _updateMusicStatus();
            PRETTY_INFO << "The window is set to close" << std::endl;
            continue;
        } else {
            PRETTY_DEBUG << "Unknown screen components are set to be displayed" << std::endl;
            _unknownScreen();
            PRETTY_ERROR << "Unknown active screen: " << _activeScreen << std::endl;
        }
        window->display();
        window->clear(GUI::ECS::Systems::Colour::Black);
    }
}

/**
 * @brief This is the function used to start the program's main section.
 *
 * @return int The status of the execution of that section of the program.
 */
void Main::run()
{
    _initialiseRessources();
    _mainLoop();
    _closeConnection();
}

/**
 * @brief This is the function in charge of setting the ip
 * on which the GUI is going to use to communicate about the server.
 *
 * @param ip : std::string
 *
 * @throws CustomExceptions::IncorrectIp(ip) : This error is thrown
 * if the ip format is wrong.
 */
void Main::setIp(const std::string &ip)
{
    if (_isIpInRange(ip) == true) {
        _ip = ip;
        _networkManager->setIp(ip);
    } else {
        throw CustomExceptions::InvalidIp(ip);
    }
}

/**
 * @brief Set the port on which the GUI is going to connect to.
 *
 * @param port
 * @throws CustomExceptions::InvalidPort(port) This error is thrown
 * if the port format is incorrect
 */
void Main::setPort(const unsigned int port)
{
    if (_isPortCorrect(port) == true) {
        _port = port;
        _networkManager->setPort(_port);
    } else {
        throw CustomExceptions::InvalidPort(std::to_string(port));
    }
}

/**
 * @brief Set the width of the window.
 *
 * @param width
 */
void Main::setWindowWidth(unsigned int width)
{
    _windowWidth = width;
}

/**
 * @brief Set the height of the window.
 *
 * @param height
 */
void Main::setWindowHeight(unsigned int height)
{
    _windowHeight = height;
}

/**
 * @brief Set if the cursor is visible when in the window.
 *
 * @param cursorVisible
 */
void Main::setWindowCursor(bool cursorVisible)
{
    _windowCursor = cursorVisible;
}

/**
 * @brief Start the window in full screen mode.
 *
 * @param fullscreen
 */
void Main::setWindowFullscreen(bool fullscreen)
{
    _windowFullscreen = fullscreen;
}

/**
 * @brief Set the title of the window.
 *
 * @param title
 */
void Main::setWindowTitle(const std::string &title)
{
    _windowTitle = title;
}

/**
 * @brief Set the position of the window.
 *
 * @param x The x position of the window.
 * @param y The y position of the window.
 */
void Main::setWindowPosition(unsigned int x, unsigned int y)
{
    _windowX = x;
    _windowY = y;
}

/**
 * @brief Set the X position of the window.
 *
 * @param x The x position of the window.
 */
void Main::setWindowPositionX(unsigned int x)
{
    _windowX = x;
}

/**
 * @brief Set the Y position of the window.
 *
 * @param y The y position of the window.
 */
void Main::setWindowPositionY(unsigned int y)
{
    _windowY = y;
}

/**
 * @brief Set the icon of the cursor
 * (if the user wishes to change the default icon)
 *
 * @param cursorImage
 * @throws CustomExceptions::FileNotFound(cursorImage) This error is thrown
 * if the path to the file is invalid or the file cannot be opened.
 */
void Main::setWindowCursorIcon(const std::string cursorImage)
{
    if (cursorImage == "" || cursorImage == "NULL") {
        _windowCursorIcon = nullptr;
    } else if (_isFilePresent(cursorImage) == true) {
        _windowCursorIcon = cursorImage;
    } else {
        throw CustomExceptions::FileNotFound(cursorImage);
    }
}

/**
 * @brief Set if the image passed is of type sprite or not.
 *
 * @param imageIsSprite
 */
void Main::setWindowCursorSprite(bool imageIsSprite)
{
    _imageIsSprite = imageIsSprite;
}

/**
 * @brief Set the height for the sprite's overlay texture,
 * which is used to draw the sprite's texture during animation.
 *
 * @param spriteWidth
 */
void Main::setWindowCursorSpriteWidth(unsigned int spriteWidth)
{
    _spriteWidth = spriteWidth;
}

/**
 * @brief Inform if the animation should start from the top.
 *
 * @param spriteStartTop
 */
void Main::setWindowCursorSpriteReadFromTop(bool spriteStartTop)
{
    _spriteStartTop = spriteStartTop;
}

/**
 * @brief Inform if the animation should start from the left.
 *
 * @param spriteStartLeft
 */
void Main::setWindowCursorSpriteReadFromLeft(bool spriteStartLeft)
{
    _spriteStartLeft = spriteStartLeft;
}

/**
 * @brief Set the height for the sprite's overlay texture,
 * which is used to draw the sprite's texture during animation.
 *
 * @param spriteHeight
 */
void Main::setWindowCursorSpriteHeight(unsigned int spriteHeight)
{
    _spriteHeight = spriteHeight;
}

/**
 * @brief The window width and height that will be created.
 *
 * @param width
 * @param height
 */
void Main::setWindowSize(unsigned int width, unsigned int height)
{
    _spriteWidth = width;
    _spriteHeight = height;
}

/**
 * @brief The function in charge of setting the frame Limit
 *
 * @param frameLimit
 */
void Main::setFrameLimit(unsigned int frameLimit)
{
    if (_isFrameLimitCorrect(frameLimit) == false) {
        throw CustomExceptions::InvalidFrameLimit(frameLimit);
    }
    _windowFrameLimit = frameLimit;
}

/**
 * @brief This is the function in charge of seting the config filepath.
 *
 * @param configFile
 */
void Main::setConfigFile(const std::string &configFile)
{
    _configFilePath = configFile;
    _loadToml();
}

/**
 * @brief Toggle the logging mode for the program.
 *
 * @param log
 */
void Main::setLog(const bool log)
{
    _log = log;
    Logging::Log::getInstance().setLogEnabled(log);
}

/**
 * @brief Toggle the debug mode for the program.
 *
 * @param debug
 */
void Main::setDebug(const bool debug)
{
    _debug = debug;
    Logging::Log::getInstance().setDebugEnabled(debug);
}

/**
*@brief Function in charge of updating the type of screen that is supposed
*to be displayed as well as change the music based on the active screen.
*
*@param screen of type Active screen which informs the program of the current
*screen type that needs to be processed.
*/
void Main::setActiveScreen(const ActiveScreen screen)
{
    PRETTY_DEBUG << "Getting the event manager component" << std::endl;
    const std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(_ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0], false);
    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<std::any un-casting failed>");
    }
    PRETTY_SUCCESS << "Event manager component found" << std::endl;
    PRETTY_DEBUG << "Flushing stored events" << std::endl;
    event_ptr.value()->flushEvents();
    PRETTY_SUCCESS << "Events flushed" << std::endl;

    PRETTY_DEBUG << "Setting active screen to: '" << Recoded::myToString(screen) << "'" << std::endl;
    _activeScreen = screen;
    PRETTY_DEBUG << "Set active screen to: '" << getActiveScreenAsString() << "'." << std::endl;
    _updateMusicStatus();
}

/**
 * @brief Get the value of the ip that was set.
 *
 * @return const std::string
 */
const std::string Main::getIp()
{
    return _ip;
}

/**
 * @brief Get the value of the port.
 *
 * @return const unsigned int
 */
const unsigned int Main::getPort()
{
    return _port;
}

/**
 * @brief Get the value of the window width.
 *
 * @return unsigned int
 */
unsigned int  Main::getWindowWidth()
{
    return _windowWidth;
}

/**
 * @brief Get the value of the window height.
 *
 * @return unsigned int
 */
unsigned int Main::getWindowHeight()
{
    return _windowHeight;
}

/**
 * @brief Get the status of the window cursor.
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursor()
{
    return _windowCursor;
}

/**
 * @brief Get the status of the window (if it is in fullscreen)
 *
 * @return true
 * @return false
 */
bool Main::getWindowFullscreen()
{
    return _windowFullscreen;
}

/**
 * @brief Get the title of the window.
 *
 * @return const std::string&
 */
const std::string &Main::getWindowTitle()
{
    return _windowTitle;
}

/**
 * @brief Get the icon to display for the window's cursor
 *
 * The string represents a path to the image/sprite file to load.
 *
 * @return const std::string
 */
const std::string &Main::getWindowCursorIcon()
{
    return _windowCursorIcon;
}

/**
 * @brief Get the status if the cursor is of type image or spritesheet
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursorSprite()
{
    return _imageIsSprite;
}

/**
 * @brief Get if the program is supposed to read from the top or not.
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursorSpriteReadFromTop()
{
    return _spriteStartTop;
}

/**
 * @brief Get if the program is supposed to read from the left or the rigth.
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursorSpriteReadFromLeft()
{
    return _spriteStartLeft;
}

/**
 * @brief Get the width of the sprite texture.
 *
 * @return unsigned int
 */
unsigned int Main::getWindowCursorSpriteWidth()
{
    return _spriteWidth;
}

/**
 * @brief Get the height of the sprite texture.
 *
 * @return unsigned int
 */
unsigned int Main::getWindowCursorSpriteHeight()
{
    return _spriteHeight;
}

/**
 * @brief The function in charge of returning the status of the logging variable.
 *
 * @return true
 * @return false
 */
const bool Main::getLog() const
{
    return _log;
}

/**
 * @brief The function in charge of returning the status of the debug variable.
 *
 * @return true
 * @return false
 */
const bool Main::getDebug() const
{
    return _debug;
}


/**
 * @brief Function in charge of returning the current frame limit.
 *
 * @return unsigned int
 */
unsigned int Main::getFrameLimit() const
{
    return _windowFrameLimit;
}


/**
 * @brief Function in charge of returning the path to the config file.
 *
 * @return std::string
 */
std::string Main::getConfigFile() const
{
    return _configFilePath;
}

/**
 * @brief Get the window's position.
 *
 * The order of the tuple is x,y
 *
 * @return std::tuple<unsigned int, unsigned int>
 */
std::tuple<unsigned int, unsigned int> Main::getWindowPosition()
{
    std::tuple<unsigned int, unsigned int> position;
    position = std::make_tuple(_windowX, _windowY);
    return position;
}

/**
 * @brief Get the windows dimensions
 *
 * The order of the tuple is width, height
 *
 * @return std::tuple<unsigned int, unsigned int>
 */
std::tuple<unsigned int, unsigned int> Main::getWindowSize()
{
    std::tuple<unsigned int, unsigned int> dimension;
    dimension = std::make_tuple(_windowWidth, _windowHeight);
    return dimension;
}

/**
 * @brief Function in charge of returning the screen that is currently active
 *
 * @return const ActiveScreen
 */
const ActiveScreen Main::getActiveScreen() const
{
    return _activeScreen;
}

/**
 * @brief Function in charge of returning the screen that is currently active
 * but here, the type will be converted to the human readable version
 * of the screen type.
 *
 * @return const std::string
 */
const std::string Main::getActiveScreenAsString() const
{
    return Recoded::myToString(_activeScreen);
}

/**
*@brief Retrieves the player's name.
*
*This function returns the name of the current player.
*
*@return A string containing the player's name.
*/
const std::string Main::getPlayer() const
{
    return _player;
}

/**
*@brief Load a toml file into the program if it is present.
*
*/
void Main::_loadToml()
{
    _tomlContent.setTOMLPath(_configFilePath);
}
