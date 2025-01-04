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
  * @param ip The IP address to use for connections (default: "127.0.0.1").
  * @param port The port number to use for connections (default: 5000).
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
    const bool debug
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
    _spriteHeight(spriteHeight)
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
    PRETTY_INFO << "End of processing" << std::endl;
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
 * @return true
 * @return false
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
 * @return true
 * @return false
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
 * @brief Check if a music configuration is correct.
 *
 * @param node
 * @return true
 * @return false
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
 * @return true
 * @return false
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
 * @brief This is a generic function that will check if a given key is present and that the type of the value is correct.
 *
 * @param node
 * @param key
 * @param valueType
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

    if (SUCCESS != SUCCESS) {
        throw CustomExceptions::ConnectionFailed(address);
    }
}

/**
 * @brief Close the connection with the server.
 *
 */
void Main::_closeConnection()
{

}


/**
 * @brief This is the function in charge of loading the Sprites and Spritesheets into the program.
 *
 */
std::uint32_t Main::_initialiseSprites()
{
    TOMLLoader sprites(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string spriteSheetKey = "spritesheets";
    const std::string spriteSheetKeyAlt = "spritesheet";
    std::unordered_map<std::string, TOMLLoader> loadedSprites;

    if (_tomlContent.hasKey(spriteSheetKey)) {
        PRETTY_INFO << "Fetching the content for '" << spriteSheetKey << "'." << std::endl;
        PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(spriteSheetKey) << "'." << std::endl;
        if (_tomlContent.getValueType(spriteSheetKey) == toml::node_type::table) {
            sprites = _tomlContent.getTable(spriteSheetKey);
        } else {
            throw CustomExceptions::InvalidConfigurationSpritesheetType(tomlPath, spriteSheetKey, _tomlContent.getValueTypeAsString(spriteSheetKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else if (_tomlContent.hasKey(spriteSheetKeyAlt)) {
        PRETTY_INFO << "Fetching the content for '" << spriteSheetKeyAlt << "'." << std::endl;
        PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(spriteSheetKeyAlt) << "'." << std::endl;
        if (_tomlContent.getValueType(spriteSheetKey) == toml::node_type::table) {
            sprites = _tomlContent.getTable(spriteSheetKey);
        } else {
            throw CustomExceptions::InvalidConfigurationSpritesheetType(tomlPath, spriteSheetKeyAlt, _tomlContent.getValueTypeAsString(spriteSheetKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else {
        PRETTY_CRITICAL << "The key " << spriteSheetKey << " is missing from the config file, " <<
            "the other supported key " << spriteSheetKeyAlt << " wasn't found in the config file." << std::endl;
        throw CustomExceptions::NoSpritesInConfigFile(_tomlContent.getTOMLPath(), spriteSheetKey);
    }

    PRETTY_INFO << "Table data fetched: '" << sprites.getRawTOML() << "'." << std::endl;

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

        if (it->second.hasKey("initial_frame")) {
            initialFrame = it->second.getValue<int>("initial_frame");
        }
        if (it->second.hasKey("end_frame")) {
            endFrame = it->second.getValue<int>("end_frame");
        }

        _updateLoadingText("Loading sprite '" + name + "'...");
        PRETTY_INFO << "Loading sprite '" << name << "' [LOADING]" << std::endl;


        PRETTY_INFO << "Processing Animation component" << std::endl;
        GUI::ECS::Components::AnimationComponent animationNode(_baseId, path, spriteWidth, spriteHeight, startLeft, startTop, initialFrame, endFrame);
        std::shared_ptr<GUI::ECS::Components::AnimationComponent> animationPointer = std::make_shared<GUI::ECS::Components::AnimationComponent>(animationNode);
        _ecsEntities[typeid(GUI::ECS::Components::AnimationComponent)].push_back(animationPointer);
        _baseId++;
        PRETTY_SUCCESS << "Animation component processed" << std::endl;
        PRETTY_INFO << "Adding animation node to sprite '" << name << "'" << std::endl;
        GUI::ECS::Components::SpriteComponent spriteEntity(_baseId, name);
        spriteEntity.setAnimation(animationNode);
        PRETTY_SUCCESS << "Sprite entity added to sprite '" << name << "'" << std::endl;
        PRETTY_INFO << "Creating a shared pointer of the sprite" << std::endl;
        std::shared_ptr<GUI::ECS::Components::SpriteComponent> node = std::make_shared<GUI::ECS::Components::SpriteComponent>(spriteEntity);
        PRETTY_SUCCESS << "Sprite pointer created" << std::endl;
        PRETTY_SUCCESS << "Sprite '" << name << "' loaded" << std::endl;
        node->setApplication(application);
        PRETTY_INFO << "Storing " << name << " into the ecs" << std::endl;
        _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)].push_back(node);
        PRETTY_SUCCESS << name << " stored into the ecs entity" << std::endl;
        _baseId++;

        PRETTY_SUCCESS << "Sprite '" << name << "' [LOADED]" << std::endl;
        _updateLoadingText("Loading sprite '" + name + "'...[OK]");
    }

    PRETTY_SUCCESS << "The sprites are loaded." << std::endl;
    PRETTY_INFO << "Value of the base id: " << std::to_string(_baseId) << std::endl;
    return _baseId;
}

/**
 * @brief This is the function in charge of loading the ²s into the program.
 *
 */
std::uint32_t Main::_initialiseAudio()
{
    TOMLLoader audio(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string musicKey = "music";
    const std::string musicKeyAlt = "musics";
    std::vector<std::string> audios;
    std::unordered_map<std::string, TOMLLoader> loadedAudios;

    if (_tomlContent.hasKey(musicKey)) {
        PRETTY_INFO << "Fetching the content for '" << musicKey << "'." << std::endl;
        PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(musicKey) << "'." << std::endl;
        if (_tomlContent.getValueType(musicKey) == toml::node_type::table) {
            audio = _tomlContent.getTable(musicKey);
        } else {
            throw CustomExceptions::InvalidConfigurationMusicType(tomlPath, musicKey, _tomlContent.getValueTypeAsString(musicKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else if (_tomlContent.hasKey(musicKeyAlt)) {
        PRETTY_INFO << "Fetching the content for '" << musicKeyAlt << "'." << std::endl;
        PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(musicKeyAlt) << "'." << std::endl;
        if (_tomlContent.getValueType(musicKey) == toml::node_type::table) {
            audio = _tomlContent.getTable(musicKey);
        } else {
            throw CustomExceptions::InvalidConfigurationMusicType(tomlPath, musicKeyAlt, _tomlContent.getValueTypeAsString(musicKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else {
        PRETTY_CRITICAL << "The key " << musicKey << " is missing from the config file, " <<
            "the other supported key " << musicKeyAlt << " wasn't found in the config file." << std::endl;
        throw CustomExceptions::NoMusicInConfigFile(_tomlContent.getTOMLPath(), musicKey);
    }

    PRETTY_INFO << audio.getRawTOML() << std::endl;


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
 * @brief This is the function in charge of loading the fonts into the program.
 *
 */
std::uint32_t Main::_initialiseFonts()
{
    TOMLLoader font(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string fontKey = "font";
    const std::string fontKeyAlt = "fonts";
    std::unordered_map<std::string, TOMLLoader> loadedFonts;

    if (_tomlContent.hasKey(fontKey)) {
        PRETTY_INFO << "Fetching the content for '" << fontKey << "'." << std::endl;
        PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(fontKey) << "'." << std::endl;
        if (_tomlContent.getValueType(fontKey) == toml::node_type::table) {
            font = _tomlContent.getTable(fontKey);
        } else {
            throw CustomExceptions::InvalidConfigurationFontType(tomlPath, fontKey, _tomlContent.getValueTypeAsString(fontKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else if (_tomlContent.hasKey(fontKeyAlt)) {
        PRETTY_INFO << "Fetching the content for '" << fontKeyAlt << "'." << std::endl;
        PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(fontKeyAlt) << "'." << std::endl;
        if (_tomlContent.getValueType(fontKey) == toml::node_type::table) {
            font = _tomlContent.getTable(fontKey);
        } else {
            throw CustomExceptions::InvalidConfigurationFontType(tomlPath, fontKeyAlt, _tomlContent.getValueTypeAsString(fontKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else {
        PRETTY_CRITICAL << "The key " << fontKey << " is missing from the config file, " <<
            "the other supported key " << fontKeyAlt << " wasn't found in the config file." << std::endl;
        throw CustomExceptions::NoFontInConfigFile(_tomlContent.getTOMLPath(), fontKey);
    }

    PRETTY_INFO << font.getRawTOML() << std::endl;

    const std::string titleFontNode = "title";
    const std::string bodyFontNode = "body";
    const std::string defaultFontNode = "default";

    if (!font.hasKey(titleFontNode)) {
        throw CustomExceptions::NoTitleFontConfiguration(tomlPath);
    }
    if (!font.hasKey(bodyFontNode)) {
        throw CustomExceptions::NoBodyFontConfiguration(tomlPath);
    }
    if (!font.hasKey(defaultFontNode)) {
        throw CustomExceptions::NoDefaultFontConfiguration(tomlPath);
    }

    TOMLLoader tempNode(font);

    loadedFonts["title"] = tempNode;
    loadedFonts["body"] = tempNode;
    loadedFonts["default"] = tempNode;


    loadedFonts["body"].update(font.getTable(titleFontNode));
    loadedFonts["title"].update(font.getTable(bodyFontNode));
    loadedFonts["default"].update(font.getTable(defaultFontNode));

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
        PRECISE_DEBUG << "Storing in ecs entity" << std::endl;
        _ecsEntities[typeid(GUI::ECS::Systems::Font)].push_back(node);
        PRECISE_DEBUG << "Stored in ecs entity" << std::endl;
        _baseId++;
    }
    PRETTY_INFO << "Value of the base id: " << std::to_string(_baseId) << std::endl;
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

    PRECISE_INFO << "Fetching loaded font for displaying a loading text on screen." << std::endl;
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> firstFontCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>, CustomExceptions::NoFont>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][0], true);
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
 * @brief Function in charge of displaying the main menu to the user before launching them into the game.
 *
 */
void Main::_mainMenu()
{

};

/**
 * @brief This is the function in charge of running the program's graphic logic.
 *
 * @return int The status of the overall execution of that section of the program.
 */
void Main::_mainLoop()
{
    // Get the window and event
    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> window_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][0], false);
    std::optional<std::shared_ptr<GUI::ECS::Systems::EventManager>> event_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::EventManager>>(_ecsEntities[typeid(GUI::ECS::Systems::EventManager)][0], false);

    if (!window_ptr.has_value()) {
        throw CustomExceptions::NoWindow("<std::any un-casting failed>");
    }
    GUI::ECS::Systems::Window &window = *window_ptr.value();
    if (!event_ptr.has_value()) {
        throw CustomExceptions::NoEventManager("<std::any un-casting failed>");
    }
    GUI::ECS::Systems::EventManager &event = *event_ptr.value();

    // Get the fonts

    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_title_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][0], false);
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_body_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][1], false);
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> font_default_ptr = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][2], false);

    if (!font_title_ptr.has_value()) {
        throw CustomExceptions::NoFont("Title font", "<std::any un-casting failed>");
    }
    if (!font_body_ptr.has_value()) {
        throw CustomExceptions::NoFont("Body font", "<std::any un-casting failed>");
    }
    if (!font_default_ptr.has_value()) {
        throw CustomExceptions::NoFont("Default font", "<std::any un-casting failed>");
    }
    GUI::ECS::Systems::Font &font_title = *font_title_ptr.value();
    GUI::ECS::Systems::Font &font_body = *font_body_ptr.value();
    GUI::ECS::Systems::Font &font_default = *font_default_ptr.value();

    std::vector<std::any> sprites = _ecsEntities[typeid(GUI::ECS::Components::SpriteComponent)];

    // Create a test text

    GUI::ECS::Components::TextComponent text(_baseId, font_body, "Sample Text", 40, GUI::ECS::Systems::Colour::Pink, GUI::ECS::Systems::Colour::Cyan, GUI::ECS::Systems::Colour::Yellow, { 20, 50 });
    _baseId++;

    // Create a test button

    GUI::ECS::Components::ShapeComponent rectangle(_baseId, { {200, 80}, {80,50} });
    _baseId++;
    GUI::ECS::Components::ButtonComponent button(_baseId, rectangle, text);
    button.setPosition({ 200,200 });
    button.setTextSize(20);
    _baseId++;

    // Create an image 
    GUI::ECS::Components::CollisionComponent col(0, 0, 0, 0, 0);
    GUI::ECS::Components::TextureComponent MyTexture(_baseId, std::string("./assets/img/r-typesheet3.gif"), col);
    GUI::ECS::Components::ImageComponent Image(_baseId, MyTexture, "testName", "application name");

    PRETTY_INFO << "Updating loading text to 'All the ressources have been loaded'." << std::endl;
    _updateLoadingText("All the ressources have been loaded.");
    PRETTY_INFO << "Updated loading text to 'All the ressources have been loaded'." << std::endl;

    while (window.isOpen()) {
        event.processEvents(window);
        _updateMouseForAllRendererables(event.getMouseInfo());
        if (event.isKeyPressed(GUI::ECS::Systems::Key::CapsLock)) {
            _testContent();
        }
        text.update(event.getMouseInfo());
        button.update(event.getMouseInfo());
        PRETTY_INFO << "Mouse position: " << Recoded::myToString(event.getMousePosition()) << std::endl;
        window.draw(text);
        window.draw(button);
        window.draw(Image);
        // int index = 0;
        // for (std::any spriteItem : sprites) {
        //     PRETTY_INFO << "Displaying sprite " << index << std::endl;
        //     std::optional<std::shared_ptr<GUI::ECS::Components::SpriteComponent>> spriteCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::SpriteComponent>>(spriteItem, false);
        //     if (!spriteCapsule.has_value()) {
        //         PRETTY_WARNING << "No sprite entity" << std::endl;
        //     } else {
        //         PRETTY_SUCCESS << "Sprite entity found" << std::endl;
        //         std::shared_ptr<GUI::ECS::Components::SpriteComponent> sprite = spriteCapsule.value();
        //         PRETTY_INFO << "Sprite component decapsulated" << std::endl;
        //         sprite->checkTick();
        //         PRETTY_INFO << "Ticked the sprite animation" << std::endl;
        //         sprite->setPosition({ index, index });
        //         PRETTY_INFO << "Moved the sprite to position " << Recoded::myToString<int>({ index, index }) << std::endl;
        //         // window.draw(*sprite);
        //         PRETTY_SUCCESS << "Sprite added to the render" << std::endl;
        //         index++;
        //     }
        // }
        window.display();
        window.clear();
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
    _initialiseConnection();
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
 * @brief Load a toml file into the program if it is present.
 *
 */
void Main::_loadToml()
{
    _tomlContent.setTOMLPath(_configFilePath);
}
