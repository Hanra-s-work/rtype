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
        PRECISE_DEBUG << "Storing in ecs entity" << std::endl;
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
        PRECISE_DEBUG << "Stored in ecs entity" << std::endl;
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

    PRECISE_INFO << "Fetching loaded font for displaying a loading text on screen." << std::endl;
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

};

/**
 * @brief Function in charge of processing (treating) all the packets that have
 * been received into actions that can be understood by the program.
 *
 */
void Main::_processIncommingPackets()
{

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
const std::shared_ptr<GUI::ECS::Components::ButtonComponent> Main::_createButton(const std::string &application, const std::string &title, std::function<void()> callback, const std::string &callbackName, const int width, const int height, const int textSize, const GUI::ECS::Systems::Colour &bg, const GUI::ECS::Systems::Colour &normal, const GUI::ECS::Systems::Colour &hover, const GUI::ECS::Systems::Colour &clicked)
{
    const std::string errMsgFont = "<Required font not found for the text of the button>, system error: ";
    std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> fontInstance = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>, CustomExceptions::NoFont>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], true, errMsgFont);
    if (!fontInstance.has_value()) {
        PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the unknown screen screen." << std::endl;
        throw CustomExceptions::NoFont(errMsgFont);
    }
    std::shared_ptr<GUI::ECS::Components::ShapeComponent> shapeItem = std::make_shared<GUI::ECS::Components::ShapeComponent>(_baseId);
    _baseId += 1;
    shapeItem->setShape(std::pair<float, float>(width, height));
    shapeItem->setNormalColor(bg);
    shapeItem->setHoverColor(bg);
    shapeItem->setClickedColor(bg);
    shapeItem->setApplication(application);

    std::shared_ptr<GUI::ECS::Components::TextComponent> textItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(fontInstance.value()), title, textSize, normal, hover, clicked);
    textItem->setApplication(application);
    _baseId += 1;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> buttonItem = std::make_shared<GUI::ECS::Components::ButtonComponent>(_baseId, *shapeItem, *textItem);
    buttonItem->setCallback(callback, callbackName);
    buttonItem->setApplication(application);
    _baseId += 1;
    _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(textItem);
    _ecsEntities[typeid(GUI::ECS::Components::ShapeComponent)].push_back(shapeItem);
    _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)].push_back(buttonItem);
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

}

void Main::_demoScreen()
{

}

void Main::_settingsMenu()
{

}

void Main::_unknownScreen()
{
    bool bodyTextFound = false;
    bool titleTextFound = false;
    bool homeButtonFound = false;

    const std::string titleKey = "unknownScreenTitle";
    const std::string bodyKey = "unknownScreenBody";

    std::shared_ptr<GUI::ECS::Components::TextComponent> body;
    std::shared_ptr<GUI::ECS::Components::TextComponent> title;
    std::shared_ptr<GUI::ECS::Components::ButtonComponent> homeItem;

    std::vector<std::any> texts = _ecsEntities[typeid(GUI::ECS::Components::TextComponent)];
    std::vector<std::any> buttons = _ecsEntities[typeid(GUI::ECS::Components::ButtonComponent)];

    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }


    for (std::any textCast : texts) {
        std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> textCapsule = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::TextComponent>>(textCast, false);
        if (textCapsule) {
            if (textCapsule.value()->getApplication() == titleKey) {
                titleTextFound = true;
                title = textCapsule.value();
            } else if (textCapsule.value()->getApplication() == bodyKey) {
                bodyTextFound = true;
                body = textCapsule.value();
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
        title = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(titleFont.value()), "Uh Oh!");
        title->setApplication(titleKey);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(title);
        _baseId += 1;
    }

    if (!bodyTextFound) {
        std::optional<std::shared_ptr<GUI::ECS::Systems::Font>> bodyFont = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Font>>(_ecsEntities[typeid(GUI::ECS::Systems::Font)][_bodyFontIndex], false);
        if (!bodyFont.has_value()) {
            PRETTY_CRITICAL << "There is no font to be extracted for creating the body text of the unknown screen screen." << std::endl;
            return;
        }
        body = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(bodyFont.value()), "It seems like you have landed on an unknown page.");
        body->setApplication(bodyKey);
        _ecsEntities[typeid(GUI::ECS::Components::TextComponent)].push_back(body);
        _baseId += 1;
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

    title->setPosition({ posx, posy });
    body->setPosition({ posx, posy + 20 });
    homeItem->setPosition({ posx, posy + 40 });
    PRETTY_DEBUG << "Component's positions updated for the current screen." << std::endl;
    win.value()->draw(*title);
    win.value()->draw(*body);
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

    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }

    PRECISE_DEBUG << "Fetching the text components if present." << std::endl;
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
    PRECISE_DEBUG << "Fetched the text components that were present." << std::endl;

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

    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
    }

    PRECISE_DEBUG << "Fetching the text components if present." << std::endl;
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
    PRECISE_DEBUG << "Fetched the text components that were present." << std::endl;

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
        bodyItem = std::make_shared<GUI::ECS::Components::TextComponent>(_baseId, *(bodyFont.value()), "You have won !", 20);
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

    std::optional<std::shared_ptr<GUI::ECS::Systems::Window>> win = Utilities::unCast<std::shared_ptr<GUI::ECS::Systems::Window>, CustomExceptions::NoWindow>(_ecsEntities[typeid(GUI::ECS::Systems::Window)][_mainWindowIndex], true, "<No window to render on>");
    if (!win.has_value()) {
        PRETTY_CRITICAL << "There is no window to draw on." << std::endl;
        throw CustomExceptions::NoWindow("<There was no window found on which components could be rendered>");
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
                onlineGameKey, "Online Game", std::bind(&Main::_goPlay, this), "_goPlay", buttonWidth, buttonHeight, textSize, bg, normal, hover, clicked
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

}

