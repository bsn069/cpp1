#!/bin/sh

#  gdb error add seccomp=unconfined
docker run -it --security-opt seccomp=unconfined -v  /root/bsn_cpp:/bsn_cpp bsn069/cppdev
