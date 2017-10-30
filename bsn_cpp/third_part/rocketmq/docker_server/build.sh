#!/bin/bash 



pushd server
	./docker_build.sh
popd

pushd namesrv
	./docker_build.sh
popd

pushd broker
	./docker_build.sh
popd

 