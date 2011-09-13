#! /bin/sh
INCLUDE_PATHS="" #-I ./src/Utilities -I ./testsrc/UtilitiesTests"

for i in `find -name "*.h" -exec dirname {} \;`
do
    I_DIR=`dirname $i`;

    INCLUDE_PATHS="$INCLUDE_PATHS -I $i -I $I_DIR -I `dirname $I_DIR`"
    echo "$i `dirname $i`"
done

cppcheck --enable=all $INCLUDE_PATHS . 2> cppcheck.txt
