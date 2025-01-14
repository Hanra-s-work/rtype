/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Main.hpp
*/

/**
 * @file RealMain.hpp
 * @brief This is the file in charge of containing the main class and other ressources at the root of the program
 */

#pragma once
#include <any>
#include <map>
#include <tuple>
#include <memory>
#include <string>
#include <cctype> 
#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>
#include <typeindex>
#include <exception>
#include <stdexcept>
#include <functional>
#include <unordered_map>
#include <toml++/toml.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"
#include "TOMLLoader.hpp"
#include "ActiveScreen.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/Systems.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components.hpp"
#include "GUI/ECS/Systems/Colour.hpp"
#include "GUI/ECS/Systems/Window.hpp"
#include "GUI/ECS/Systems/EventManager.hpp"


 /**
  * @brief The Main class is the main class of the program.
  *
  */
class Main {
  public:
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
  Main(const std::string &ip = "127.0.0.1", unsigned int port = 5000, unsigned int windowWidth = 800, unsigned int windowHeight = 600, bool windowCursor = true, bool windowFullscreen = false, const std::string &windowTitle = "R-Type", unsigned int windowX = 0, unsigned int windowY = 0, const std::string &windowCursorIcon = "NULL", bool imageIsSprite = false, bool spriteStartTop = false, bool spriteStartLeft = false, unsigned int spriteWidth = 20, unsigned int spriteHeight = 20, unsigned int frameLimit = 60, const std::string &configFilePath = "client_config.toml", const bool log = false, const bool debug = false);
  ~Main();

  void run();

  // Setters 
  void setIp(const std::string &ip);
  void setPort(const unsigned int port);
  void setWindowWidth(unsigned int width);
  void setWindowCursor(bool cursorVisible);
  void setWindowHeight(unsigned int height);
  void setWindowFullscreen(bool fullscreen);
  void setWindowTitle(const std::string &title);
  void setWindowPositionX(unsigned int x);
  void setWindowPositionY(unsigned int y);
  void setWindowPosition(unsigned int x, unsigned int y);
  void setWindowCursorIcon(const std::string cursorImage);
  void setWindowCursorSprite(bool imageIsSprite);
  void setWindowCursorSpriteWidth(unsigned int spriteWidth);
  void setWindowCursorSpriteReadFromTop(bool spriteStartTop);
  void setWindowCursorSpriteHeight(unsigned int spriteHeight);
  void setWindowCursorSpriteReadFromLeft(bool spriteStartLeft);
  void setWindowSize(unsigned int width, unsigned int height);
  void setFrameLimit(unsigned int frameLimit);
  void setConfigFile(const std::string &configFile);
  void setLog(const bool debug);
  void setDebug(const bool debug);
  void setActiveScreen(const ActiveScreen screen);

  // Getters
  const std::string getIp();
  const unsigned int getPort();
  unsigned int  getWindowWidth();
  unsigned int getWindowHeight();
  bool getWindowCursor();
  bool getWindowFullscreen();
  const std::string &getWindowTitle();
  const std::string &getWindowCursorIcon();
  bool getWindowCursorSprite();
  bool getWindowCursorSpriteReadFromTop();
  bool getWindowCursorSpriteReadFromLeft();
  unsigned int getWindowCursorSpriteWidth();
  unsigned int getWindowCursorSpriteHeight();
  const bool getLog() const;
  const bool getDebug() const;
  unsigned int getFrameLimit() const;
  std::string getConfigFile() const;
  std::tuple<unsigned int, unsigned int> getWindowPosition();
  std::tuple<unsigned int, unsigned int> getWindowSize();
  const ActiveScreen getActiveScreen() const;
  const std::string getActiveScreenAsString() const;

  private:
  // Private helper methods
  void _loadToml();
  void _mainLoop();
  std::string _lowerText(const std::string &text);
  const bool _isIpInRange(const std::string &ip) const;
  const bool _isPortCorrect(const unsigned int port) const;
  const bool _isFilePresent(const std::string &filepath) const;
  const bool _isFrameLimitCorrect(const unsigned int frameLimit) const;
  const bool _isFontConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isIconConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isMusicConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isSpriteConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isBackgroundConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isKeyPresentAndOfCorrectType(const TOMLLoader &node, const std::string &key, const toml::node_type &valueType) const;

