#!/bin/sh
rm -rf ./build
mkdir ./build
find -name '*.cbp' -exec rm {} \;
find -name 'cmake_install.cmake' -exec rm {} \;
find -name 'Makefile' -exec rm {} \;
find -name 'CMakeCache.txt' -exec rm {} \;
find -name 'CMakeFiles' -exec rm -rf {} \;
