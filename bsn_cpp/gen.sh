#!/bin/sh

if [ ! -d "./third_part/boost" ]; then
	cp /usr/include/boost ./third_part/boost -R
fi

rm -fr ./build
rm -fr ./out
mkdir ./build

pushd build
	# cmake -DCMAKE_BUILD_TYPE=Release ./..
	cmake -DCMAKE_BUILD_TYPE=Debug ./..
	make
popd


