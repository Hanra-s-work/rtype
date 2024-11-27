#!/bin/bash

# The link to run sudo on the user
SUDO=/usr/bin/sudo

# The link to the source file
SOURCE_CODE=https://www.sfml-dev.org/files/SFML-2.6.2-linux-gcc-64-bit.tar.gz

# The file name
FILE_NAME=SFML-2.6.2-linux-gcc-64-bit.tar.gz

# The destination folder for the file to extract
FILE_LOCATION=/tmp/SFML
FINAL_DOWNLOAD_PATH=$FILE_LOCATION/$FILE_NAME

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

# The functions to install the SFML library
function download_sfml {
    display_title "Downloading the SFML library..."
    mkdir -p $FILE_LOCATION
    wget --progress=bar:force $SOURCE_CODE -O $FINAL_DOWNLOAD_PATH
    STATUS=$?
    display_status $STATUS "Downloading the SFML library"
}

function extract_sfml {
    display_title "Extracting the SFML library..."
    tar -xvzf $FINAL_DOWNLOAD_PATH -C $FILE_LOCATION
    STATUS=$?
    display_status $STATUS "Extracting the SFML library to $FILE_LOCATION"
}

function compile_sfml {
    display_title "Compiling the SFML library..."
    cd $FILE_LOCATION/SFML-2.6.2
    cmake .
    STATUS=$?
    display_status $STATUS "Configuring the SFML library"
    make
    STATUS=$?
    display_status $STATUS "Compiling the SFML library"
}

function install_sfml {
    display_title "Installing the SFML library..."
    $SUDO make install
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
    download_sfml
    extract_sfml
    compile_sfml
    install_sfml
    clean_up
}

main
if [ $GLOBAL_STATUS -eq $ERROR ]; then
    display_error "An error occurred during the installation of the SFML library."
fi
display_info "The global status is $GLOBAL_STATUS"
display_status $GLOBAL_STATUS "The installation of the SFML library"
display_default "The installation of the SFML library has ended."
exit $GLOBAL_STATUS
