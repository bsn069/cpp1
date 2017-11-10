#!/bin/sh
# run in docker

if [ ! -d "boost" ]; then
	cp /usr/include/boost boost -R
fi
 
if [ ! -d "LuaJIT" ]; then
	if [ ! -f "LuaJIT-2.0.5.tar.gz" ]; then
		curl http://luajit.org/download/LuaJIT-2.0.5.tar.gz -o LuaJIT-2.0.5.tar.gz
	fi
	tar -xzvf LuaJIT-2.0.5.tar.gz
	mv LuaJIT-2.0.5 LuaJIT
fi
 
if [ ! -d "LuaBridge" ]; then
	git clone https://github.com/bsn069/LuaBridge.git
fi

if [ ! -d "pbc" ]; then
	git clone https://github.com/bsn069/pbc.git
fi

if [ ! -d "protobuf" ]; then
	git clone https://github.com/bsn069/protobuf.git
fi
 
 
# if [ ! -d "protobuf-cpp" ]; then
# 	if [ ! -f "protobuf-cpp-3.4.1.tar.gz" ]; then
# 		curl https://github.com/google/protobuf/releases/download/v3.4.1/protobuf-cpp-3.4.1.tar.gz -o protobuf-cpp-3.4.1.tar.gz
# 	fi
# 	tar -xzvf protobuf-cpp-3.4.1.tar.gz
# 	mv protobuf-cpp-3.4.1 protobuf-cpp
# fi