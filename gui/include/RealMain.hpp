/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Main.hpp
*/

#pragma once
#include <string>

class Main {
    public:
    Main(std::string ip = "127.0.0.1", unsigned int port = 5000, unsigned int windowWidth = 800, unsigned int windowHeight = 800, bool windowCursor = true, bool windowFullscreen = false, std::string windowTitle = "R-Type", unsigned int windowX = 0, unsigned int windowY = 0, std::string windowCursorIcon = "NULL", bool imageIsSprite = false, bool spriteStartTop = false, bool spriteStartLeft = false, unsigned int spriteWidth = 20, unsigned int spriteHeight = 20);
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
    std::tuple<unsigned int, unsigned int> getWindowPosition();
    std::tuple<unsigned int, unsigned int> getWindowSize();
    private:
    bool _isIpInRange(const std::string &ip);
    bool _isPortCorrect(const unsigned int port);
    bool _isFilePresent(const std::string &filepath);
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
    unsigned int _spriteWidth;
    unsigned int _spriteHeight;

};

int RealMain(int argc, char **argv);