  /**
   * @brief Function in charge of retrieving the section corresponding to the provided key and return it as a TOMLLoader content.
   *
   * @tparam Exception The exception for an invalid format when the section is found.
   * @tparam ExceptionMissing The exception for a missing section.
   *
   * @param node The parent TOML content in which to search.
   * @param key The first probable name of the section.
   * @param keyAlt The second probable name of the section.
   *
   * @return const TOMLLoader The section extracted from the parent.
   *
   * @throws Exception The exception for an invalid format when the section is found
   * @throws ExceptionMissing The exception for when the section is not found.
   */
  template <typename Exception = CustomExceptions::InvalidFontConfiguration, typename ExceptionMissing = CustomExceptions::NoFontInConfigFile>
  const TOMLLoader _getTOMLNodeContent(const TOMLLoader &node, const std::string &key, const std::string &keyAlt)
  {
    TOMLLoader ItemNode(_tomlContent);
    const std::string tomlPath = _tomlContent.getTOMLPath();

    if (_tomlContent.hasKey(key)) {
      PRETTY_INFO << "Fetching the content for '" << key << "'." << std::endl;
      PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(key) << "'." << std::endl;
      if (_tomlContent.getValueType(key) == toml::node_type::table) {
        ItemNode = _tomlContent.getTable(key);
      } else {
        throw Exception(tomlPath, key, _tomlContent.getValueTypeAsString(key), _tomlContent.getTypeAsString(toml::node_type::table));
      }
    } else if (_tomlContent.hasKey(keyAlt)) {
      PRETTY_INFO << "Fetching the content for '" << keyAlt << "'." << std::endl;
      PRETTY_INFO << "Fetching the type of the content '" << _tomlContent.getValueTypeAsString(keyAlt) << "'." << std::endl;
      if (_tomlContent.getValueType(keyAlt) == toml::node_type::table) {
        ItemNode = _tomlContent.getTable(keyAlt);
      } else {
        throw Exception(tomlPath, keyAlt, _tomlContent.getValueTypeAsString(keyAlt), _tomlContent.getTypeAsString(toml::node_type::table));
      }
    } else {
      PRETTY_CRITICAL << "The key " << key << " is missing from the config file, " <<
        "the other supported key " << keyAlt << " wasn't found in the config file." << std::endl;
      throw ExceptionMissing(_tomlContent.getTOMLPath(), key);
    }

    PRETTY_DEBUG << ItemNode.getRawTOML() << std::endl;
    return ItemNode;
  }

  std::uint32_t _initialiseAudio();
  std::uint32_t _initialiseFonts();
  std::uint32_t _initialiseIcon();
  std::uint32_t _initialiseSprites();
  std::uint32_t _initialiseBackgrounds();

  void _initialiseConnection();
  void _initialiseRessources();

  void _updateLoadingText(const std::string &detail = "Loading...");

  void _updateMouseForAllRendererables(const GUI::ECS::Systems::MouseInfo &mouse);

  void _sendAllPackets();
  void _processIncommingPackets();

  // Ip string processing
  const std::string _getIpChunk(const unsigned int index, const std::string &defaultValue) const;

  // Text component fetching
  const std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> _getTextComponent(const std::string &textComponentKey);

  // Functions in charge of managing a node from an ipv4
  const std::string _incrementIpV4Node(const std::string &v4Section);
  const std::string _decrementIpV4Node(const std::string &v4Section);

  // Functions in charge of managing the port counter
  const std::string _incrementPortCounter(const std::string &portSection);
  const std::string _decrementPortCounter(const std::string &portSection);

  // Functions to increment a specific chunk of the address
  void _incrementIpChunkOne();
  void _incrementIpChunkTwo();
  void _incrementIpChunkThree();
  void _incrementIpChunkFour();
  void _incrementPortChunk();

  // Functions to decrement a specific chunk of the address
  void _decrementIpChunkOne();
  void _decrementIpChunkTwo();
  void _decrementIpChunkThree();
  void _decrementIpChunkFour();
  void _decrementPortChunk();

  // Function in charge of returning the Event manager
  const std::shared_ptr<GUI::ECS::Systems::EventManager> _getEventManager();

  // Function in charge of creating text components
  const std::shared_ptr<GUI::ECS::Components::TextComponent> _createText(const std::string &application, const std::string &name, const std::string &text, const GUI::ECS::Systems::Font &font, const unsigned int size = 40, const GUI::ECS::Systems::Colour &normal = GUI::ECS::Systems::Colour::Black, const GUI::ECS::Systems::Colour &hover = GUI::ECS::Systems::Colour::Black, const GUI::ECS::Systems::Colour &clicked = GUI::ECS::Systems::Colour::Black);

  // Function in charge of creating buttons
  const std::shared_ptr<GUI::ECS::Components::ButtonComponent> _createButton(const std::string &application, const std::string &title, std::function<void()> callback, const std::string &callbackName = "callback function", const int width = 40, const int height = 20, const int textSize = 20, const GUI::ECS::Systems::Colour &bg = GUI::ECS::Systems::Colour::Black, const GUI::ECS::Systems::Colour &normal = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &hover = GUI::ECS::Systems::Colour::Yellow, const GUI::ECS::Systems::Colour &clicked = GUI::ECS::Systems::Colour::AliceBlue, const std::shared_ptr<GUI::ECS::Systems::Font> &textFont = nullptr);

