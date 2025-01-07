/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** NotFound.hpp
*/

/**
 * @file NotFound.hpp
 *
 * @brief File in charge of informing the user that the content they tried to access was not found.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{
    /**
     * @brief This is the class in charge of informing the user
     * that the provided file path could not be found.
     *
     */
    class FileNotFound : public std::exception {
        public:
        /**
         * @brief Construct a new File Not Found object
         *
         * @param error additional information about the error.
         */
        FileNotFound(const std::string &error = "");
        /**
         * @brief Destroy the File Not Found object
         */
        ~FileNotFound();
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
