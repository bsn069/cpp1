# Start from a Java image.
FROM bsn069/rocketmq_server:latest

RUN chmod +x bin/mqnamesrv

EXPOSE 9876

CMD cd ${ROCKETMQ_HOME}/bin && sh mqnamesrv 

 
