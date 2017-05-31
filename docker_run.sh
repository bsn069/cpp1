#!/bin/sh

#  gdb error add seccomp=unconfined
docker run -it --security-opt seccomp=unconfined -v  /media:/media bsn/cppdev
