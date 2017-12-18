#!/bin/sh

#  gdb error add seccomp=unconfined
docker run -it --security-opt seccomp=unconfined -v  /root/bsn_cpp:/b -v  /root/bsn_cpp/out:/o bsn069/cppdev