  // Functions in charge of extracting the x and y coordinates of the screen
  const unsigned int _getScreenCenterX();
  const unsigned int _getScreenCenterY();

  // Screens for the gui
  void _gameScreen();                //GAME
  void _demoScreen();                //DEMO
  void _settingsMenu();              //SETTINGS
  void _unknownScreen();             //when the enum does not cover it
  void _gameOverScreen();            //GAME_OVER
  void _gameWonScreen();             //GAME_WON
  void _mainMenuScreen();            //MENU
  void _bossFightScreen();           //BOSS_FIGHT
  void _connectionFailedScreen();    //CONNECTION_FAILED
  void _connectionAddressScreen();   //CONNECTION_ADDRESS

  // Function related to managing sub components in the windows

  // Action functions (functions used in button components)
  void _goPlay();              // Game screen
  void _goDemo();              // Demo screen
  void _goHome();              // Main menu screen
  void _goExit();              // Exit program
  void _goSettings();          // Settings screen
  void _goGameOver();          // Game over screen
  void _goGameWon();           // Game won screen
  void _goBossFight();         // Boss fight screen
  void _goUnknown();           // When the screen is unknown
  void _goConnectionFailed();  // Connection failed screen
  void _goConnect();           // Connection in progress (this function will redirect the user to either the game or the connection failed)
  void _goConnectionAddress(); // Connection changer screen


  // Musics

  // Main menu music
  void _startMainMenuMusic();
  void _stopMainMenuMusic();

  // Game loop music
  void _startGameLoopMusic();
  void _stopGameLoopMusic();

  // Boss fight music
  void _startBossFightMusic();
  void _stopBossFightMusic();

  // Sound effects

  void _shootSound();
  void _damageSound();
  void _deadSound();
  void _buttonSound();
  void _gameOverSound();
  void _winSound();


  void _testContent();

  void _closeConnection();

  // Private members

  // ecs entity holder
  std::unordered_map<std::type_index, std::vector<std::any>> _ecsEntities;

  // settings information
  std::string _ip;
  unsigned int _port;
  unsigned int _windowWidth;
  unsigned int _windowHeight;
  bool _windowCursor;
  bool _windowFullscreen;
  std::string _windowTitle;
  unsigned int _windowX;
  unsigned int _windowY;
  std::string _windowCursorIcon;
  bool _imageIsSprite;
  bool _spriteStartTop;
  bool _spriteStartLeft;
  bool _log;
  bool _debug;
  unsigned int _spriteWidth;
  unsigned int _spriteHeight;
  unsigned int _windowFrameLimit;

  // Variable in charge of setting the maximum allowed port range
  unsigned int _maximumPortRange = 64738;

  // Entity id tracking
  std::uint32_t _baseId = 0;

  // Configuration file information
  std::string _configFilePath = "client_config.toml";
  TOMLLoader _tomlContent;

  // ecs important indexes
  unsigned int _iconIndex = 0;
  unsigned int _loadingIndex = 0;
  unsigned int _mainEventIndex = 0;
  unsigned int _mainWindowIndex = 0;
  unsigned int _titleFontIndex = 0;
  unsigned int _bodyFontIndex = 0;
  unsigned int _defaultFontIndex = 0;
  unsigned int _buttonFontIndex = 0;

  // ecs important key
  std::string _mainMenuKey = "mainMenuButton";

  // Current screen in focus
  ActiveScreen _activeScreen = ActiveScreen::LOADING;

  // Music tracking variables
  bool _gameMusicStarted = false;
  bool _mainMenuMusicStarted = false;
  bool _bossFightMusicStarted = false;

  // Variable in charge of informing the gui if we are connected
  bool _connected = false;

  // Variables in charge of tracking the keys for the ip's
  const std::string _ipV4FirstChunkKey = "connectionAddressScreenIpV4FirstChunk";
  const std::string _ipV4SecondChunkKey = "connectionAddressScreenIpV4SecondChunk";
  const std::string _ipV4ThirdChunkKey = "connectionAddressScreenIpV4ThirdChunk";
  const std::string _ipV4FourthChunkKey = "connectionAddressScreenIpV4FourthChunk";
  const std::string _portV4ChunkKey = "connectionAddressScreenPortV4ChunkKey";
};

int RealMain(int argc, char **argv);
void DisplayHelp(const std::string binName);
void DisplayVersion(bool helpMode = false);
