#!/bin/sh

if [ -x ./filters.pl ] ; then
	./filters.pl "qkc -e -u" ./sys2wonx.pl ./int2sint.pl -f $*
else
	filters.pl "qkc -e -u" sys2wonx.pl int2sint.pl -f $*
fi
