/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MainClass.cpp
*/

/**
 * @file MainClass.cpp
 * @brief This is the file in charge of containing the class Main of the program.
 */

#include <cstdint>
#include <sstream>
#include <fstream>
#include "RealMain.hpp"

 /**
  *@brief Construct a new Main:: Main object
  *
  * @param ip
  * @param port
  * @param windowWidth
  * @param windowHeight
  * @param windowCursor
  * @param windowFullscreen
  * @param windowTitle
  * @param windowX
  * @param windowY
  * @param windowCursorIcon
  * @param imageIsSprite
  * @param spriteStartTop
  * @param spriteStartLeft
  * @param spriteWidth
  * @param spriteHeight
  * @param frameLimit
  * @param configFilePath
  * @param debug
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
    const std::string configFilePath,
    bool debug
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
    _debug = debug;
    Debug::getInstance().setDebugEnabled(debug);
    Debug::getInstance() << "Processing ip" << std::endl;
    if (_isIpInRange(ip) == true) {
        _ip = ip;
    } else {
        throw MyException::InvalidIp(ip);
    }
    Debug::getInstance() << "Processing port" << std::endl;
    if (_isPortCorrect(port) == true) {
        _port = port;
    } else {
        throw MyException::InvalidPort(std::to_string(port));
    }
    Debug::getInstance() << "Processing cursor icon" << std::endl;
    std::string windowText = _lowerText(windowCursorIcon);
    if (windowText.empty() || windowText == "null" || windowText == "none") {
        _windowCursorIcon = "";
    } else if (_isFilePresent(windowCursorIcon) == true) {
        _windowCursorIcon = windowCursorIcon;
    } else {
        throw MyException::FileNotFound(windowCursorIcon);
    }
    Debug::getInstance() << "Processing frame limit" << std::endl;
    if (_isFrameLimitCorrect(frameLimit)) {
        _windowFrameLimit = frameLimit;
    } else {
        throw MyException::InvalidFrameLimit(frameLimit);
    }
    Debug::getInstance() << "End of processing" << std::endl;
}

/**
 *@brief Destroy the Main:: Main object
 *
 */
Main::~Main() {}

/**
 *@brief Function in charge of converting a string of characters
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
 *@brief Check if the provided file path is present and can be opened.
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
 *@brief The function in charge of checking if the provided frame limit is correct.
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
 *@brief Check if a font configuration is correct.
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
 *@brief Check if a music configuration is correct.
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
 *@brief Check if a sprite configuration is correct.
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
 *@brief This is a generic function that will check if a given key is present and that the type of the value is correct.
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
 *@brief The function in charge of initialising the connection to the server.
 *
 * @return int
 */
void Main::_initialiseConnection()
{
    std::string address = _ip + ":" + std::to_string(_port);

    if (SUCCESS != SUCCESS) {
        throw MyException::ConnectionFailed(address);
    }
}

/**
 *@brief Close the connection with the server.
 *
 */
void Main::_closeConnection()
{

}


/**
 *@brief This is the function in charge of loading the Sprites and Spritesheets into the program.
 *
 */
