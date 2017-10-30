#!/bin/bash 

sudo docker rm bsn_rocketmq_server
sudo docker run -it --name bsn_rocketmq_server --link bsn_rocketmq_n1:bsn_rocketmq_n1 --link bsn_rocketmq_b1:bsn_rocketmq_b1 -e "NAMESRV_ADDR=bsn_rocketmq_n1:9876" bsn069/rocketmq_server:latest
