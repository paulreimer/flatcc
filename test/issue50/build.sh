#!/usr/bin/env bash

set -e
cd `dirname $0`/../..
ROOT=`pwd`
TMP=${ROOT}/build/tmp/test/issue50

CC=${CC:-cc}
${ROOT}/scripts/build.sh
mkdir -p ${TMP}
rm -rf ${TMP}/*

# could also use --json to generate both at once
bin/flatcc -av --json -o ${TMP} test/issue50/issue50.fbs

cp test/issue50/*.c ${TMP}

cd ${TMP}

$CC -g -I ${ROOT}/include issue50.c\
    ${ROOT}/lib/libflatccrt_d.a -o issue50_d

echo "running issue50 debug"
./issue50_d

$CC -O2 -DNDEBUG -I ${ROOT}/include issue50.c\
    ${ROOT}/lib/libflatccrt.a -o issue50

echo "running issue50 optimized"
./issue50

echo "issue50 passed"
