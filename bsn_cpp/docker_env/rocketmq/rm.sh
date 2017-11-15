#!/bin/bash 

sudo docker stop bsn_rocketmq_b1
sudo docker rm bsn_rocketmq_b1
sudo docker stop bsn_rocketmq_n1
sudo docker rm bsn_rocketmq_n1
sudo docker stop bsn_rocketmq_server
sudo docker rm bsn_rocketmq_server

 