#!/bin/sh


if [ ! -d "/root/bsn_cpp" ]; then
	if [ -d "/media/sf_/github/cpp1/bsn_cpp" ]; then
		ln -s /media/sf_/github/cpp1/bsn_cpp /root/bsn_cpp
	fi

	if [ -d "/media/psf/Home/Documents/pt/github/cpp1/bsn_cpp" ]; then
		ln -s /media/psf/Home/Documents/pt/github/cpp1/bsn_cpp /root/bsn_cpp
	fi
fi

chmod +x _compile.sh
chmod +x _gen.sh
chmod +x _recompile.sh
chmod +x _rm_docker.sh

pushd docker_env/cppdev
	chmod +x _build.sh
	chmod +x _run.sh
popd
