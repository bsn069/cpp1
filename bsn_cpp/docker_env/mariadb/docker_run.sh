#!/bin/sh

docker pull mariadb:10.3.2

mkdir -p ~/bsn_data/mariadb_1/mysql

docker run --name bsn_mariadb_1 -p 3306:3306 -v ~/bsn_data/mariadb_1/mysql:/var/lib/mysql  -e MYSQL_ROOT_PASSWORD=111111 -d mariadb:10.3.2
