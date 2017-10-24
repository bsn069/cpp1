#!/bin/bash 

pushd namesrv
	./docker_run.sh
popd

pushd broker
	./docker_run.sh
popd