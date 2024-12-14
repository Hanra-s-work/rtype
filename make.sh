#!/bin/bash

ERROR=1
SUCCESS=0

TRUE=0
FALSE=1
STATUSES=()
STATUS_TAGS=()
SOURCE_DIRS=(gui server)

DESTINATION_DIR=./bin

ALL=$FALSE
CLEAN=$FALSE
FCLEAN=$FALSE

function build_dirs {
    local build_source="${1:-./gui}"
    local build_destination="${2:-./bin}"
    local source_name="$(basename "$build_source")"
    local cache_dir="$build_destination/$source_name"
    local root_directory="$(pwd)"
    echo "Building $build_source"
    echo "Creating folder $build_destination if it does not exist"
    mkdir -p "$cache_dir"
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Failed to create the folder $cache_dir, code $STATUS"
        return $STATUS
    fi
    echo "Running cmake for the folder $build_source"
    cmake -S "$build_source" -B "$cache_dir"
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Cmake failed with status code $STATUS"
        return $STATUS
    fi
    echo "Running make in $cache_dir"
    make -C "$cache_dir"
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Make failed with status code $STATUS"
        return $STATUS
    fi
    echo "Creating folder for the binary destination, folder: $build_destination"
    mkdir -p "$build_destination"
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Failed to create the folder $build_destination, code $STATUS"
        return $STATUS
    fi
    find "$cache_dir" -maxdepth 1 -type f -executable -exec cp {} "$build_destination" \;
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Failed to copy the binary to $build_destination, code $STATUS"
        return $STATUS
    fi
    find "$cache_dir" -maxdepth 1 -type f -executable -exec cp {} "$root_directory" \;
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Failed to copy the binary to $root_directory, code $STATUS"
        return $STATUS
    fi
    echo "Build successful for $source_name"
}

function clean {
    local source_name="$(basename "$1")"
    local build_destination="${2:-./bin}"
    local cache_dir="$build_destination/$source_name"
    echo "Cleaning $cache_dir"
    if [ ! -d "$cache_dir" ]; then
        echo "Directory $cache_dir not found"
        return $ERROR
    fi
    echo "Running make -C $cache_dir clean"
    make -C "$cache_dir" clean
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Make clean failed with status code $STATUS"
        return $STATUS
    fi
    echo "The clean option was successfull"
}

function fclean {
    local build_destination="${2:-./bin}"
    local source_name="$(basename "$1")"
    local cache_dir="$build_destination/$source_name"
    echo "Cleaning $cache_dir"
    if [ ! -d $cache_dir ]; then
        echo "Directory not found"
        return $ERROR
    fi
    echo "Running make -C $cache_dir fclean"
    make -C "$cache_dir" fclean
    STATUS=$?
    if [ $STATUS -ne $SUCCESS ]; then
        echo "Make fclean failed with status code $STATUS"
        return $STATUS
    fi
    echo "The fclean option was successfull"
}

if [ $# -ne 0 ]; then
    while [ $# -ne 0 ]; do
        stripped="${1#-}"
        stripped="${stripped#-}"
        stripped="${stripped#/}"
        lower="${stripped,,}"
        if [ "$lower" == "help" ] || [ "$lower" == "h" ]; then
            echo "USAGE:"
            echo -e "\t$0 [--help] [ALL] [CLEAN] [FCLEAN]"
            echo ""
            echo "DEFAULT OPERATION:"
            echo -e "\tThe default operation is as if you had provided the ALL argument"
            echo ""
            echo "ARGUMENTS:"
            echo -e "\t-\t--help, -h, HELP,/help,/h\tDisplay this help and exit"
            echo -e "\t-\t--all, -all, all, /all\tRun the bash all command (default command)"
            echo -e "\t-\t--clean, -clean, clean, /clean\tRun the bash clean command"
            echo -e "\t-\t--fclean, -fclean, FCLEAN, /fclean\tRun the bash fclean command"
            exit 0
        elif [ "$lower" == "all" ]; then
            echo "The all option was found, enabeling."
            ALL=$TRUE
        elif [ "$lower" == "clean" ]; then
            echo "The clean option was found, enabeling."
            CLEAN=$TRUE
        elif [ "$lower" == "fclean" ]; then
            echo "The fclean option was found, enabeling."
            FCLEAN=$TRUE
        else
            echo "Invalid argument: $1"
        fi
        shift
    done
else
    echo "No options found, setting to ALL"
    ALL=$TRUE
fi

if [ "$CLEAN" == "$TRUE" ]; then
    echo "Clean triggered"
    for i in "${SOURCE_DIRS[@]}"; do
        cache_dir_name="clean: $(basename "$i")"
        clean "$i" "$DESTINATION_DIR"
        STATUS=$?
        if [ $STATUS -ne 0 ]; then
            echo "Error: $cache_dir_name, code $STATUS"
        fi
        echo "$cache_dir_name, status $STATUS"
        STATUS_TAGS+=("$cache_dir_name")
        STATUSES+=($STATUS)
    done
else
    echo "Clean not triggered"
fi

if [ "$FCLEAN" == "$TRUE" ]; then
    for i in "${SOURCE_DIRS[@]}"; do
        cache_dir_name="fclean: $(basename "$i")"
        clean "$i" "$DESTINATION_DIR"
        STATUS=$?
        if [ $STATUS -ne 0 ]; then
            echo "Error: $cache_dir_name, code $STATUS"
        fi
        STATUS_TAGS+=("$cache_dir_name")
        STATUSES+=($STATUS)
    done
    echo "Removing the $DESTINATION_DIR folder"
    rm -rf "$DESTINATION_DIR"
    STATUS=$?
    if [ $STATUS -ne 0 ]; then
        echo "Error removing $DESTINATION_DIR folder"
    fi
    STATUS_TAGS+=("Remove: $DESTINATION_DIR")
    STATUSES+=($STATUS)
fi

if [ "$ALL" == "$TRUE" ]; then
    for i in "${SOURCE_DIRS[@]}"; do
        cache_dir_name="all: $(basename "$i")"
        build_dirs "$i" "$DESTINATION_DIR"
        STATUS=$?
        if [ $STATUS -ne 0 ]; then
            echo "Error: $cache_dir_name, code $STATUS"
        fi
        STATUS_TAGS+=("$cache_dir_name")
        STATUSES+=($STATUS)
    done
fi

GLOBAL_STATUS=0
for idx in "${!STATUSES[@]}"; do
    description="${STATUS_TAGS[$idx]}"
    status="${STATUSES[$idx]}"
    echo "Task: $description, Status: $status"
    if [ "$status" -ne 0 ]; then
        GLOBAL_STATUS=$status
    fi
done
exit $GLOBAL_STATUS
