#!/bin/sh

rm -fr core.*
pushd build
	make
popd


