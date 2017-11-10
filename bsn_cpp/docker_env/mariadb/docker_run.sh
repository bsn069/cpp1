#!/bin/sh

docker pull mariadb:10.3.2

docker run --name bsn_mariadb_1 -p 3306:3306 -e MYSQL_ROOT_PASSWORD=111111 -d mariadb:10.3.2
