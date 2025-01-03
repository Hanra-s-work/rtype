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

#include "MyRecodes.hpp"

namespace MyException
{
    /**
     *@brief This is the class in charge of informing the user
     * that the provided file path could not be found.
     *
     */
    class FileNotFound : public std::exception {
        public:
        /**
         *@brief Construct a new File Not Found object
         *
         * @param error additional information about the error.
         */
        FileNotFound(const std::string &error = "");
        /**
         *@brief Destroy the File Not Found object
         */
        ~FileNotFound();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user was supposed
     * to pass a parameter along with the flag.
     *
     */
    class NoFlagParameter : public std::exception {
        public:
        /**
         *@brief Construct a new No Flag Parameter object
         *
         * @param error additional information about the error.
         */
        NoFlagParameter(const std::string &error = "");
        /**
         *@brief Destroy the No Flag Parameter object
         *
         */
        ~NoFlagParameter();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the entered ip is incorrect.
     *
     */
    class InvalidIp : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Ip object
         *
         * @param error additional information about the error.
         */
        InvalidIp(const std::string &error = "");
        /**
         *@brief Destroy the Invalid Ip object
         *
         */
        ~InvalidIp();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the port is incorrect.
     *
     */
    class InvalidPort : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Port object
         *
         * @param error additional information about the error.
         */
        InvalidPort(const std::string &error = "");
        /**
         *@brief Destroy the Invalid Port object
         *
         */
        ~InvalidPort();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the font configuration they provided is incorrect.
     *
     */
    class InvalidFontConfiguration : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Font Configuration object
         *
         * @param userConfiguration The configuration section provided by the user
         * @param fontName The name of the font that was affected by the configuration
         */
        InvalidFontConfiguration(const std::string &userConfiguration = "", const std::string &fontName = "");
        /**
         *@brief Destroy the Invalid Font Configuration object
         *
         */
        ~InvalidFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the music configuration they provided is incorrect.
     *
     */
    class InvalidMusicConfiguration : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Music Configuration object
         *
         * @param userConfiguration The configuration section provided by the user.
         * @param musicName The name of the music that was affected by the configuration.
         */
        InvalidMusicConfiguration(const std::string &userConfiguration = "", const std::string &musicName = "");
        /**
         *@brief Destroy the Invalid Music Configuration object
         *
         */
        ~InvalidMusicConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the sprite configuration they provided is incorrect.
     *
     */
    class InvalidSpriteConfiguration : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Sprite Configuration object
         *
         * @param userConfiguration The configuration section provided by the user.
         * @param spriteName The name of the sprite that was affected by the configuration.
         */
        InvalidSpriteConfiguration(const std::string &userConfiguration = "", const std::string &spriteName = "");
        /**
         *@brief Destroy the Invalid Sprite Configuration object
         *
         */
        ~InvalidSpriteConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window width is invalid.
     *
     */
    class InvalidWindowWidth : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Window Width object
         *
         * @param argument The width provided by the user.
         */
        InvalidWindowWidth(const std::string &argument = "");
        /**
         *@brief Destroy the Invalid Window Width object
         *
         */
        ~InvalidWindowWidth();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window height is invalid.
     *
     */
    class InvalidWindowHeight : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Window Height object
         *
         * @param argument The height provided by the user.
         */
        InvalidWindowHeight(const std::string &argument = "");
        /**
         *@brief Destroy the Invalid Window Height object
         *
         */
        ~InvalidWindowHeight();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window frame limit is invalid.
     *
     */
    class InvalidFrameLimit : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Frame Limit object
         *
         * @param frameLimit The frame limit provided by the user as an integer
         */
        InvalidFrameLimit(unsigned int frameLimit);
        /**
         *@brief Construct a new Invalid Frame Limit object
         *
         * @param frameLimit The frame limit provided by the user as a string
         */
        InvalidFrameLimit(const std::string &frameLimit);
        /**
         *@brief Destroy the Invalid Frame Limit object
         *
         */
        ~InvalidFrameLimit();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the help flag was found.
     * This is not an error.
     *
     */
    class HelpFound : public std::exception {
        public:
        /**
         *@brief Construct a new Help Found object
         */
        HelpFound();
        /**
         *@brief Destroy the Help Found object
         *
         */
        ~HelpFound();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the version flag was found.
     * This is not an error.
     *
     */
    class VersionFound : public std::exception {
        public:
        /**
         *@brief Construct a new Version Found object
         *
         */
        VersionFound();
        /**
         *@brief Destroy the Version Found object
         *
         */
        ~VersionFound();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the argument that was provided is not known to the program.
     *
     */
    class UnknownArgument : public std::exception {
        public:
        /**
         *@brief Construct a new Unknown Argument object
         *
         * @param argument The argument that was provided by the user.
         */
        UnknownArgument(const std::string &argument = "");
        /**
         *@brief Destroy the Unknown Argument object
         *
         */
        ~UnknownArgument();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of raising the ConnectionFailed error.
     *
     */
    class ConnectionFailed : public std::exception {
        public:
        /**
         *@brief Construct a new Connection Failed object
         *
         * @param address The address the program tried to connect to.
         */
        ConnectionFailed(const std::string &address = "");
        /**
         *@brief Destroy the Connection Failed object
         *
         */
        ~ConnectionFailed();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of raising the invalid width error
     * informing the user that the width they provided is invalid.
     * This class is meant to be a bit more generic so that this type of error
     * can be raised by more than one party.
     *
     */
    class InvalidWidth : public std::exception {
        public:
        /**
         * @brief Construct a new Invalid Width object
         *
         * @param width The width that was provided.
         * @param min The minimum allowed width
         * @param max The maximum allowed width
         */
        InvalidWidth(const std::string &width = "", const std::string &min = "", const std::string &max = "");
        /**
         *@brief Destroy the Invalid Width object
         *
         */
        ~InvalidWidth();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of raising the invalid height error
     * informing the user that the height they provided is invalid.
     * This class is meant to be a bit more generic so that this type of error
     * can be raised by more than one party.
     *
     */
    class InvalidHeight : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Height object
         *
         * @param height The height they provided
         * @param min The minimum allowed height
         * @param max The maximum allowed height
         */
        InvalidHeight(const std::string &height = "", const std::string &min = "", const std::string &max = "");
        /**
         *@brief Destroy the Invalid Height object
         *
         */
        ~InvalidHeight();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the height they entered is invalid.
     *
     */
    class InvalidFontPath : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Font Path object
         *
         * @param path The path of the font that was provided by the user.
         */
        InvalidFontPath(const std::string &path = "");
        /**
         *@brief Destroy the Invalid Font Path object
         *
         */
        ~InvalidFontPath();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to display a non-existent or invalid shape.
     *
     */
    class InvalidShape : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Shape object
         *
         * @param extraDetails a string of a more detailed explanation of their error.
         */
        InvalidShape(const std::string &extraDetails = "");
        /**
         *@brief Destroy the Invalid Shape object
         *
         */
        ~InvalidShape();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to play music from a class that has not music
     * initialised.
     *
     */
    class MusicNotInitialised : public std::exception {
        public:
        /**
         *@brief Construct a new Music Not Initialised object
         *
         */
        MusicNotInitialised();
        /**
         *@brief Destroy the Music Not Initialised object
         *
         */
        ~MusicNotInitialised();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };


