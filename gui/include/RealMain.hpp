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
#include <memory>
#include <string>
#include <cctype> 
#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include <toml++/toml.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "Constants.hpp"
#include "TOMLLoader.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/Systems.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Utilities/Window.hpp"
#include "GUI/ECS/Utilities/EventManager.hpp"

 /**
  *@brief The Main class is the main class of the program.
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
   * @param debug Whether debug mode is enabled (default: false).
   */
  Main(const std::string &ip = "127.0.0.1", unsigned int port = 5000, unsigned int windowWidth = 800, unsigned int windowHeight = 600, bool windowCursor = true, bool windowFullscreen = false, const std::string &windowTitle = "R-Type", unsigned int windowX = 0, unsigned int windowY = 0, const std::string &windowCursorIcon = "NULL", bool imageIsSprite = false, bool spriteStartTop = false, bool spriteStartLeft = false, unsigned int spriteWidth = 20, unsigned int spriteHeight = 20, unsigned int frameLimit = 60, const std::string configFilePath = "client_config.toml", bool debug = false);
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
  void setDebug(bool debug);

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
  bool getDebug() const;
  unsigned int getFrameLimit() const;
  std::string getConfigFile() const;
  std::tuple<unsigned int, unsigned int> getWindowPosition();
  std::tuple<unsigned int, unsigned int> getWindowSize();

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
  const bool _isMusicConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isSpriteConfigurationCorrect(const TOMLLoader &node) const;
  const bool _isKeyPresentAndOfCorrectType(const TOMLLoader &node, const std::string &key, const toml::node_type &valueType) const;

  std::uint32_t _initialiseAudio();
  std::uint32_t _initialiseFonts();
  std::uint32_t _initialiseSprites();
  void _initialiseConnection();
  void _initialiseRessources();

  void _updateMouseForAllRendererables(const GUI::ECS::Utilities::MouseInfo &mouse);

  void _testContent();

  void _closeConnection();

  // Private members
  std::unordered_map<std::type_index, std::vector<std::any>> _ecsEntities;
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
  bool _debug;
  unsigned int _spriteWidth;
  unsigned int _spriteHeight;
  unsigned int _windowFrameLimit;
  std::uint32_t _baseId = 0;
  std::string _configFilePath = "client_config.toml";
  TOMLLoader _tomlContent;
};

int RealMain(int argc, char **argv);
void DisplayHelp(const std::string binName);
void DisplayVersion(bool helpMode = false);
