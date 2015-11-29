#!/bin/bash

if [ -z $1 ];
then
echo "Usage: $0 build_dir" >&2; exit 1;
else
BUILD_DIR=$1
fi

export BIN_DIR="$BUILD_DIR"
export OBJ_DIR="$BUILD_DIR"

if [ -d "$BUILD_DIR" ];
then
  make clean all > /dev/null
else
  mkdir -p "$BUILD_DIR"
  make all > /dev/null
fi


