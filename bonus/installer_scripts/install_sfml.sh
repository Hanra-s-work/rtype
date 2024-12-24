#!/bin/bash
##
## EPITECH PROJECT, 2024
## rtype
## File description:
## install_sfml.sh
##

# Set the script in fail on error mode
set -e

# The link to run sudo on the user
SUDO=/usr/bin/sudo

# The link to the source file
SOURCE_CODE=https://www.sfml-dev.org/files/SFML-3.0.0-sources.zip

# The file name
FILE_NAME=SFML-3.0.0-sources.zip

# The extracted folder name
FOLDER_NAME=SFML-3.0.0

# The destination folder for the file to extract
FILE_LOCATION=/tmp/SFML
FINAL_DOWNLOAD_PATH=$FILE_LOCATION/$FILE_NAME
FINAL_FOLDER_PATH=$FILE_LOCATION/$FOLDER_NAME

# Boolean values
TRUE=0
FALSE=1

# The silent mode (make the commands verbose or not)
SILENT=$TRUE

# Sleep after the warning message
SLEEP=$TRUE

# Colour list
RESET='\033[0m'
BACKGROUND='\033[0;40m'
RED="$BACKGROUND\033[0;31m"
GREEN="$BACKGROUND\033[0;32m"
YELLOW="$BACKGROUND\033[0;33m"
BLUE="$BACKGROUND\033[0;34m"
CYAN="$BACKGROUND\033[0;36m"
WHITE="$BACKGROUND\033[0;37m"
MAGENTA="$BACKGROUND\033[0;35m"

# The function to display text
function display_text {
    echo -e "$1$2$RESET"
}

function reset_colour {
    echo -e "$RESET"
}

function display_default {
    display_text $WHITE "$1"
}

function display_title {
    display_text $CYAN "$1"
}

function display_error {
    display_text $RED "$1"
}

function display_success {
    display_text $GREEN "$1"
}

function display_info {
    display_text $BLUE "$1"
}

function display_warning {
    display_text $YELLOW "$1"
}

function display_flag {
    display_text $MAGENTA "$1"
}

# The function to relaunch the script as root
function relaunch_as_root {
    if [ $EUID -ne 0 ]; then
        display_error "The script must be run as root."
        $SUDO $0 $@
        exit $?
    else
        display_success "The script is running as root."
    fi
}

# Status tracking
# The success code
SUCCESS=0
# The epitech error code
ERROR=84

# The global status for the program
GLOBAL_STATUS=$SUCCESS

# The function to update the status
function update_global_status {
    if [ $1 -ne $SUCCESS ]; then
        GLOBAL_STATUS=$ERROR
    fi
}

function display_status {
    STATUS=$1
    ACTION=$2
    if [ $STATUS -eq $SUCCESS ]; then
        display_success "$ACTION was successful."
    else
        display_error "$ACTION was a failure."
    fi
    update_global_status $STATUS
}

# Package warning
function display_package_warning {
    display_warning "The following packages are required to install the SFML library:"
    display_warning "cmake, libfreetype6-dev, libjpeg-dev, libxrandr-dev, libgl1-mesa-dev, libudev-dev, libopenal-dev, libflac-dev, libvorbis-dev, libogg-dev"
    display_warning "These are the packages for the ubuntu distribution, their name might change depending on the distribution."
    if [ $SLEEP -eq $FALSE ]; then
        return
    fi
    display_warning "The script will sleep for 5 seconds before starting the installation."
    sleep 5s
}

# The help function
function display_help {
    display_title "Help for the SFML library installation script"
    display_flag "--help, -h"
    display_default "\tDisplay this help message."
    display_flag "--no-sleep, -n, -ns"
    display_default "\tDo not sleep after showing the warning message."
    display_flag "--silent, -s"
    display_default "\tRun the script in silent mode."
    display_flag "--verbose, -v"
    display_default "\tRun the script in verbose mode."
}

# Process the arguments
HELP_FOUND=$FALSE

