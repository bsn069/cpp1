#!/bin/bash 

# sudo docker run -it bsn069/rocketmq_broker:latest

sudo docker rm bsn_rocketmq_b1
sudo docker run -d --name bsn_rocketmq_b1 --link bsn_rocketmq_n1:bsn_rocketmq_n1 -e "NAMESRV_ADDR=bsn_rocketmq_n1:9876" bsn069/rocketmq_broker:latest

# sudo docker run -d -p 10911:10911 -p 10909:10909 --name rmqbroker --link rmqnamesrv:rmqnamesrv -e "NAMESRV_ADDR=rmqnamesrv:9876" apache/incubator-rocketmq-broker:4.0.0-incubating

# sudo docker rm bsn_rocketmq_b2
# sudo docker run -it -p 10909:10909 -p 10911:10911 --name bsn_rocketmq_b2 --link bsn_rocketmq_n1:bsn_rocketmq_n1 -e "NAMESRV_ADDR=bsn_rocketmq_n1:9876" bsn069/rocketmq_broker:latest


# sudo docker run -d -p 10909:10909 -p 10911:11109 --name bsn_rocketmq_b1 --link bsn_rocketmq_n1:bsn_rocketmq_n1 -e "NAMESRV_ADDR=bsn_rocketmq_n1:9876" bsn069/rocketmq_broker:latest

# sudo docker run -d -p 10911:10911 -p 10909:10909 --name rmqbroker --link rmqnamesrv:rmqnamesrv -e "NAMESRV_ADDR=rmqnamesrv:9876" apache/incubator-rocketmq-broker:4.0.0-incubating


# sudo docker run -d -p 9876:9876 --name bsn_rocketmq_n2 bsn069/rocketmq_namesrv:latest


# sudo docker run -d -p 9876:9876 --name bsn_rocketmq_n1  bsn069/rocketmq_server:4.1.0
#  nohup sh mqbroker -c ../conf/2m-noslave/broker-a.properties  >/dev/null 2>&1 &