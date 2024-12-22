#!/bin/bash
echo "Running cmake"
cmake . .
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "Cmake failed with status code $STATUS"
    exit $STATUS
fi
echo "Running make"
make
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "Make failed with status code $STATUS"
    exit $STATUS
fi