    /**
     * @brief This is the class in charge of informing the user
     * that the index they provided is invalid.
     *
     */
    class InvalidIndex : public std::exception {
        public:
        /**
         * @brief Construct a new Invalid Index object
         *
         * @param index The index provided by the user
         * @param min The minimum allowed index.
         * @param max The maximum allowed index.
         */
        InvalidIndex(const std::string &index = "", const std::string &min = "", const std::string &max = "");
        /**
         *@brief Destroy the Invalid Index object
         *
         */
        ~InvalidIndex();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the duration they provided is invalid.
     *
     */
    class InvalidDuration : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Duration object
         *
         * @param duration The duration provided by the user.
         * @param min The minimum allowed duration.
         * @param max The maximum allowed duration.
         */
        InvalidDuration(const std::string &duration = "", const std::string &min = "", const std::string &max = "");
        /**
         *@brief Destroy the Invalid Duration object
         *
         */
        ~InvalidDuration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the toml file they provided is invalid.
     *
     */
    class InvalidTOML : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid toml object
         *
         * @param path The path to the toml file provided by the user
         * @param error Additional information about the error.
         */
        InvalidTOML(const std::string &path = "", const std::string &error = "");
        /**
         *@brief Destroy the Invalid toml object
         *
         */
        ~InvalidTOML();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the key type present in the file is of the wrong expected type for the spritesheet.
     *
     */
    class InvalidConfigurationSpritesheetType : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Configuration Spritesheet Type object
         *
         * @param path The path to the TOML file
         * @param key The key that contains the invalid type.
         * @param type The type of the key in the configuration file
         * @param expectedType The type that was expected of the key.
         */
        InvalidConfigurationSpritesheetType(const std::string &path = "", const std::string &key = "", const std::string &type = "", const std::string &expectedType = "");
        /**
         *@brief Destroy the Invalid Configuration Spritesheet Type object
         *
         */
        ~InvalidConfigurationSpritesheetType();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the key type present in the file is of the wrong expected type for the music.
     *
     */
    class InvalidConfigurationMusicType : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Configuration Music Type object
         *
         * @param path The path to the TOML file
         * @param key The key that contains the invalid type.
         * @param type The type of the key in the configuration file
         * @param expectedType The type that was expected of the key.
         */
        InvalidConfigurationMusicType(const std::string &path = "", const std::string &key = "", const std::string &type = "", const std::string &expectedType = "");
        /**
         *@brief Destroy the Invalid Configuration Music Type object
         *
         */
        ~InvalidConfigurationMusicType();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the key type present in the file is of the wrong expected type for the spritesheet.
     *
     */
    class InvalidConfigurationFontType : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid Configuration Font Type object
         *
         * @param path The path to the TOML file
         * @param key The key that contains the invalid type.
         * @param type The type of the key in the configuration file
         * @param expectedType The type that was expected of the key.
         */
        InvalidConfigurationFontType(const std::string &path = "", const std::string &key = "", const std::string &type = "", const std::string &expectedType = "");
        /**
         *@brief Destroy the Invalid Configuration Font Type object
         *
         */
        ~InvalidConfigurationFontType();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant spritesheet.
     *
     */
    class NoSpriteSheet : public std::exception {
        public:
        /**
         *@brief Construct a new No Sprite Sheet object
         *
         */
        NoSpriteSheet();
        /**
         * @brief Destroy the No Sprite Sheet object
         *
         */
        ~NoSpriteSheet();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant collision class.
     *
     */
    class NoCollision : public std::exception {
        public:
        /**
         *@brief Construct a new No Collision object
         *
         */
        NoCollision();
        /**
         *@brief Destroy the No Collision object
         *
         */
        ~NoCollision();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant animation class.
     *
     */
    class NoAnimation : public std::exception {
        public:
        /**
         *@brief Construct a new No Animation object
         *
         */
        NoAnimation();
        /**
         *@brief Destroy the No Animation object
         *
         */
        ~NoAnimation();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant animation class.
     *
     */
    class NoSprite : public std::exception {
        public:
        /**
         *@brief Construct a new No Sprite object
         *
         */
        NoSprite();
        /**
         *@brief Destroy the No Sprite object
         *
         */
        ~NoSprite();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant Button class.
     *
     */
    class NoButton : public std::exception {
        public:
        /**
         *@brief Construct a new No Button object
         *
         */
        NoButton();
        /**
         *@brief Destroy the No Button object
         *
         */
        ~NoButton();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant font instance.
     *
     */
    class NoFont : public std::exception {
        public:
        /**
         *@brief Construct a new No Font object
         *
         * @param fontName The name of the font that was provided.
         */
        NoFont(const std::string &fontName = "");
        /**
         *@brief Destroy the No Font object
         *
         */
        ~NoFont();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that there is no configuration for the font in charge of displaying text
     * when it is a title.
     *
     */
    class NoTitleFontConfiguration : public std::exception {
        public:
        /**
         *@brief Construct a new No Title Font Configuration object
         *
         * @param tomlPath The path to the toml configuration file.
         */
        NoTitleFontConfiguration(const std::string &tomlPath = "");
        /**
         *@brief Destroy the No Title Font Configuration object
         *
         */
        ~NoTitleFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that there is no configuration for the font in charge of displaying text
     * when it is a body.
     *
     */
    class NoBodyFontConfiguration : public std::exception {
        public:
        /**
         *@brief Construct a new No Body Font Configuration object
         *
         * @param tomlPath The path to the toml configuration file.
         */
        NoBodyFontConfiguration(const std::string &tomlPath = "");
        /**
         *@brief Destroy the No Body Font Configuration object
         *
         */
        ~NoBodyFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that there is no configuration for the font in charge of displaying text
     * when it is not a title nor a body.
     *
     */
    class NoDefaultFontConfiguration : public std::exception {
        public:
        /**
         *@brief Construct a new No Default Font Configuration object
         *
         * @param tomlPath The path to the toml configuration file.
         */
        NoDefaultFontConfiguration(const std::string &tomlPath = "");
        /**
         *@brief Destroy the No Default Font Configuration object
         *
         */
        ~NoDefaultFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant toml instance.
     *
     */
    class NoTOML : public std::exception {
        public:
        /**
         *@brief Construct a new No toml object
         *
         * @param tomlPath The path to the toml file.
         */
        NoTOML(const std::string &tomlPath = "");
        /**
         *@brief Destroy the No toml object
         *
         */
        ~NoTOML();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };


