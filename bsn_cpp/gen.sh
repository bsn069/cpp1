#!/bin/sh


rm -fr ./build
rm -fr ./out
mkdir ./build

pushd build
	# cmake -DCMAKE_BUILD_TYPE=Release ./..
	cmake -DCMAKE_BUILD_TYPE=Debug ./..
popd


