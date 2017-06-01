#!/bin/sh

rm -fr ./build
mkdir ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Release ./..