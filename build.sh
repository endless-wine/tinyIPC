#!/bin/bash

BASE_DIR=$(dirname $(readlink -f $0))
buildPath=$BASE_DIR/build

if [ -d "$buildPath" ]; then
	rm -r "$buildPath"	
fi
mkdir "$buildPath"

cd $buildPath
cmake -DCMAKE_TOOLCHAIN_FILE=$BASE_DIR/cmake/cv500.cmake $BASE_DIR
cmake --build . -j
