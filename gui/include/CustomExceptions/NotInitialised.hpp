/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** NotInitialised.hpp
*/

/**
 * @file NotInitialised.hpp
 *
 * @brief File in charge of informing the user that the content they tried to access was not initialised.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"


namespace CustomExceptions
{

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to play music from a class that has not music
     * initialised.
     *
     */
    class MusicNotInitialised : public std::exception {
        public:
        /**
         * @brief Construct a new Music Not Initialised object
         *
         * @param exceptionDetail A string allowing you to provide
         * additional detail if required.
         */
        MusicNotInitialised(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the Music Not Initialised object
         *
         */
        ~MusicNotInitialised();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

}
