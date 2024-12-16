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
    _spriteHeight(spriteHeight)
{
    _debug = debug;
    Debug::getInstance().setDebugEnabled(debug);
    Debug::getInstance() << "Processing ip" << std::endl;
    if (_isIpInRange(ip) == true) {
        _ip = ip;
    } else {
        throw MyException::IpIncorrect(ip);
    }
    Debug::getInstance() << "Processing port" << std::endl;
    if (_isPortCorrect(port) == true) {
        _port = port;
    } else {
        throw MyException::PortIncorrect(std::to_string(port));
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
bool Main::_isIpInRange(const std::string &ip)
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
bool Main::_isPortCorrect(const unsigned int port)
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
bool Main::_isFilePresent(const std::string &filepath)
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
bool Main::_isFrameLimitCorrect(unsigned int frameLimit)
{
    if (frameLimit < 10 || frameLimit > 1000) {
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
 *@brief This is the function in charge of initialise the default ressources for the class.
 *
 */
void Main::_initialiseRessources()
{
    std::shared_ptr<GUI::ECS::Utilities::Window> window = std::make_shared<GUI::ECS::Utilities::Window>(_windowWidth, _windowHeight, _windowTitle);
    std::shared_ptr<GUI::ECS::Utilities::EventManager> event = std::make_shared<GUI::ECS::Utilities::EventManager>();

    window->setFullScreen(_windowFullscreen);
    window->setFramerateLimit(_windowFrameLimit);

    _ecsEntities[typeid(GUI::ECS::Utilities::Window)].push_back(window);
    _ecsEntities[typeid(GUI::ECS::Utilities::EventManager)].push_back(event);
}

/**
 *@brief This is the function in charge of running the program's graphic logic.
 *
 * @return int The status of the overall execution of that section of the program.
 */
void Main::_mainLoop()
{
    std::shared_ptr<GUI::ECS::Utilities::Window> window_ptr = std::any_cast<std::shared_ptr<GUI::ECS::Utilities::Window>>(_ecsEntities[typeid(GUI::ECS::Utilities::Window)][0]);
    std::shared_ptr<GUI::ECS::Utilities::EventManager> event_ptr = std::any_cast<std::shared_ptr<GUI::ECS::Utilities::EventManager>>(_ecsEntities[typeid(GUI::ECS::Utilities::EventManager)][0]);

    GUI::ECS::Utilities::Window &window = *window_ptr;
    GUI::ECS::Utilities::EventManager &event = *event_ptr;

    while (window.isOpen()) {
        event.processEvents(window);
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
 * @throws MyException::IpIncorrect(ip) : This error is thrown
 * if the ip format is wrong.
 */
void Main::setIp(const std::string &ip)
{
    if (_isIpInRange(ip) == true) {
        _ip = ip;
    } else {
        throw MyException::IpIncorrect(ip);
    }
}

/**
 *@brief Set the port on which the GUI is going to connect to.
 *
 * @param port
 * @throws MyException::PortIncorrect(port) This error is thrown
 * if the port format is incorrect
 */
void Main::setPort(const unsigned int port)
{
    if (_isPortCorrect(port) == true) {
        _port = port;
    } else {
        throw MyException::PortIncorrect(std::to_string(port));
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
