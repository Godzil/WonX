#!/bin/sh

arg=${1}

if   [ -n "${arg}" -a -x "${arg}" ]; then
	whereperl="${1}"
elif [ -x /usr/local/bin/perl ]; then
	whereperl="/usr/local/bin/perl"
elif [ -x /usr/pkg/bin/perl ]; then
	whereperl="/usr/pkg/bin/perl"
elif [ -x /usr/bin/perl ]; then
	whereperl="/usr/bin/perl"
elif which -s perl; then
	whereperl=`which perl`
else
	echo "Cannot find perl." 1>&2
	echo -n "Input path to perl as full path (Ex. /usr/bin/perl): " 1>&2
	read whereperl
	if [ ! -x $whereperl ]; then
		echo "Error: cannot find perl." 1>&2
		exit 1
	fi
fi

echo "#!$whereperl"
exit 0