function process_input_arguments {
    while [ $# -gt 0 ]; do
        if [ "${1,,}" == "--silent" ] || [ "${1,,}" == "-s" ]; then
            SILENT=$TRUE
        elif [ "${1,,}" == "--verbose" ] || [ "${1,,}" == "-v" ]; then
            SILENT=$FALSE
        elif [ "${1,,}" == "--no-sleep" ] || [ "${1,,}" == "-n" ] || [ "${1,,}" == "-ns" ]; then
            SLEEP=$FALSE
        elif [ "${1,,}" == "--help" ] || [ "${1,,}" == "-h" ]; then
            display_help
            HELP_FOUND=$TRUE
            return $SUCCESS
        else
            display_error "Unknown argument: $1"
            display_help
            return $ERROR
        fi
        shift
    done
}

# The functions to install the SFML library
function download_sfml {
    display_title "Downloading the SFML library..."
    mkdir -p $FILE_LOCATION
    if [ $SILENT -eq $TRUE ]; then
        curl -sS $SOURCE_CODE -o $FINAL_DOWNLOAD_PATH
    else
        curl -# $SOURCE_CODE -o $FINAL_DOWNLOAD_PATH
    fi
    STATUS=$?
    display_status $STATUS "Downloading the SFML library"
}

function extract_sfml {
    display_title "Extracting the SFML library..."
    if [ $SILENT -eq $TRUE ]; then
        unzip -o -q $FINAL_DOWNLOAD_PATH -d $FILE_LOCATION
    else
        unzip -o -v $FINAL_DOWNLOAD_PATH -d $FILE_LOCATION
    fi
    STATUS=$?
    display_status $STATUS "Extracting the SFML library to $FILE_LOCATION"
}

function compile_sfml {
    display_title "Compiling the SFML library..."
    cd $FILE_LOCATION/$FOLDER_NAME
    if [ $SILENT -eq $TRUE ]; then
        cmake . . >/dev/null
    else
        cmake . .
    fi
    STATUS=$?
    display_status $STATUS "Configuring the SFML library"
    if [ $STATUS -ne $SUCCESS ]; then
        return
    fi
    if [ $SILENT -eq $TRUE ]; then
        make all >/dev/null
    else
        make all
    fi
    STATUS=$?
    display_status $STATUS "Compiling the SFML library"
}

function install_sfml {
    display_title "Installing the SFML library..."
    if [ $SILENT -eq $TRUE ]; then
        make install >/dev/null
    else
        make install
    fi
    STATUS=$?
    display_status $STATUS "Installing the SFML library"
}

function clean_up {
    display_title "Cleaning up the installation..."
    rm -rf $FILE_LOCATION
    STATUS=$?
    display_status $STATUS "Cleaning up the installation"
}

function main {
    if [ $SILENT -eq $TRUE ]; then
        display_info "The script is running in silent mode."
    else
        display_info "The script is running in verbose mode."
    fi
    download_sfml
    if [ $GLOBAL_STATUS -eq $ERROR ]; then
        display_error "An error occurred during the download of the SFML library."
        clean_up
        return
    fi
    extract_sfml
    if [ $GLOBAL_STATUS -eq $ERROR ]; then
        display_error "An error occurred during the extraction of the SFML library."
        clean_up
        return
    fi
    compile_sfml
    if [ $GLOBAL_STATUS -eq $ERROR ]; then
        display_error "An error occurred during the compilation of the SFML library."
        clean_up
        return
    fi
    install_sfml
    if [ $GLOBAL_STATUS -eq $ERROR ]; then
        display_error "An error occurred during the installation of the SFML library."
        clean_up
        return
    fi
    # clean_up
}

process_input_arguments $@
STATUS=$?
update_global_status $STATUS
if [ $HELP_FOUND -eq $TRUE ]; then
    display_default "End of script"
    exit $SUCCESS
fi
if [ $GLOBAL_STATUS -eq $SUCCESS ]; then
    relaunch_as_root $@
    display_package_warning $@
    main
fi
if [ $GLOBAL_STATUS -eq $ERROR ] && [ $STATUS -eq $SUCCESS ]; then
    display_error "An error occurred during the installation of the SFML library."
    display_info "The global status is $GLOBAL_STATUS"
    display_status $GLOBAL_STATUS "The installation of the SFML library"
fi
display_default "End of script"
exit $GLOBAL_STATUS
