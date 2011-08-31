#!/bin/sh
find -name 'CMakeFiles' -exec rm {} \;
find -name '*.cbp' -exec rm {} \;
find -name 'cmake_install.cmake' -exec rm {} \;
find -name 'Makefile' -exec rm {} \;
