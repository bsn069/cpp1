# Start from a Java image.
FROM bsn069/rocketmq_server:latest

RUN chmod +x bin/mqbroker

EXPOSE 10909 10911

COPY bin ${ROCKETMQ_HOME}/bin
COPY conf ${ROCKETMQ_HOME}/conf

CMD cd ${ROCKETMQ_HOME}/bin && sh mqbroker -c ../conf/2m-noslave/broker-a.properties 

 