void Main::_connectionFailedScreen()
{

}

void Main::_connectionAddressScreen()
{

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
 * @brief Switches the active screen to a connection address input screen.
 *
 * Sets the active screen to @c ActiveScreen::CONNECTION_ADDRESS, allowing the user to input a connection address.
 */
void Main::_goConnectionAddress()
{
    setActiveScreen(ActiveScreen::CONNECTION_ADDRESS);
};

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
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "shooting" ||
            node.value()->getMusicName() == "shooting" ||
            node.value()->getApplication() == "Shooting" ||
            node.value()->getMusicName() == "Shooting"
            ) {
            node.value()->setLoopMusic(false);
            node.value()->play();
        }
    }
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
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "damage" ||
            node.value()->getMusicName() == "damage" ||
            node.value()->getApplication() == "Damage" ||
            node.value()->getMusicName() == "Damage"
            ) {
            node.value()->setLoopMusic(false);
            node.value()->play();
        }
    }
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
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "dead" ||
            node.value()->getMusicName() == "dead" ||
            node.value()->getApplication() == "Dead" ||
            node.value()->getMusicName() == "Dead"
            ) {
            node.value()->setLoopMusic(false);
            node.value()->play();
        }
    }
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
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "button" ||
            node.value()->getMusicName() == "button" ||
            node.value()->getApplication() == "Button" ||
            node.value()->getMusicName() == "Button"
            ) {
            node.value()->setLoopMusic(false);
            node.value()->play();
        }
    }
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
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "gameOver" ||
            node.value()->getMusicName() == "gameOver" ||
            node.value()->getApplication() == "Game Over" ||
            node.value()->getMusicName() == "Game Over"
            ) {
            node.value()->setLoopMusic(false);
            node.value()->play();
        }
    }
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
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "success" ||
            node.value()->getMusicName() == "success" ||
            node.value()->getApplication() == "Success" ||
            node.value()->getMusicName() == "Success"
            ) {
            node.value()->setLoopMusic(false);
            node.value()->play();
        }
    }
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

    // setActiveScreen(ActiveScreen::MENU);
    setActiveScreen(ActiveScreen::GAME_WON);

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
        event->processEvents(*window);
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
        } else if (_activeScreen == ActiveScreen::DEMO) {
            PRETTY_DEBUG << "Demo screen components are going to be set to be displayed" << std::endl;
            _demoScreen();
            PRETTY_SUCCESS << "Demo screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::LOADING) {
            PRETTY_DEBUG << "Update loading text screen components are going to be set to be displayed" << std::endl;
            _updateLoadingText("Apparently we are loading something...");
            PRETTY_SUCCESS << "Update loading text screen components are set to be displayed" << std::endl;
        } else if (_activeScreen == ActiveScreen::EXIT) {
            PRETTY_INFO << "Exit choice detected, stopping" << std::endl;
            window->close();
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
 * @brief Function in charge of updating the type of screen that is supposed
 * to be displayed as well as change the music based on the active screen.
 *
 * @param screen of type Active screen which informs the program of the current
 * screen type that needs to be processed.
 */
void Main::setActiveScreen(const ActiveScreen screen)
{
    _activeScreen = screen;
    PRETTY_DEBUG << "Setting active screen to: '" << getActiveScreenAsString() << "'." << std::endl;
    if (screen == ActiveScreen::MENU || screen == ActiveScreen::SETTINGS || screen == ActiveScreen::CONNECTION_ADDRESS) {
        PRETTY_DEBUG << "We're not in game nor in a boss fight, switching to menu music." << std::endl;
        _startMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
    } else if (screen == ActiveScreen::GAME || screen == ActiveScreen::DEMO) {
        PRETTY_DEBUG << "Were gaming, swithing to game music." << std::endl;
        _stopMainMenuMusic();
        _startGameLoopMusic();
        _stopBossFightMusic();
    } else if (screen == ActiveScreen::BOSS_FIGHT) {
        PRETTY_DEBUG << "Boss fight!, switching to boss fight music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _startBossFightMusic();
    } else if (screen == ActiveScreen::GAME_WON) {
        PRETTY_DEBUG << "Game won!, switching to game won music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
        _winSound();
    } else if (screen == ActiveScreen::GAME_OVER) {
        PRETTY_DEBUG << "Game won!, switching to game won music." << std::endl;
        _stopMainMenuMusic();
        _stopGameLoopMusic();
        _stopBossFightMusic();
        _deadSound();
        _gameOverSound();
    } else if (screen == ActiveScreen::CONNECTION_FAILED) {
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
 * @brief Load a toml file into the program if it is present.
 *
 */
void Main::_loadToml()
{
    _tomlContent.setTOMLPath(_configFilePath);
}
