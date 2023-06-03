#!/usr/bin/env bash

# This script runs valgrind, if available on the system.

VG=$(which valgrind)
if [ ! -z "$VG" ]; then
   echo "valgrind available on this system at $VG"
   valgrind --tool=memcheck --verbose --log-file=valog $@
else
   $@
fi
