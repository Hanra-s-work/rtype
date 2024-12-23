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
#include "Debug.hpp"
#include "Constants.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/Systems.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components.hpp"
#include "GUI/ECS/Utilities/Window.hpp"
#include "GUI/ECS/Utilities/EventManager.hpp"

 /**
  *@brief The Main class is the main class of the program.
  *
  */
class Main {
  public:
  Main(const std::string &ip = "127.0.0.1", unsigned int port = 5000, unsigned int windowWidth = 800, unsigned int windowHeight = 600, bool windowCursor = true, bool windowFullscreen = false, const std::string &windowTitle = "R-Type", unsigned int windowX = 0, unsigned int windowY = 0, const std::string &windowCursorIcon = "NULL", bool imageIsSprite = false, bool spriteStartTop = false, bool spriteStartLeft = false, unsigned int spriteWidth = 20, unsigned int spriteHeight = 20, unsigned int frameLimit = 60, bool debug = false);
  ~Main();
  void run();
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
  void setDebug(bool debug);
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
  std::tuple<unsigned int, unsigned int> getWindowPosition();
  std::tuple<unsigned int, unsigned int> getWindowSize();

  private:
  void _mainLoop();
  std::string _lowerText(const std::string &text);
  bool _isIpInRange(const std::string &ip);
  bool _isPortCorrect(const unsigned int port);
  bool _isFilePresent(const std::string &filepath);
  bool _isFrameLimitCorrect(unsigned int frameLimit);
  void _initialiseRessources();
  void _initialiseConnection();
  void _closeConnection();

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
};

int RealMain(int argc, char **argv);
void DisplayHelp(const std::string binName);
