#!/bin/sh

target=${1:-main.js}

make clean
TARGET_EXEC=$target CXX=/usr/lib/emscripten/emcc make -e
