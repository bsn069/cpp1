#!/bin/sh

if [ ! -d "./third_part/asio-1.10.6" ]; then
	pushd third_part	
		tar -jxvf asio-1.10.6.tar.bz2 
	popd
fi

 


