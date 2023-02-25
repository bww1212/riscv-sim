#!/bin/sh

target=${1:-main}

make clean
TARGET_EXEC=$target CXX=clang++ make -e
#CXX=clang++ make -e

