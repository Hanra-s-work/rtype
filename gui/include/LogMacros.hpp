/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** LogMacros.hpp
*/

/**
 * @file LogMacros.hpp
 * @brief File in charge of containing macro binds to allow an easier call to sugar coated log outputs.
 * @li DEBUG This line is for debugging
 * @li INFO This line is for your information
 * @li WARNING This line is for warning you about information that you should pay attention to
 * @li ERROR This line is for informing you that an error has occurred (it should however not be critical)
 * @li CRITICAL This line is for informing the user that something critical has happened and the program thus has to stop
 *
 * @note For the location of the error, call these levels but wit a P, D, PRETTY_, DETAIL_, PRECISE_ preceding it
 *
 * @note If you prefer, you can also prepend the name with LOG_, i.e. DEBUG will become LOG_DEBUG and PDEBUG will become LOG_PDEBUG
 */

#ifndef _LOG_MACROS
    #define _LOG_MACROS

    #include "Log.hpp"

    #ifndef _LOG_CORE
        #define _LOG_CORE
        #define _DEBUG_STR " DEBUG: "
        #define _INFO_STR " INFO: "
        #define _WARNING_STR " WARNING: "
        #define _ERROR_STR " ERROR: "
        #define _CRITICAL_STR " CRITICAL: "
    #endif

    #ifndef _MY_FILE_GETTER
        #define _MY_FILE_GETTER __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << ": "
    #endif

    #ifndef _LEVELS
        #define _LEVELS
        #ifdef _LOG_CORE
            #define DEBUG    Log::getInstance() << _DEBUG_STR
            #define INFO     Log::getInstance() << _INFO_STR
            #define WARNING  Log::getInstance() << _WARNING_STR
            #define ERROR    Log::getInstance() << _ERROR_STR
            #define CRITICAL Log::getInstance() << _CRITICAL_STR
        #endif
        #ifndef _LOG_CORE
            #define DEBUG    Log::getInstance()
            #define INFO     Log::getInstance()
            #define WARNING  Log::getInstance()
            #define ERROR    Log::getInstance()
            #define CRITICAL Log::getInstance()
        #endif
    #endif

    #ifndef _LOG_LEVELS
        #define _LOG_LEVELS
        #ifdef _LOG_CORE
            #define LOG_DEBUG    DEBUG
            #define LOG_INFO     INFO
            #define LOG_WARNING  WARNING
            #define LOG_ERROR    ERROR
            #define LOG_CRITICAL CRITICAL
        #endif
        #ifndef _LOG_CORE
            #define LOG_DEBUG    Log::getInstance()
            #define LOG_INFO     Log::getInstance()
            #define LOG_WARNING  Log::getInstance()
            #define LOG_ERROR    Log::getInstance()
            #define LOG_CRITICAL Log::getInstance()
        #endif
    #endif

    #ifndef _FULL_WORDS
        #define _FULL_WORDS
        #ifndef _PRETTY_LOG
            #define _PRETTY_LOG
            #ifdef _LEVELS
                #ifdef _MY_FILE_GETTER
                    #define PRETTY_DEBUG    DEBUG    << _MY_FILE_GETTER
                    #define PRETTY_INFO     INFO     << _MY_FILE_GETTER
                    #define PRETTY_WARNING  WARNING  << _MY_FILE_GETTER
                    #define PRETTY_ERROR    ERROR    << _MY_FILE_GETTER
                    #define PRETTY_CRITICAL CRITICAL << _MY_FILE_GETTER
                #endif
                #ifndef _MY_FILE_GETTER
                    #define PRETTY_DEBUG    DEBUG
                    #define PRETTY_INFO     INFO
                    #define PRETTY_WARNING  WARNING
                    #define PRETTY_ERROR    ERROR
                    #define PRETTY_CRITICAL CRITICAL
                #endif
            #endif
            #ifndef _LEVELS
                #ifdef _MY_FILE_GETTER
                    #define PRETTY_DEBUG    Log::getInstance() << _MY_FILE_GETTER
                    #define PRETTY_INFO     Log::getInstance() << _MY_FILE_GETTER
                    #define PRETTY_WARNING  Log::getInstance() << _MY_FILE_GETTER
                    #define PRETTY_ERROR    Log::getInstance() << _MY_FILE_GETTER
                    #define PRETTY_CRITICAL Log::getInstance() << _MY_FILE_GETTER
                #endif
                #ifndef _MY_FILE_GETTER
                    #define PRETTY_DEBUG    Log::getInstance()
                    #define PRETTY_INFO     Log::getInstance()
                    #define PRETTY_WARNING  Log::getInstance()
                    #define PRETTY_ERROR    Log::getInstance()
                    #define PRETTY_CRITICAL Log::getInstance()
                #endif
            #endif
        #endif
        #ifndef _DETAIL_LOG
            #define _DETAIL_LOG
            #ifdef _LEVELS
                #ifdef _MY_FILE_GETTER
                    #define DETAIL_DEBUG    DEBUG    << _MY_FILE_GETTER
                    #define DETAIL_INFO     INFO     << _MY_FILE_GETTER
                    #define DETAIL_WARNING  WARNING  << _MY_FILE_GETTER
                    #define DETAIL_ERROR    ERROR    << _MY_FILE_GETTER
                    #define DETAIL_CRITICAL CRITICAL << _MY_FILE_GETTER
                #endif
                #ifndef _MY_FILE_GETTER
                    #define DETAIL_DEBUG    DEBUG
                    #define DETAIL_INFO     INFO
                    #define DETAIL_WARNING  WARNING
                    #define DETAIL_ERROR    ERROR
                    #define DETAIL_CRITICAL CRITICAL
                #endif
            #endif
            #ifndef _LEVELS
                #ifdef _MY_FILE_GETTER
                    #define DETAIL_DEBUG    Log::getInstance() << _MY_FILE_GETTER
                    #define DETAIL_INFO     Log::getInstance() << _MY_FILE_GETTER
                    #define DETAIL_WARNING  Log::getInstance() << _MY_FILE_GETTER
                    #define DETAIL_ERROR    Log::getInstance() << _MY_FILE_GETTER
                    #define DETAIL_CRITICAL Log::getInstance() << _MY_FILE_GETTER
                #endif
                #ifndef _MY_FILE_GETTER
                    #define DETAIL_DEBUG    Log::getInstance()
                    #define DETAIL_INFO     Log::getInstance()
                    #define DETAIL_WARNING  Log::getInstance()
                    #define DETAIL_ERROR    Log::getInstance()
                    #define DETAIL_CRITICAL Log::getInstance()
                #endif
            #endif
        #endif
        #ifndef _PRECISE_LOG
            #define _PRECISE_LOG
            #ifdef _LEVELS
                #ifdef _MY_FILE_GETTER
                    #define PRECISE_DEBUG    DEBUG    << _MY_FILE_GETTER
                    #define PRECISE_INFO     INFO     << _MY_FILE_GETTER
                    #define PRECISE_WARNING  WARNING  << _MY_FILE_GETTER
                    #define PRECISE_ERROR    ERROR    << _MY_FILE_GETTER
                    #define PRECISE_CRITICAL CRITICAL << _MY_FILE_GETTER
                #endif
                #ifndef _MY_FILE_GETTER
                    #define PRECISE_DEBUG    DEBUG
                    #define PRECISE_INFO     INFO
                    #define PRECISE_WARNING  WARNING
                    #define PRECISE_ERROR    ERROR
                    #define PRECISE_CRITICAL CRITICAL
                #endif
            #endif
            #ifndef _LEVELS
                #ifdef _MY_FILE_GETTER
                    #define PRECISE_DEBUG    Log::getInstance() << _MY_FILE_GETTER
                    #define PRECISE_INFO     Log::getInstance() << _MY_FILE_GETTER
                    #define PRECISE_WARNING  Log::getInstance() << _MY_FILE_GETTER
                    #define PRECISE_ERROR    Log::getInstance() << _MY_FILE_GETTER
                    #define PRECISE_CRITICAL Log::getInstance() << _MY_FILE_GETTER
                #endif
                #ifndef _MY_FILE_GETTER
                    #define PRECISE_DEBUG    Log::getInstance()
                    #define PRECISE_INFO     Log::getInstance()
                    #define PRECISE_WARNING  Log::getInstance()
                    #define PRECISE_ERROR    Log::getInstance()
                    #define PRECISE_CRITICAL Log::getInstance()
                #endif
            #endif
        #endif
    #endif

    #ifndef _P_LOGGERS
        #define _P_LOGGERS
        #ifdef _LEVELS
            #ifdef _MY_FILE_GETTER
                #define PDEBUG    DEBUG    << _MY_FILE_GETTER
                #define PINFO     INFO     << _MY_FILE_GETTER
                #define PWARNING  WARNING  << _MY_FILE_GETTER
                #define PERROR    ERROR    << _MY_FILE_GETTER
                #define PCRITICAL CRITICAL << _MY_FILE_GETTER
            #endif
            #ifndef _MY_FILE_GETTER
                #define PDEBUG    DEBUG
                #define PINFO     INFO
                #define PWARNING  WARNING
                #define PERROR    ERROR
                #define PCRITICAL CRITICAL
            #endif
        #endif
        #ifndef _LEVELS
            #ifdef _MY_FILE_GETTER
                #define PDEBUG    Log::getInstance() << _MY_FILE_GETTER
                #define PINFO     Log::getInstance() << _MY_FILE_GETTER
                #define PWARNING  Log::getInstance() << _MY_FILE_GETTER
                #define PERROR    Log::getInstance() << _MY_FILE_GETTER
                #define PCRITICAL Log::getInstance() << _MY_FILE_GETTER
            #endif
            #ifndef _MY_FILE_GETTER
                #define PDEBUG    Log::getInstance()
                #define PINFO     Log::getInstance()
                #define PWARNING  Log::getInstance()
                #define PERROR    Log::getInstance()
                #define PCRITICAL Log::getInstance()
            #endif
        #endif
    #endif

    #ifndef _D_LOGGERS
        #define _D_LOGGERS
        #ifdef _MY_FILE_GETTER
            #define DDEBUG    DEBUG    << _MY_FILE_GETTER
            #define DINFO     INFO     << _MY_FILE_GETTER
            #define DWARNING  WARNING  << _MY_FILE_GETTER
            #define DERROR    ERROR    << _MY_FILE_GETTER
            #define DCRITICAL CRITICAL << _MY_FILE_GETTER
        #endif
        #ifndef _MY_FILE_GETTER
            #define DDEBUG    DEBUG
            #define DINFO     INFO
            #define DWARNING  WARNING
            #define DERROR    ERROR
            #define DCRITICAL CRITICAL
        #endif
    #endif
    #ifndef _LEVELS
        #ifdef _MY_FILE_GETTER
            #define DDEBUG    Log::getInstance() << _MY_FILE_GETTER
            #define DINFO     Log::getInstance() << _MY_FILE_GETTER
            #define DWARNING  Log::getInstance() << _MY_FILE_GETTER
            #define DERROR    Log::getInstance() << _MY_FILE_GETTER
            #define DCRITICAL Log::getInstance() << _MY_FILE_GETTER
        #endif
        #ifndef _MY_FILE_GETTER
            #define DDEBUG    Log::getInstance()
            #define DINFO     Log::getInstance()
            #define DWARNING  Log::getInstance()
            #define DERROR    Log::getInstance()
            #define DCRITICAL Log::getInstance()
        #endif
    #endif

    #ifndef _LOG_P_LOGGERS
        #define _LOG_P_LOGGERS
        #ifdef _MY_FILE_GETTER
            #define LOG_PDEBUG    DEBUG    << _MY_FILE_GETTER
            #define LOG_PINFO     INFO     << _MY_FILE_GETTER
            #define LOG_PWARNING  WARNING  << _MY_FILE_GETTER
            #define LOG_PERROR    ERROR    << _MY_FILE_GETTER
            #define LOG_PCRITICAL CRITICAL << _MY_FILE_GETTER
        #endif
        #ifndef _MY_FILE_GETTER
            #define LOG_PDEBUG    DEBUG
            #define LOG_PINFO     INFO
            #define LOG_PWARNING  WARNING
            #define LOG_PERROR    ERROR
            #define LOG_PCRITICAL CRITICAL
        #endif
    #endif
    #ifndef _LEVELS
        #ifdef _MY_FILE_GETTER
            #define LOG_PDEBUG    Log::getInstance() << _MY_FILE_GETTER
            #define LOG_PINFO     Log::getInstance() << _MY_FILE_GETTER
            #define LOG_PWARNING  Log::getInstance() << _MY_FILE_GETTER
            #define LOG_PERROR    Log::getInstance() << _MY_FILE_GETTER
            #define LOG_PCRITICAL Log::getInstance() << _MY_FILE_GETTER
        #endif
        #ifndef _MY_FILE_GETTER
            #define LOG_PDEBUG    Log::getInstance()
            #define LOG_PINFO     Log::getInstance()
            #define LOG_PWARNING  Log::getInstance()
            #define LOG_PERROR    Log::getInstance()
            #define LOG_PCRITICAL Log::getInstance()
        #endif
    #endif

    #ifndef _LOG_D_LOGGERS
        #define _LOG_D_LOGGERS
        #ifdef _MY_FILE_GETTER
            #define LOG_DDEBUG    DEBUG    << _MY_FILE_GETTER
            #define LOG_DINFO     INFO     << _MY_FILE_GETTER
            #define LOG_DWARNING  WARNING  << _MY_FILE_GETTER
            #define LOG_DERROR    ERROR    << _MY_FILE_GETTER
            #define LOG_DCRITICAL CRITICAL << _MY_FILE_GETTER
        #endif
        #ifndef _MY_FILE_GETTER
            #define LOG_DDEBUG    DEBUG
            #define LOG_DINFO     INFO
            #define LOG_DWARNING  WARNING
            #define LOG_DERROR    ERROR
            #define LOG_DCRITICAL CRITICAL
        #endif
    #endif
    #ifndef _LEVELS
        #ifdef _MY_FILE_GETTER
            #define LOG_DDEBUG    Log::getInstance() << _MY_FILE_GETTER
            #define LOG_DINFO     Log::getInstance() << _MY_FILE_GETTER
            #define LOG_DWARNING  Log::getInstance() << _MY_FILE_GETTER
            #define LOG_DERROR    Log::getInstance() << _MY_FILE_GETTER
            #define LOG_DCRITICAL Log::getInstance() << _MY_FILE_GETTER
        #endif
        #ifndef _MY_FILE_GETTER
            #define LOG_DDEBUG    Log::getInstance()
            #define LOG_DINFO     Log::getInstance()
            #define LOG_DWARNING  Log::getInstance()
            #define LOG_DERROR    Log::getInstance()
            #define LOG_DCRITICAL Log::getInstance()
        #endif
    #endif

#endif
