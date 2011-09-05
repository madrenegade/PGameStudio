#!/bin/sh
rm -rf ../coverage
mkdir ../coverage

find -name '*.gcno' -exec rm {} \;
find -name '*.gcda' -exec rm {} \;

lcov --directory ../ --zerocounters

GLOG_v=1 ./TestRunner

lcov --directory ../ --capture --output-file ../coverage/app.info
genhtml --output-directory ../coverage --legend --demangle-cpp ../coverage/app.info

