#!/bin/bash 


if [ ! -d nogit/rocketmq ]; then
	./init.sh
fi


sudo docker build -t bsn069/rocketmq_server:latest .
 