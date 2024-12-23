/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.hpp
*/

/**
 * @file ExceptionHandling.hpp
 * @brief File in charge of containing the custom errors that are going to be used for custom description errors.
 */

#pragma once
#include <string>
#include <exception>

namespace MyException
{
    /**
     *@brief This is the class in charge of informing the user
     * that the provided file path could not be found.
     *
     */
    class FileNotFound : public std::exception {
        public:
        FileNotFound(const std::string &error = "");
        ~FileNotFound();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user was supposed
     * to pass a parameter along with the flag.
     *
     */
    class NoFlagParameter : public std::exception {
        public:
        NoFlagParameter(const std::string &error = "");
        ~NoFlagParameter();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the entered ip is incorrect.
     *
     */
    class IpIncorrect : public std::exception {
        public:
        IpIncorrect(const std::string &error = "");
        ~IpIncorrect();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the port is incorrect.
     *
     */
    class PortIncorrect : public std::exception {
        public:
        PortIncorrect(const std::string &error = "");
        ~PortIncorrect();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window width is invalid.
     *
     */
    class InvalidWindowWidth : public std::exception {
        public:
        InvalidWindowWidth();
        ~InvalidWindowWidth();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window height is invalid.
     *
     */
    class InvalidWindowHeight : public std::exception {
        public:
        InvalidWindowHeight();
        ~InvalidWindowHeight();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window frame limit is invalid.
     *
     */
    class InvalidFrameLimit : public std::exception {
        public:
        InvalidFrameLimit(unsigned int frameLimit);
        InvalidFrameLimit(const std::string &frameLimit);
        ~InvalidFrameLimit();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the help flag was found.
     * This is not an error.
     *
     */
    class HelpFound : public std::exception {
        public:
        HelpFound();
        ~HelpFound();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the argument that was provided is not known to the program.
     *
     */
    class UnknownArgument : public std::exception {
        public:
        UnknownArgument(const std::string &argument = "");
        ~UnknownArgument();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     * @brief This is the class in charge of raising the ConnectionFailed error.
     *
     */
    class ConnectionFailed : public std::exception {
        public:
        ConnectionFailed(const std::string &address = "");
        ~ConnectionFailed();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of raising the invalid width error
     * informing the user that the width they provided is invalid.
     *
     */
    class InvalidWidth : public std::exception {
        public:
        InvalidWidth(const std::string &width = "", const std::string &min = "", const std::string &max = "");
        ~InvalidWidth();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user that the height they provided is invalid.
     *
     */
    class InvalidHeight : public std::exception {
        public:
        InvalidHeight(const std::string &height = "", const std::string &min = "", const std::string &max = "");
        ~InvalidHeight();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the height they entered is invalid.
     *
     */
    class InvalidFontPath : public std::exception {
        public:
        InvalidFontPath(const std::string &path = "");
        ~InvalidFontPath();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to display a non-existent or invalid shape.
     *
     */
    class InvalidShape : public std::exception {
        public:
        InvalidShape(const std::string &extraDetails = "");
        ~InvalidShape();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to play music from a class that has not music
     * initialised.
     *
     */
    class MusicNotInitialised : public std::exception {
        public:
        MusicNotInitialised();
        ~MusicNotInitialised();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };


    /**
     * @brief This is the class in charge of informing the user
     * that the index they provided is invalid.
     *
     */
    class InvalidIndex : public std::exception {
        public:
        InvalidIndex(const std::string &index = "", const std::string &min = "", const std::string &max = "");
        ~InvalidIndex();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the duration they provided is invalid.
     *
     */
    class InvalidDuration : public std::exception {
        public:
        InvalidDuration(const std::string &duration = "", const std::string &min = "", const std::string &max = "");
        ~InvalidDuration();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant spritesheet.
     *
     */
    class NoSpriteSheet : public std::exception {
        public:
        NoSpriteSheet();
        ~NoSpriteSheet();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant collision class.
     *
     */
    class NoCollision : public std::exception {
        public:
        NoCollision();
        ~NoCollision();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant animation class.
     *
     */
    class NoAnimation : public std::exception {
        public:
        NoAnimation();
        ~NoAnimation();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant animation class.
     *
     */
    class NoSprite : public std::exception {
        public:
        NoSprite();
        ~NoSprite();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant Button class.
     *
     */
    class NoButton : public std::exception {
        public:
        NoButton();
        ~NoButton();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant font instance.
     *
     */
    class NoFont : public std::exception {
        public:
        NoFont(const std::string &fontName = "");
        ~NoFont();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };
}
