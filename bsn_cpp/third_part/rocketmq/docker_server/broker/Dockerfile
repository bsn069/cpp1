# Start from a Java image.
FROM bsn069/rocketmq_server:latest

RUN chmod +x mqbroker

EXPOSE 10909 10911

COPY conf ${ROCKETMQ_HOME}/conf

CMD sh mqbroker -c ../conf/2m-noslave/broker-a.properties 

 
