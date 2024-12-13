#!/bin/bash

function build_dirs {
    local success=0
    local build_source="${1:-./gui}"
    local build_destination="${2:-./bin}"
    local source_name="$(basename "$build_source")"
    local cache_dir="$build_destination/$source_name"
    local root_directory="$(pwd)"
    echo "Building $build_source"
    echo "Creating folder $build_destination if it does not exist"
    mkdir -p "$cache_dir"
    STATUS=$?
    if [ $STATUS -ne $success ]; then
        echo "Failed to create the folder $cache_dir, code $STATUS"
        return $STATUS
    fi
    echo "Running cmake for the folder $build_source"
    cmake -S "$build_source" -B "$cache_dir"
    STATUS=$?
    if [ $STATUS -ne $success ]; then
        echo "Cmake failed with status code $STATUS"
        return $STATUS
    fi
    echo "Running make in $cache_dir"
    make -C "$cache_dir"
    STATUS=$?
    if [ $STATUS -ne $success ]; then
        echo "Make failed with status code $STATUS"
        return $STATUS
    fi
    echo "Creating folder for the binary destination, folder: $build_destination"
    mkdir -p "$build_destination"
    STATUS=$?
    if [ $STATUS -ne $success ]; then
        echo "Failed to create the folder $build_destination, code $STATUS"
        return $STATUS
    fi
    find "$cache_dir" -maxdepth 1 -type f -executable -exec cp {} "$build_destination" \;
    STATUS=$?
    if [ $STATUS -ne $success ]; then
        echo "Failed to copy the binary to $build_destination, code $STATUS"
        return $STATUS
    fi
    find "$cache_dir" -maxdepth 1 -type f -executable -exec cp {} "$root_directory" \;
    STATUS=$?
    if [ $STATUS -ne $success ]; then
        echo "Failed to copy the binary to $root_directory, code $STATUS"
        return $STATUS
    fi
    echo "Build successful for $source_name"
}

DESTINATION_DIR=./bin
build_dirs gui $DESTINATION_DIR
GUI_STATUS=$?
build_dirs server $DESTINATION_DIR
SERVER_STATUS=$?

STATUSES=(GUI_STATUS SERVER_STATUS)

GLOBAL_STATUS=0
for i in "${STATUSES[@]}"; do
    echo "The $i is ${!i}"
    if [ "${!i}" -ne 0 ]; then
        GLOBAL_STATUS=$i
    fi
done
echo "Overall status: $GLOBAL_STATUS"
exit $GLOBAL_STATUS
