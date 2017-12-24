#!/bin/sh


if [ ! -d "/root/bsn_cpp" ]; then
	if [ -d "/media/sf_/github/cpp1/bsn_cpp" ]; then
		ln -s /media/sf_/github/cpp1/bsn_cpp /root/bsn_cpp
	fi

	if [ -d "/media/psf/Home/Documents/pt/github/cpp1/bsn_cpp" ]; then
		ln -s /media/psf/Home/Documents/pt/github/cpp1/bsn_cpp /root/bsn_cpp
	fi
fi
