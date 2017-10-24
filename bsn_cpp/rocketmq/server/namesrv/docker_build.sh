#!/bin/bash 


pushd ..
	./docker_build.sh
popd

sudo docker build -t bsn069/rocketmq_namesrv:latest .
 