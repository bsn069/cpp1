#!/bin/bash 

sudo docker rm bsn_rocketmq_n1
sudo docker run -d -p 50001:9876 --name bsn_rocketmq_n1  bsn069/rocketmq_namesrv:latest



# sudo docker run -d -p 9876:9876 --name bsn_rocketmq_n2 bsn069/rocketmq_namesrv:latest


# sudo docker run -d -p 9876:9876 --name bsn_rocketmq_n1  bsn069/rocketmq_server:4.1.0