void Main::_initialiseSprites()
{
    TOMLLoader sprites(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string spriteSheetKey = "spritesheets";
    const std::string spriteSheetKeyAlt = "spritesheet";
    std::unordered_map<std::string, std::string> spritesheets;

    if (_tomlContent.hasKey(spriteSheetKey)) {
        Debug::getInstance() << "Fetching the content for '" << spriteSheetKey << "'." << std::endl;
        Debug::getInstance() << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(spriteSheetKey) << "'." << std::endl;
        if (_tomlContent.getValueType(spriteSheetKey) == toml::node_type::table) {
            sprites = _tomlContent.getTable(spriteSheetKey);
        } else {
            throw MyException::InvalidConfigurationSpritesheetType(tomlPath, spriteSheetKey, _tomlContent.getValueTypeAsString(spriteSheetKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else if (_tomlContent.hasKey(spriteSheetKeyAlt)) {
        Debug::getInstance() << "Fetching the content for '" << spriteSheetKeyAlt << "'." << std::endl;
        Debug::getInstance() << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(spriteSheetKeyAlt) << "'." << std::endl;
        if (_tomlContent.getValueType(spriteSheetKey) == toml::node_type::table) {
            sprites = _tomlContent.getTable(spriteSheetKey);
        } else {
            throw MyException::InvalidConfigurationSpritesheetType(tomlPath, spriteSheetKeyAlt, _tomlContent.getValueTypeAsString(spriteSheetKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else {
        Debug::getInstance() << "The key " << spriteSheetKey << " is missing from the config file, " <<
            "the other supported key " << spriteSheetKeyAlt << " wasn't found in the config file." << std::endl;
        throw MyException::NoSpritesInConfigFile(_tomlContent.getTOMLPath(), spriteSheetKey);
    }

    Debug::getInstance() << "Table data fetched: '" << sprites.getRawTOML() << "'." << std::endl;

    spritesheets["r-typesheet1"] = "assets/img/r-typesheet1.gif";

    bool startTop = true;
    bool startLeft = true;
    unsigned int frameWidth = 0;
    unsigned int frameHeight = 0;

    for (const auto &[name, info] : spritesheets) {
        std::string path = info;
        GUI::ECS::Components::CollisionComponent collision(_baseId);
        collision.setHeight(frameWidth);
        collision.setWidth(frameHeight);
        GUI::ECS::Components::AnimationComponent animation(_baseId);
        animation.setAnimation(path, frameWidth, frameHeight, startLeft, startTop);
        std::shared_ptr<GUI::ECS::Components::SpriteComponent> nodeSprite = std::make_shared<GUI::ECS::Components::SpriteComponent>(_baseId, name, collision, animation);
        _baseId++;
    }
}

/**
 *@brief This is the function in charge of loading the audios into the program.
 *
 */
void Main::_initialiseAudio()
{
    TOMLLoader audio(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string musicKey = "music";
    const std::string musicKeyAlt = "musics";
    std::unordered_map<std::string, std::string> audios;

    if (_tomlContent.hasKey(musicKey)) {
        Debug::getInstance() << "Fetching the content for '" << musicKey << "'." << std::endl;
        Debug::getInstance() << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(musicKey) << "'." << std::endl;
        if (_tomlContent.getValueType(musicKey) == toml::node_type::table) {
            audio = _tomlContent.getTable(musicKey);
        } else {
            throw MyException::InvalidConfigurationMusicType(tomlPath, musicKey, _tomlContent.getValueTypeAsString(musicKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else if (_tomlContent.hasKey(musicKeyAlt)) {
        Debug::getInstance() << "Fetching the content for '" << musicKeyAlt << "'." << std::endl;
        Debug::getInstance() << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(musicKeyAlt) << "'." << std::endl;
        if (_tomlContent.getValueType(musicKey) == toml::node_type::table) {
            audio = _tomlContent.getTable(musicKey);
        } else {
            throw MyException::InvalidConfigurationMusicType(tomlPath, musicKeyAlt, _tomlContent.getValueTypeAsString(musicKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else {
        Debug::getInstance() << "The key " << musicKey << " is missing from the config file, " <<
            "the other supported key " << musicKeyAlt << " wasn't found in the config file." << std::endl;
        throw MyException::NoMusicInConfigFile(_tomlContent.getTOMLPath(), musicKey);
    }

    Debug::getInstance() << audio.getRawTOML() << std::endl;


    std::string mainMenuPath = "assets/audio/2019-12-11_-_Retro_Platforming_-_David_Fesliyan.ogg";
    std::string bossFightPath = "assets/audio/2021-08-30_-_Boss_Time_-_www.FesliyanStudios.com.ogg";
    std::string gameLoopPath = "assets/audio/FASTER-2020-03-22_-_A_Bit_Of_Hope_-_David_Fesliyan.ogg";
    std::string shootingPath = "assets/audio/Laser-A1-www.fesliyanstudios.com.ogg";
    std::string damagePath = "assets/audio/Undertale_Damage_Sound_Effect.ogg";
    std::string deadPath = "assets/audio/Bomb-Explosion-Big-www.fesliyanstudios.com.ogg";
    std::string buttonPath = "assets/audio/Game-Menu-Selection-Z-www.fesliyanstudios.com.ogg";
    std::string gameOverPath = "assets/audio/game-over-arcade.ogg";
    std::string successPath = "assets/audio/success-fanfare-trumpets-6185.ogg";

    std::shared_ptr<GUI::ECS::Components::MusicComponents> mainMenu = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, mainMenuPath, "Main Menu");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> bossFight = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, bossFightPath, "Boss Fight");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> gameLoop = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, gameLoopPath, "Game Loop");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> shooting = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, shootingPath, "Shooting");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> damage = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, damagePath, "Damage");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> dead = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, deadPath, "Dead");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> button = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, buttonPath, "Button");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> gameOver = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, gameOverPath, "Game Over");
    _baseId++;
    std::shared_ptr<GUI::ECS::Components::MusicComponents> success = std::make_shared<GUI::ECS::Components::MusicComponents>(_baseId, successPath, "Success");
    _baseId++;


    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(mainMenu);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(bossFight);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(gameLoop);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(shooting);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(damage);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(dead);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(button);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(gameOver);
    _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)].push_back(success);
}

/**
 *@brief This is the function in charge of loading the fonts into the program.
 *
 */
void Main::_initialiseFonts()
{
    TOMLLoader font(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();
    const std::string fontKey = "font";
    const std::string fontKeyAlt = "fonts";
    std::unordered_map<std::string, std::string> fonts;

    if (_tomlContent.hasKey(fontKey)) {
        Debug::getInstance() << "Fetching the content for '" << fontKey << "'." << std::endl;
        Debug::getInstance() << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(fontKey) << "'." << std::endl;
        if (_tomlContent.getValueType(fontKey) == toml::node_type::table) {
            font = _tomlContent.getTable(fontKey);
        } else {
            throw MyException::InvalidConfigurationFontType(tomlPath, fontKey, _tomlContent.getValueTypeAsString(fontKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else if (_tomlContent.hasKey(fontKeyAlt)) {
        Debug::getInstance() << "Fetching the content for '" << fontKeyAlt << "'." << std::endl;
        Debug::getInstance() << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(fontKeyAlt) << "'." << std::endl;
        if (_tomlContent.getValueType(fontKey) == toml::node_type::table) {
            font = _tomlContent.getTable(fontKey);
        } else {
            throw MyException::InvalidConfigurationFontType(tomlPath, fontKeyAlt, _tomlContent.getValueTypeAsString(fontKey), _tomlContent.getTypeAsString(toml::node_type::table));
        }
    } else {
        Debug::getInstance() << "The key " << fontKey << " is missing from the config file, " <<
            "the other supported key " << fontKeyAlt << " wasn't found in the config file." << std::endl;
        throw MyException::NoFontInConfigFile(_tomlContent.getTOMLPath(), fontKey);
    }

    Debug::getInstance() << font.getRawTOML() << std::endl;

    const std::string titleFontNode = "title";
    const std::string bodyFontNode = "body";
    const std::string defaultFontNode = "default";

    if (!font.hasKey(titleFontNode)) {
        throw MyException::NoTitleFontConfiguration(tomlPath);
    }
    if (!font.hasKey(bodyFontNode)) {
        throw MyException::NoBodyFontConfiguration(tomlPath);
    }
    if (!font.hasKey(defaultFontNode)) {
        throw MyException::NoDefaultFontConfiguration(tomlPath);
    }


    TOMLLoader titleData(font);
    TOMLLoader bodyData(font);
    TOMLLoader defaultData(font);

    titleData.update(font.getTable(titleFontNode));
    bodyData.update(font.getTable(bodyFontNode));
    defaultData.update(font.getTable(defaultFontNode));

    if (!_isFontConfigurationCorrect(titleData)) {
        const std::string userConfig = titleData.getTOMLString();
        const std::string fontName = titleFontNode;
        throw MyException::InvalidFontConfiguration(userConfig, fontName);
    }
    if (!_isFontConfigurationCorrect(bodyData)) {
        const std::string userConfig = bodyData.getTOMLString();
        const std::string fontName = bodyFontNode;
        throw MyException::InvalidFontConfiguration(userConfig, fontName);
    }
    if (!_isFontConfigurationCorrect(defaultData)) {
        const std::string userConfig = defaultData.getTOMLString();
        const std::string fontName = defaultFontNode;
        throw MyException::InvalidFontConfiguration(userConfig, fontName);
    }

    std::string titleFontPath = "assets/font/Blox/TTF Fonts/Blox.ttf";
    std::shared_ptr<GUI::ECS::Utilities::Font> titleFont = std::make_shared<GUI::ECS::Utilities::Font>(_baseId, "Color Basic", titleFontPath);
    _baseId++;

    _ecsEntities[typeid(GUI::ECS::Utilities::Font)].push_back(titleFont);
}

/**
 *@brief This is the function in charge of initialise the default ressources for the class.
 *
 */
void Main::_initialiseRessources()
{
    std::uint32_t _baseId = 0;
    _ecsEntities.clear();

    Debug::getInstance() << "========================== Displaying loaded toml data. ==========================" << std::endl;
    _tomlContent.printTOML();
    Debug::getInstance() << "========================== Displayed loaded toml data.  ==========================" << std::endl;

    std::shared_ptr<GUI::ECS::Utilities::Window> window = std::make_shared<GUI::ECS::Utilities::Window>(_baseId, _windowWidth, _windowHeight, _windowTitle);
    _baseId++;
    std::shared_ptr<GUI::ECS::Utilities::EventManager> event = std::make_shared<GUI::ECS::Utilities::EventManager>(_baseId);
    _baseId++;

    window->setFullScreen(_windowFullscreen);
    window->setFramerateLimit(_windowFrameLimit);

    _ecsEntities[typeid(GUI::ECS::Utilities::Window)].push_back(window);
    _ecsEntities[typeid(GUI::ECS::Utilities::EventManager)].push_back(event);

    _initialiseSprites();
    _initialiseAudio();
    _initialiseFonts();
}

void Main::_testContent()
{
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponents)];

    for (unsigned int index = 0; index < musics.size(); index++) {
        std::shared_ptr<GUI::ECS::Components::MusicComponents> music_ptr = std::any_cast<std::shared_ptr<GUI::ECS::Components::MusicComponents>>(musics[index]);
        Debug::getInstance() << "Playing " << music_ptr->getMusicName() << " audio." << std::endl;
        music_ptr->play();
    }
}

/**
 *@brief This is the function in charge of running the program's graphic logic.
 *
 * @return int The status of the overall execution of that section of the program.
 */
void Main::_mainLoop()
{
    std::vector<sf::Keyboard::Key> keys;
    std::shared_ptr<GUI::ECS::Utilities::Window> window_ptr = std::any_cast<std::shared_ptr<GUI::ECS::Utilities::Window>>(_ecsEntities[typeid(GUI::ECS::Utilities::Window)][0]);
    std::shared_ptr<GUI::ECS::Utilities::EventManager> event_ptr = std::any_cast<std::shared_ptr<GUI::ECS::Utilities::EventManager>>(_ecsEntities[typeid(GUI::ECS::Utilities::EventManager)][0]);

    GUI::ECS::Utilities::Window &window = *window_ptr;
    GUI::ECS::Utilities::EventManager &event = *event_ptr;

    while (window.isOpen()) {
        event.processEvents(window);
        if (event.isKeyPressed(GUI::ECS::Utilities::Key::T)) {
            _testContent();
        }
        window.clear();
        window.display();
    }
}

/**
 *@brief This is the function used to start the program's main section.
 *
 * @return int The status of the execution of that section of the program.
 */
void Main::run()
{
    _initialiseConnection();
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
 * @throws MyException::IncorrectIp(ip) : This error is thrown
 * if the ip format is wrong.
 */
void Main::setIp(const std::string &ip)
{
    if (_isIpInRange(ip) == true) {
        _ip = ip;
    } else {
        throw MyException::InvalidIp(ip);
    }
}

/**
 *@brief Set the port on which the GUI is going to connect to.
 *
 * @param port
 * @throws MyException::InvalidPort(port) This error is thrown
 * if the port format is incorrect
 */
void Main::setPort(const unsigned int port)
{
    if (_isPortCorrect(port) == true) {
        _port = port;
    } else {
        throw MyException::InvalidPort(std::to_string(port));
    }
}

/**
 *@brief Set the width of the window.
 *
 * @param width
 */
void Main::setWindowWidth(unsigned int width)
{
    _windowWidth = width;
}

/**
 *@brief Set the height of the window.
 *
 * @param height
 */
void Main::setWindowHeight(unsigned int height)
{
    _windowHeight = height;
}

/**
 *@brief Set if the cursor is visible when in the window.
 *
 * @param cursorVisible
 */
void Main::setWindowCursor(bool cursorVisible)
{
    _windowCursor = cursorVisible;
}

/**
 *@brief Start the window in full screen mode.
 *
 * @param fullscreen
 */
void Main::setWindowFullscreen(bool fullscreen)
{
    _windowFullscreen = fullscreen;
}

/**
 *@brief Set the title of the window.
 *
 * @param title
 */
void Main::setWindowTitle(const std::string &title)
{
    _windowTitle = title;
}

/**
 *@brief Set the position of the window.
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
 *@brief Set the icon of the cursor
 * (if the user wishes to change the default icon)
 *
 * @param cursorImage
 * @throws MyException::FileNotFound(cursorImage) This error is thrown
 * if the path to the file is invalid or the file cannot be opened.
 */
void Main::setWindowCursorIcon(const std::string cursorImage)
{
    if (cursorImage == "" || cursorImage == "NULL") {
        _windowCursorIcon = nullptr;
    } else if (_isFilePresent(cursorImage) == true) {
        _windowCursorIcon = cursorImage;
    } else {
        throw MyException::FileNotFound(cursorImage);
    }
}

/**
 *@brief Set if the image passed is of type sprite or not.
 *
 * @param imageIsSprite
 */
void Main::setWindowCursorSprite(bool imageIsSprite)
{
    _imageIsSprite = imageIsSprite;
}

/**
 *@brief Set the height for the sprite's overlay texture,
 * which is used to draw the sprite's texture during animation.
 *
 * @param spriteWidth
 */
void Main::setWindowCursorSpriteWidth(unsigned int spriteWidth)
{
    _spriteWidth = spriteWidth;
}

/**
 *@brief Inform if the animation should start from the top.
 *
 * @param spriteStartTop
 */
void Main::setWindowCursorSpriteReadFromTop(bool spriteStartTop)
{
    _spriteStartTop = spriteStartTop;
}

/**
 *@brief Inform if the animation should start from the left.
 *
 * @param spriteStartLeft
 */
void Main::setWindowCursorSpriteReadFromLeft(bool spriteStartLeft)
{
    _spriteStartLeft = spriteStartLeft;
}

/**
 *@brief Set the height for the sprite's overlay texture,
 * which is used to draw the sprite's texture during animation.
 *
 * @param spriteHeight
 */
void Main::setWindowCursorSpriteHeight(unsigned int spriteHeight)
{
    _spriteHeight = spriteHeight;
}

/**
 *@brief The window width and height that will be created.
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
 *@brief The function in charge of setting the frame Limit
 *
 * @param frameLimit
 */
void Main::setFrameLimit(unsigned int frameLimit)
{
    if (_isFrameLimitCorrect(frameLimit) == false) {
        throw MyException::InvalidFrameLimit(frameLimit);
    }
    _windowFrameLimit = frameLimit;
}

/**
 *@brief This is the function in charge of seting the config filepath.
 *
 * @param configFile
 */
void Main::setConfigFile(const std::string &configFile)
{
    _configFilePath = configFile;
    _loadToml();
}

/**
 *@brief Toggle the debug mode for the program.
 *
 * @param debug
 */
void Main::setDebug(bool debug)
{
    _debug = debug;
    Debug::getInstance().setDebugEnabled(debug);
}

/**
 *@brief Get the value of the ip that was set.
 *
 * @return const std::string
 */
const std::string Main::getIp()
{
    return _ip;
}

/**
 *@brief Get the value of the port.
 *
 * @return const unsigned int
 */
const unsigned int Main::getPort()
{
    return _port;
}

/**
 *@brief Get the value of the window width.
 *
 * @return unsigned int
 */
unsigned int  Main::getWindowWidth()
{
    return _windowWidth;
}

/**
 *@brief Get the value of the window height.
 *
 * @return unsigned int
 */
unsigned int Main::getWindowHeight()
{
    return _windowHeight;
}

/**
 *@brief Get the status of the window cursor.
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursor()
{
    return _windowCursor;
}

/**
 *@brief Get the status of the window (if it is in fullscreen)
 *
 * @return true
 * @return false
 */
bool Main::getWindowFullscreen()
{
    return _windowFullscreen;
}

/**
 *@brief Get the title of the window.
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
 *@brief Get the status if the cursor is of type image or spritesheet
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursorSprite()
{
    return _imageIsSprite;
}

/**
 *@brief Get if the program is supposed to read from the top or not.
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursorSpriteReadFromTop()
{
    return _spriteStartTop;
}

/**
 *@brief Get if the program is supposed to read from the left or the rigth.
 *
 * @return true
 * @return false
 */
bool Main::getWindowCursorSpriteReadFromLeft()
{
    return _spriteStartLeft;
}

/**
 *@brief Get the width of the sprite texture.
 *
 * @return unsigned int
 */
unsigned int Main::getWindowCursorSpriteWidth()
{
    return _spriteWidth;
}

/**
 *@brief Get the height of the sprite texture.
 *
 * @return unsigned int
 */
unsigned int Main::getWindowCursorSpriteHeight()
{
    return _spriteHeight;
}

/**
 *@brief The function in charge of returning the status of the debug variable.
 *
 * @return true
 * @return false
 */
bool Main::getDebug() const
{
    return _debug;
}


/**
 *@brief Function in charge of returning the current frame limit.
 *
 * @return unsigned int
 */
unsigned int Main::getFrameLimit() const
{
    return _windowFrameLimit;
}


/**
 *@brief Function in charge of returning the path to the config file.
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
 *@brief Load a toml file into the program if it is present.
 *
 */
void Main::_loadToml()
{
    _tomlContent.setTOMLPath(_configFilePath);
}
