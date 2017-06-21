#!/bin/sh

rm -fr core.*
pushd build
	make clean
	make
popd