    /**
     *@brief This is the class in charge of informing the user
     * that they tried to access a non-existant toml key instance.
     *
     */
    class NoTOMLKey : public std::exception {
        public:
        /**
         *@brief Construct a new No toml Key object
         *
         * @param tomlPath The path to the toml file
         * @param tomlKey The key that the user tried to access.
         */
        NoTOMLKey(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         *@brief Destroy the No toml Key object
         *
         */
        ~NoTOMLKey();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };


    /**
     *@brief This is the class in charge of informing the user
     * that the type of the toml key is not the one that was expected.
     *
     */
    class InvalidTOMLKeyType : public std::exception {
        public:
        /**
         *@brief Construct a new Invalid toml Key Type object
         *
         * @param path The path to the toml file
         * @param key The key that contains the invalid type.
         * @param type The type of the key in the configuration file
         * @param expectedType The type that was expected of the key.
         */
        InvalidTOMLKeyType(const std::string &tomlPath = "", const std::string &tomlKey = "", const std::string &currentType = "", const std::string &expectedType = "");
        /**
         *@brief Destroy the Invalid toml Key Type object
         *
        */
        ~InvalidTOMLKeyType();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the program could not find the sprite section in the configuration file.
     *
     */
    class NoSpritesInConfigFile : public std::exception {
        public:
        /**
         *@brief Construct a new No Sprites In Config File object
         *
         * @param tomlPath The path to the toml file.
         * @param tomlKey The toml key that is affected.
         */
        NoSpritesInConfigFile(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         *@brief Destroy the No Sprites In Config File object
         *
        */
        ~NoSpritesInConfigFile();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the program could not find the music section in the configuration file.
     *
     */
    class NoMusicInConfigFile : public std::exception {
        public:
        /**
         *@brief Construct a new No Music In Config File object
         *
         * @param tomlPath The path to the toml file.
         * @param tomlKey The key that was affected.
         */
        NoMusicInConfigFile(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         *@brief Destroy the No Music In Config File object
         *
        */
        ~NoMusicInConfigFile();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the program could not find the font section in the configuration file.
     *
     */
    class NoFontInConfigFile : public std::exception {
        public:
        /**
         *@brief Construct a new No Font In Config File object
         *
         * @param tomlPath The path to the toml file.
         * @param tomlKey The key that was affected.
         */
        NoFontInConfigFile(const std::string &tomlPath = "", const std::string &tomlKey = "");
        ~NoFontInConfigFile();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; ///< Stores the error message.
        const char *_buffer; ///< Buffer for formatted error message.
    };
}
