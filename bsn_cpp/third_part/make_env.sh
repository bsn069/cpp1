#!/bin/sh
# run in docker

#if [ ! -d "boost" ]; then
#	cp /usr/include/boost boost -R
#fi
 
if [ ! -d "LuaJIT" ]; then
	if [ ! -f "LuaJIT-2.0.5.tar.gz" ]; then
		curl http://luajit.org/download/LuaJIT-2.0.5.tar.gz -o LuaJIT-2.0.5.tar.gz
	fi
	tar -xzvf LuaJIT-2.0.5.tar.gz
	mv LuaJIT-2.0.5 LuaJIT
fi
 
if [ ! -d "LuaBridge" ]; then
	git clone https://github.com/vinniefalco/LuaBridge.git
fi

if [ ! -d "pbc" ]; then
	git clone https://github.com/bsn069/pbc.git
fi

if [ ! -d "protobuf" ]; then
	git clone https://github.com/bsn069/protobuf.git
fi
 
if [ ! -d "boost_1_65_1" ]; then
	if [ ! -f "boost_1_65_1.tar.bz2" ]; then
		curl https://ncu.dl.sourceforge.net/project/boost/boost/1.65.1/boost_1_65_1.tar.bz2 -o boost_1_65_1.tar.bz2
	fi
	tar -jxvf boost_1_65_1.tar.bz2
fi

if [ ! -d "sqlite-autoconf-3210000" ]; then
	if [ ! -f "sqlite-autoconf-3210000.tar.gz" ]; then
		curl https://www.sqlite.org/2017/sqlite-autoconf-3210000.tar.gz -o sqlite-autoconf-3210000.tar.gz
	fi
	tar -zxvf sqlite-autoconf-3210000.tar.gz
fi

if [ ! -d "SQLiteCpp" ]; then
	git clone https://github.com/bsn069/SQLiteCpp.git
fi

if [ ! -d "cryptopp" ]; then
	if [ ! -f "cryptopp600.zip" ]; then
		curl https://www.cryptopp.com/cryptopp600.zip -o cryptopp600.zip
	fi
    unzip cryptopp600.zip -d cryptopp
fi

# if [ ! -d "protobuf-cpp" ]; then
# 	if [ ! -f "protobuf-cpp-3.4.1.tar.gz" ]; then
# 		curl https://github.com/google/protobuf/releases/download/v3.4.1/protobuf-cpp-3.4.1.tar.gz -o protobuf-cpp-3.4.1.tar.gz
# 	fi
# 	tar -xzvf protobuf-cpp-3.4.1.tar.gz
# 	mv protobuf-cpp-3.4.1 protobuf-cpp
# fi
