#!/bin/bash 

bsn_var_rocketmq_ver=4.1.0


bsn_var_rocketmq_zip="rocketmq.zip"
echo ${bsn_var_rocketmq_zip}

pushd nogit
	if [ ! -f ${bsn_var_rocketmq_zip} ]; then
		bsn_var_rocketmq_zip_url="https://dist.apache.org/repos/dist/release/rocketmq/${bsn_var_rocketmq_ver}-incubating/rocketmq-all-${bsn_var_rocketmq_ver}-incubating-bin-release.zip"
		echo ${bsn_var_rocketmq_zip_url}
		curl ${bsn_var_rocketmq_zip_url} -o ${bsn_var_rocketmq_zip}
	fi

	if [ ! -d rocketmq ]; then
		if ! which unzip; then
			echo not found unzip
			yum install -y unzip 
		fi

		unzip rocketmq.zip
		mv rocketmq-all-4.1.0-incubating rocketmq
	fi
popd

